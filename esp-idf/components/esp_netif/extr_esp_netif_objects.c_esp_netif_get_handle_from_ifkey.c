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
 int /*<<< orphan*/  esp_netif_get_ifkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_list_lock () ; 
 int /*<<< orphan*/  esp_netif_list_unlock () ; 
 int /*<<< orphan*/ * esp_netif_next_unsafe (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

esp_netif_t *esp_netif_get_handle_from_ifkey(const char *if_key)
{
    esp_err_t ret;
    if ((ret = esp_netif_list_lock()) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to lock esp-netif list with %d", ret);
        return NULL;
    }

    esp_netif_t *esp_netif = esp_netif_next_unsafe(NULL);
    do {
        if (esp_netif && strcmp(if_key, esp_netif_get_ifkey(esp_netif))==0) {
            esp_netif_list_unlock();
            return esp_netif;
        }
    } while (NULL != (esp_netif = esp_netif_next_unsafe(esp_netif)));
    esp_netif_list_unlock();
    return NULL;
}