// This #include statement was automatically added by the Particle IDE.
#include "HttpClient.h"

unsigned int nextTime = 0;    // Next time to contact the server
HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    // delay(500);
    clearDisplay();
    
    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(128); // move cursor to beginning of first line
    Serial1.write("Starting...");
    
    clearDisplay();
    
    delay(2000);
}

void loop() {
    // if (nextTime > millis()) {
    //     return;
    // }
    
    clearDisplay();
    
    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(128); // move cursor to beginning of first line
    Serial1.write("Updating...");
    
    String t = getApparentTemperature();
    String p = getPrecipProbability();
    String s = getSummary();

    Serial.println();
    Serial.println();
    Serial.println("Apparent temperature: " + t);
    Serial.println();
    Serial.println();
    Serial.println("Precipitation probability: " + p);
    Serial.println();
    Serial.println();
    Serial.println("Summary: " + s);
    Serial.println();
    Serial.println();
    
    clearDisplay();

    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(128); // move cursor to beginning of first line
    
    String tempStr = t + "  " + p;
    
    char tempArr[16];
    strcpy(tempArr, tempStr.c_str());
    Serial1.write(tempArr);
    
    
    Serial1.write(254); // move cursor to beginning of second line
    Serial1.write(192); // move cursor to beginning of second line
    
    Serial1.write("                "); // clear second line of display
    
    Serial1.write(254); // move cursor to beginning of second line 
    Serial1.write(192); // move cursor to beginning of second line
    
    char summArr[16];
    strcpy(summArr, s.c_str());
    Serial1.write(summArr);
    
    if (t.length() > 3 && p.length() > 3 && s.length() > 3) {
        delay(1000*80); // pause if data is retrieved
    }
    
   clearDisplay();
    
    // nextTime = millis() + 10000;
}

String getApparentTemperature() {
    request.hostname = "samir-heroku.herokuapp.com";
    request.path = "/apparentTemperature.json";
    request.port = 80;
    http.get(request, response, headers);
    return response.body;
}

String getPrecipProbability() {
    request.hostname = "samir-heroku.herokuapp.com";
    request.path = "/precipProbability.json";
    request.port = 80;
    http.get(request, response, headers);
    return response.body;
}

String getSummary() {
    request.hostname = "samir-heroku.herokuapp.com";
    request.path = "/summary.json";
    request.port = 80;
    http.get(request, response, headers);
    return response.body;
}

void clearDisplay() {
    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(128); // move cursor to beginning of first line
    Serial1.write("                "); // clear display
    Serial1.write("                ");
}