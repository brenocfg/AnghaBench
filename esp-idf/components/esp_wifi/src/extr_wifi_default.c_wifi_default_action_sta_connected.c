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
typedef  int /*<<< orphan*/  wifi_netif_driver_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 size_t WIFI_IF_STA ; 
 int /*<<< orphan*/  esp_netif_action_connected (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  esp_netif_get_io_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_receive ; 
 int /*<<< orphan*/  esp_wifi_is_if_ready_when_started (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_register_if_rxcb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** s_wifi_netifs ; 

__attribute__((used)) static void wifi_default_action_sta_connected(void *arg, esp_event_base_t base, int32_t event_id, void *data)
{
    if (s_wifi_netifs[WIFI_IF_STA] != NULL) {
        esp_err_t ret;
        esp_netif_t *esp_netif = s_wifi_netifs[WIFI_IF_STA];
        wifi_netif_driver_t driver = esp_netif_get_io_driver(esp_netif);

        if (!esp_wifi_is_if_ready_when_started(driver)) {
            // if interface not ready when started, rxcb to be registered on connection
            if ((ret = esp_wifi_register_if_rxcb(driver,  esp_netif_receive, esp_netif)) != ESP_OK) {
                ESP_LOGE(TAG, "esp_wifi_register_if_rxcb for if=%p failed with %d", driver, ret);
                return;
            }
        }

        esp_netif_action_connected(s_wifi_netifs[WIFI_IF_STA], base, event_id, data);
    }
}