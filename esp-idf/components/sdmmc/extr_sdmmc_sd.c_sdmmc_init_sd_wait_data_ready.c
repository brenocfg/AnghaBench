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
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ESP_OK ; 
 int MMC_R1_READY_FOR_DATA ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  host_is_spi (int /*<<< orphan*/ *) ; 
 scalar_t__ sdmmc_send_cmd_send_status (int /*<<< orphan*/ *,int*) ; 

esp_err_t sdmmc_init_sd_wait_data_ready(sdmmc_card_t* card)
{
    /* Wait for the card to be ready for data transfers */
    uint32_t status = 0;
    uint32_t count = 0;
    while (!host_is_spi(card) && !(status & MMC_R1_READY_FOR_DATA)) {
        // TODO: add some timeout here
        esp_err_t err = sdmmc_send_cmd_send_status(card, &status);
        if (err != ESP_OK) {
            return err;
        }
        if (++count % 16 == 0) {
            ESP_LOGV(TAG, "waiting for card to become ready (%d)", count);
        }
    }
    return ESP_OK;
}