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
typedef  int /*<<< orphan*/ * wifi_netif_driver_t ;
typedef  int /*<<< orphan*/  wifi_interface_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_netif_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_wifi_create_if_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t create_and_attach(wifi_interface_t wifi_if, esp_netif_t* esp_netif)
{
    wifi_netif_driver_t driver = esp_wifi_create_if_driver(wifi_if);
    if (driver == NULL) {
        ESP_LOGE(TAG, "Failed to create wifi interface handle");
        return ESP_FAIL;
    }
    return esp_netif_attach(esp_netif, driver);
}