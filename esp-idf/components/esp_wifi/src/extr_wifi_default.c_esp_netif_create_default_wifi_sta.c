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
typedef  int /*<<< orphan*/  esp_netif_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_NETIF_DEFAULT_WIFI_STA () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_attach_wifi_station (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_netif_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_wifi_set_default_wifi_sta_handlers () ; 

esp_netif_t* esp_netif_create_default_wifi_sta(void)
{
    esp_netif_config_t cfg = ESP_NETIF_DEFAULT_WIFI_STA();
    esp_netif_t *netif = esp_netif_new(&cfg);
    assert(netif);
    esp_netif_attach_wifi_station(netif);
    esp_wifi_set_default_wifi_sta_handlers();
    return netif;
}