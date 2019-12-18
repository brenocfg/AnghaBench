#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  ddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  emmc_ddr_reg; TYPE_1__ uhs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ SDMMC ; 
 int /*<<< orphan*/  TAG ; 
 int* s_slot_width ; 

esp_err_t sdmmc_host_set_bus_ddr_mode(int slot, bool ddr_enabled)
{
    if (!(slot == 0 || slot == 1)) {
        return ESP_ERR_INVALID_ARG;
    }
    if (s_slot_width[slot] == 8 && ddr_enabled) {
        ESP_LOGW(TAG, "DDR mode with 8-bit bus width is not supported yet");
        // requires reconfiguring controller clock for 2x card frequency
        return ESP_ERR_NOT_SUPPORTED;
    }
    uint32_t mask = BIT(slot);
    if (ddr_enabled) {
        SDMMC.uhs.ddr |= mask;
        SDMMC.emmc_ddr_reg |= mask;
    } else {
        SDMMC.uhs.ddr &= ~mask;
        SDMMC.emmc_ddr_reg &= ~mask;
    }
    ESP_LOGD(TAG, "slot=%d ddr=%d", slot, ddr_enabled ? 1 : 0);
    return ESP_OK;
}