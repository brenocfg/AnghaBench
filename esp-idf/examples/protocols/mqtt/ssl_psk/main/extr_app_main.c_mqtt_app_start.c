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
typedef  int /*<<< orphan*/  esp_mqtt_client_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/ * psk_hint_key; int /*<<< orphan*/  event_handle; int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ esp_mqtt_client_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXAMPLE_BROKER_URI ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_get_free_heap_size () ; 
 int /*<<< orphan*/  esp_mqtt_client_init (TYPE_1__ const*) ; 
 int /*<<< orphan*/  esp_mqtt_client_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqtt_event_handler ; 
 int /*<<< orphan*/  psk_hint_key ; 

__attribute__((used)) static void mqtt_app_start(void)
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = EXAMPLE_BROKER_URI,
        .event_handle = mqtt_event_handler,
        .psk_hint_key = &psk_hint_key,
    };

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}