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
struct TYPE_3__ {char const* cert_pem; int /*<<< orphan*/  event_handle; } ;
typedef  TYPE_1__ esp_mqtt_client_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_get_free_heap_size () ; 
 int /*<<< orphan*/  esp_mqtt_client_init (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mqtt_client ; 
 scalar_t__ mqtt_eclipse_org_pem_start ; 
 int /*<<< orphan*/  mqtt_event_group ; 
 int /*<<< orphan*/  mqtt_event_handler ; 
 int /*<<< orphan*/  xEventGroupCreate () ; 

__attribute__((used)) static void mqtt_app_start(void)
{
    mqtt_event_group = xEventGroupCreate();
    const esp_mqtt_client_config_t mqtt_cfg = {
        .event_handle = mqtt_event_handler,
        .cert_pem = (const char *)mqtt_eclipse_org_pem_start,
    };

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
}