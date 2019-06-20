
#include <user_interface.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

/* 热点设置 */
const char *ssid = "name";
const char *password = "pwd";
uint8_t mac[] = {0x22,0x33,0x33,0x66,0x66,0x66};
// 8266的ip
const IPAddress softLocal(192, 168, 102, 1);
// 网关
const IPAddress softGateway(192, 168, 102, 1);
const IPAddress softSubnet(255, 255, 255, 0);

ESP8266WebServer server(80);

void handleRoot() {
    server.send(200, "text/html", "<h1>Sparkle Hammer</h1>");
}

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("init...");

    bool SETMAC = wifi_set_macaddr(SOFTAP_IF, &mac[0]);
    //bool SETMAC = wifi_set_macaddr(STATION_IF, &mac[0]);
    Serial.print("set MAC: ");
    Serial.println(SETMAC?"OK":"FALL");

    WiFi.softAPConfig(softLocal, softGateway, softSubnet);
    WiFi.hostname("Hammer");
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("IP address: ");
    Serial.println(myIP);
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);
    Serial.print("MAC: ");
    Serial.println(WiFi.softAPmacAddress());
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() { server.handleClient(); }
