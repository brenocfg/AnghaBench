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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int MAX_WIFI_IFS ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  _esp_wifi_clear_default_wifi_handlers () ; 
 int /*<<< orphan*/  disconnect_and_destroy (void*) ; 
 void** s_wifi_netifs ; 

esp_err_t esp_wifi_clear_default_wifi_driver_and_handlers(void *esp_netif)
{
    int i;
    for (i = 0; i< MAX_WIFI_IFS; ++i) {
        // clear internal static pointers to netifs
        if (s_wifi_netifs[i] == esp_netif) {
            s_wifi_netifs[i] = NULL;
        }
        // check if all netifs are cleared to delete default handlers
        if (s_wifi_netifs[i] != NULL) {
            break;
        }
    }

    if (i == MAX_WIFI_IFS) { // if all wifi default netifs are null
        ESP_LOGD(TAG, "Clearing wifi default handlers");
        _esp_wifi_clear_default_wifi_handlers();
    }
    return disconnect_and_destroy(esp_netif);
}