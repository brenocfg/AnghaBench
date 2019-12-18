#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MMC_GO_IDLE_STATE ; 
 int SCF_CMD_BC ; 
 int SCF_RSP_R0 ; 
 int SCF_RSP_R1 ; 
 int SDMMC_GO_IDLE_DELAY_MS ; 
 scalar_t__ host_is_spi (int /*<<< orphan*/ *) ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ sdmmc_send_cmd (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

esp_err_t sdmmc_send_cmd_go_idle_state(sdmmc_card_t* card)
{
    sdmmc_command_t cmd = {
        .opcode = MMC_GO_IDLE_STATE,
        .flags = SCF_CMD_BC | SCF_RSP_R0,
    };
    esp_err_t err = sdmmc_send_cmd(card, &cmd);
    if (host_is_spi(card)) {
        /* To enter SPI mode, CMD0 needs to be sent twice (see figure 4-1 in
         * SD Simplified spec v4.10). Some cards enter SD mode on first CMD0,
         * so don't expect the above command to succeed.
         * SCF_RSP_R1 flag below tells the lower layer to expect correct R1
         * response (in SPI mode).
         */
        (void) err;
        vTaskDelay(SDMMC_GO_IDLE_DELAY_MS / portTICK_PERIOD_MS);

        cmd.flags |= SCF_RSP_R1;
        err = sdmmc_send_cmd(card, &cmd);
    }
    if (err == ESP_OK) {
        vTaskDelay(SDMMC_GO_IDLE_DELAY_MS / portTICK_PERIOD_MS);
    }
    return err;
}