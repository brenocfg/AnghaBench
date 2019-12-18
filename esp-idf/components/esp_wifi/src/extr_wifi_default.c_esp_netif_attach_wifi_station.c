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
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 size_t WIFI_IF_STA ; 
 int /*<<< orphan*/  create_and_attach (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** s_wifi_netifs ; 

esp_err_t esp_netif_attach_wifi_station(esp_netif_t *esp_netif)
{
    if (esp_netif == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    s_wifi_netifs[WIFI_IF_STA] = esp_netif;
    return create_and_attach(WIFI_IF_STA, esp_netif);
}