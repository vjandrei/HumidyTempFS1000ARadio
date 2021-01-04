// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12
// https://microcontrollerelectronics.com/fs1000a-wireless-rf433-transmit-and-receive-module-pair/

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <SHT1x.h>

RH_ASK driver(2000, 11, 12);
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 
// RH_ASK driver(2000, PD14, PD13, 0); STM32F4 Discovery: see tx and rx on Orange and Red LEDS

// Specify data and clock connections and instantiate SHT1x object
#define dataPin  4
#define clockPin 5
SHT1x sht1x(dataPin, clockPin);


void setup()
{
    Serial.begin(115200);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
	  ;

}

void loop()
{

    float temp_c;
    float temp_f;
    float humidity;

    // Read values from the sensor
    temp_c = sht1x.readTemperatureC();
    temp_f = sht1x.readTemperatureF();
    humidity = sht1x.readHumidity();
    
    // Print the values to the serial port
    Serial.print("Temperature: ");
    Serial.print(temp_c, DEC);
    Serial.print("C / ");
    Serial.print(temp_f, DEC);
    Serial.print("F. Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
 
  
    const char * msg = "Hello World!";
    int temp = temp_c;
    driver.send((uint8_t *)temp, strlen(temp));
 
    driver.waitPacketSent();
    delay(2000);
}
