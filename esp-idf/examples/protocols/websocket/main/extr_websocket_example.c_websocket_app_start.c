#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ esp_websocket_client_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ esp_websocket_client_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WEBSOCKET_ECHO_ENDPOINT ; 
 int /*<<< orphan*/  WEBSOCKET_EVENT_ANY ; 
 int /*<<< orphan*/  esp_websocket_client_destroy (scalar_t__) ; 
 scalar_t__ esp_websocket_client_init (TYPE_1__ const*) ; 
 scalar_t__ esp_websocket_client_is_connected (scalar_t__) ; 
 int /*<<< orphan*/  esp_websocket_client_send (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_websocket_client_start (scalar_t__) ; 
 int /*<<< orphan*/  esp_websocket_client_stop (scalar_t__) ; 
 int /*<<< orphan*/  esp_websocket_register_events (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_RATE_MS ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  websocket_event_handler ; 

__attribute__((used)) static void websocket_app_start(void)
{
    ESP_LOGI(TAG, "Connectiong to %s...", WEBSOCKET_ECHO_ENDPOINT);

    const esp_websocket_client_config_t websocket_cfg = {
        .uri = WEBSOCKET_ECHO_ENDPOINT, // or wss://echo.websocket.org for websocket secure
    };

    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);

    esp_websocket_client_start(client);
    char data[32];
    int i = 0;
    while (i < 10) {
        if (esp_websocket_client_is_connected(client)) {
            int len = sprintf(data, "hello %04d", i++);
            ESP_LOGI(TAG, "Sending %s", data);
            esp_websocket_client_send(client, data, len, portMAX_DELAY);
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
    esp_websocket_client_stop(client);
    ESP_LOGI(TAG, "Websocket Stopped");
    esp_websocket_client_destroy(client);
}