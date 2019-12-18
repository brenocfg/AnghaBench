#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wifi_init_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESPNOW_WIFI_IF ; 
 int /*<<< orphan*/  ESPNOW_WIFI_MODE ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_INIT_CONFIG_DEFAULT () ; 
 int WIFI_PROTOCOL_11B ; 
 int WIFI_PROTOCOL_11G ; 
 int WIFI_PROTOCOL_11N ; 
 int WIFI_PROTOCOL_LR ; 
 int /*<<< orphan*/  WIFI_STORAGE_RAM ; 
 int /*<<< orphan*/  esp_event_loop_create_default () ; 
 int /*<<< orphan*/  esp_netif_init () ; 
 int /*<<< orphan*/  esp_wifi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_wifi_set_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_set_protocol (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_wifi_set_storage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_start () ; 

__attribute__((used)) static void example_wifi_init(void)
{
    esp_netif_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(ESPNOW_WIFI_MODE) );
    ESP_ERROR_CHECK( esp_wifi_start());

#if CONFIG_ESPNOW_ENABLE_LONG_RANGE
    ESP_ERROR_CHECK( esp_wifi_set_protocol(ESPNOW_WIFI_IF, WIFI_PROTOCOL_11B|WIFI_PROTOCOL_11G|WIFI_PROTOCOL_11N|WIFI_PROTOCOL_LR) );
#endif
}