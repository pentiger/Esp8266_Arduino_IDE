#include <ESP8266WiFi.h>

const char* ssid     = "xxxxxxxxxx";  //Our Wifi SSID
const char* password = "xxxxxxxxxx";  //Our Wifi Password
const int buttonPin = 5;             // Pin that we want to monitor
const char* host = "maker.ifttt.com";     //IFTTT channel address
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  }

int value = 1;
void loop() {
   buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {                     //normally the pin is pulled down to ground
       if (value == 1){
       // We now connect to local WIFI
       WiFi.begin(ssid, password);
       while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       }
       WiFiClient client;
       const int httpPort = 80;
       if (!client.connect(host, httpPort)) {
       return;
       }
       // We now create a URI for the request
       String url = "/trigger/EVENT_NAME/with/key/SPECIAL_KEY";   //our link to trigger the event with special key and event name 
  
       // This will send the request to the server
       client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
       value = 0;
       delay(5000);
       }
    }
    else{
    value = 1;
    delay(500);
    }
}
