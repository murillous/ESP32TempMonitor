#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

const int ONE_WIRE_BUS = 4;

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

int numberOfDevices;

DeviceAddress tempDevicesAddress;

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}

void setup(){
  Serial.begin(9600);
  sensors.begin();

  numberOfDevices = sensors.getDeviceCount();

  Serial.println();
  Serial.print(numberOfDevices,DEC);
  Serial.println(" sensores encontrados");

  for(int i = 0; i < numberOfDevices; i++){
    if(sensors.getAddress(tempDevicesAddress, i)){
      Serial.printf("Sensor %d com endereco: ", i+1);
      printAddress(tempDevicesAddress);
      Serial.println();
    }
    else{
      Serial.printf("Sensor %d com problema. Verifique a alimentacao e os cabos\n", i+1);
    }
  }
}
void loop(){
  sensors.requestTemperatures();
  for(int i = 0; i<numberOfDevices; i++) {
    if(sensors.getAddress(tempDevicesAddress,i)){
      float TempC = sensors.getTempCByIndex(i);
      Serial.printf("Temperatura do sensor %d: %.2f°C\n", i+1, TempC);
    }
  }
  delay(1000);
}