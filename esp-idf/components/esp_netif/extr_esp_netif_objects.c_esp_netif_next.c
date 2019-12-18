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
typedef  int /*<<< orphan*/  esp_netif_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_netif_list_lock () ; 
 int /*<<< orphan*/  esp_netif_list_unlock () ; 
 int /*<<< orphan*/ * esp_netif_next_unsafe (int /*<<< orphan*/ *) ; 

esp_netif_t* esp_netif_next(esp_netif_t* netif)
{
    esp_err_t ret;
    esp_netif_t* result;
    if ((ret = esp_netif_list_lock()) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to lock esp-netif list with %d", ret);
        return NULL;
    }
    result = esp_netif_next_unsafe(netif);
    esp_netif_list_unlock();
    return result;
}