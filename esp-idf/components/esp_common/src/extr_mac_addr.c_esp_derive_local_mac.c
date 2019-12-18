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
 scalar_t__ memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

esp_err_t esp_derive_local_mac(uint8_t* local_mac, const uint8_t* universal_mac)
{
    uint8_t idx;

    if (local_mac == NULL || universal_mac == NULL) {
        ESP_LOGE(TAG, "mac address param is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    memcpy(local_mac, universal_mac, 6);
    for (idx = 0; idx < 64; idx++) {
        local_mac[0] = universal_mac[0] | 0x02;
        local_mac[0] ^= idx << 2;

        if (memcmp(local_mac, universal_mac, 6)) {
            break;
        }
    }

    return ESP_OK;
}