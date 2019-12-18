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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  base_mac_addr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 

esp_err_t esp_base_mac_addr_set(const uint8_t *mac)
{
    if (mac == NULL) {
        ESP_LOGE(TAG, "Base MAC address is NULL");
        return ESP_ERR_INVALID_ARG;
    }
    if (mac[0] & 0x01) {
        ESP_LOGE(TAG, "Base MAC must be a unicast MAC");
        return ESP_ERR_INVALID_ARG;
    }

    memcpy(base_mac_addr, mac, 6);

    return ESP_OK;
}