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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_MAC ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  base_mac_addr ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_base_mac_addr_get(uint8_t *mac)
{
    uint8_t null_mac[6] = {0};

    if (memcmp(base_mac_addr, null_mac, 6) == 0) {
        ESP_LOGI(TAG, "Base MAC address is not set, read default base MAC address from BLK0 of EFUSE");
        return ESP_ERR_INVALID_MAC;
    }

    memcpy(mac, base_mac_addr, 6);

    return ESP_OK;
}