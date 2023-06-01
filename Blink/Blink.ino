

#define button 2
#define LED_PIN 6
//#define DHTPIN 3
//#include "Arduino_SensorKit.h"


int button_pressed = 0;
volatile bool timerStarted = false;


void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(button, INPUT);
  attachInterrupt(analogPinToInterrupt(button), buttonISR, FALLING);
  Serial.begin(9600);

}

void timer_setup()
{
  // Clear Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 0;

  // Set Timer1 prescaler to 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Configure CTC Mode where TOP = OCR1A
  TCCR1B |= (1 << WGM12);

  // Set the value for the output compare register
  OCR1A = 15625; // 1 seconds

  // Enable Timer1 compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void buttonISR() {
  //digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  button_pressed++;

  if (!timerStarted) {
    timerStarted = true;
    timer_setup();

  }
}

ISR(TIMER1_COMPA_vect) {
  switch (button_pressed) {
    case 1:
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      Serial.print("times pressed: 1 \n");
      break;
    /*case 2:
      Environment.begin();
      Serial.print("times pressed: 2 \n");
      Serial.print("Temperature = ");
      Serial.print(Environment.readTemperature()); //print temperature
      Serial.println(" C");
      Serial.print("Humidity = ");
      Serial.print(Environment.readHumidity()); //print humidity
      Serial.println(" %");
      
      break;*/
      
    default:
      Serial.print("times pressed: ");
      Serial.print(button_pressed);
      Serial.print("\n");

  }
  button_pressed = 0;
  timerStarted = false;

  TIMSK1 &= ~(1 << OCIE1A);
}

void loop()
{

}