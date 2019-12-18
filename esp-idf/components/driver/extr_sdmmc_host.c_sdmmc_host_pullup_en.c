#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int width; int /*<<< orphan*/  d7_gpio; int /*<<< orphan*/  d6_gpio; int /*<<< orphan*/  d5_gpio; int /*<<< orphan*/  d4_gpio; int /*<<< orphan*/  d3_gpio; int /*<<< orphan*/  d2_gpio; int /*<<< orphan*/  d1_gpio; int /*<<< orphan*/  d0_gpio; int /*<<< orphan*/  cmd_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  gpio_pullup_en (int /*<<< orphan*/ ) ; 
 TYPE_1__* sdmmc_slot_info ; 

esp_err_t sdmmc_host_pullup_en(int slot, int width)
{
    if (width > sdmmc_slot_info[slot].width) {
        //in esp32 we only support 8 bit in slot 0, note this is occupied by the flash by default
        return ESP_ERR_INVALID_ARG;
    }
    //according to the spec, the host control the clk, we don't to pull it up here
    gpio_pullup_en(sdmmc_slot_info[slot].cmd_gpio);
    gpio_pullup_en(sdmmc_slot_info[slot].d0_gpio);
    if (width >= 4) {
        gpio_pullup_en(sdmmc_slot_info[slot].d1_gpio);
        gpio_pullup_en(sdmmc_slot_info[slot].d2_gpio);
        gpio_pullup_en(sdmmc_slot_info[slot].d3_gpio);
    }
    if (width == 8) {
        gpio_pullup_en(sdmmc_slot_info[slot].d4_gpio);
        gpio_pullup_en(sdmmc_slot_info[slot].d5_gpio);
        gpio_pullup_en(sdmmc_slot_info[slot].d6_gpio);
        gpio_pullup_en(sdmmc_slot_info[slot].d7_gpio);
    }
    return ESP_OK;
}