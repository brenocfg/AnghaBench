#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  response; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
struct TYPE_9__ {int /*<<< orphan*/  rca; } ;
typedef  TYPE_2__ sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MMC_APP_CMD ; 
 int /*<<< orphan*/  MMC_ARG_RCA (int /*<<< orphan*/ ) ; 
 int MMC_R1 (int /*<<< orphan*/ ) ; 
 int MMC_R1_APP_CMD ; 
 int SCF_CMD_AC ; 
 int SCF_RSP_R1 ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  host_is_spi (TYPE_2__*) ; 
 scalar_t__ sdmmc_send_cmd (TYPE_2__*,TYPE_1__*) ; 

esp_err_t sdmmc_send_app_cmd(sdmmc_card_t* card, sdmmc_command_t* cmd)
{
    sdmmc_command_t app_cmd = {
        .opcode = MMC_APP_CMD,
        .flags = SCF_CMD_AC | SCF_RSP_R1,
        .arg = MMC_ARG_RCA(card->rca),
    };
    esp_err_t err = sdmmc_send_cmd(card, &app_cmd);
    if (err != ESP_OK) {
        return err;
    }
    // Check APP_CMD status bit (only in SD mode)
    if (!host_is_spi(card) && !(MMC_R1(app_cmd.response) & MMC_R1_APP_CMD)) {
        ESP_LOGW(TAG, "card doesn't support APP_CMD");
        return ESP_ERR_NOT_SUPPORTED;
    }
    return sdmmc_send_cmd(card, cmd);
}