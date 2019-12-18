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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  init_spi_dev (int,int) ; 
 int /*<<< orphan*/  is_slot_initialized (int) ; 
 int /*<<< orphan*/  is_valid_slot (int) ; 

esp_err_t sdspi_host_set_card_clk(int slot, uint32_t freq_khz)
{
    if (!is_valid_slot(slot)) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!is_slot_initialized(slot)) {
        return ESP_ERR_INVALID_STATE;
    }
    ESP_LOGD(TAG, "Setting card clock to %d kHz", freq_khz);
    return init_spi_dev(slot, freq_khz * 1000);
}