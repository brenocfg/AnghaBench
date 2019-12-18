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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EXAMPLE_MDNS_HOST_NAME ; 
 int /*<<< orphan*/  CONFIG_EXAMPLE_WEB_MOUNT_POINT ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_event_loop_create_default () ; 
 int /*<<< orphan*/  esp_netif_init () ; 
 int /*<<< orphan*/  example_connect () ; 
 int /*<<< orphan*/  init_fs () ; 
 int /*<<< orphan*/  initialise_mdns () ; 
 int /*<<< orphan*/  netbiosns_init () ; 
 int /*<<< orphan*/  netbiosns_set_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_flash_init () ; 
 int /*<<< orphan*/  start_rest_server (int /*<<< orphan*/ ) ; 

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    esp_netif_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    initialise_mdns();
    netbiosns_init();
    netbiosns_set_name(CONFIG_EXAMPLE_MDNS_HOST_NAME);

    ESP_ERROR_CHECK(example_connect());
    ESP_ERROR_CHECK(init_fs());
    ESP_ERROR_CHECK(start_rest_server(CONFIG_EXAMPLE_WEB_MOUNT_POINT));
}