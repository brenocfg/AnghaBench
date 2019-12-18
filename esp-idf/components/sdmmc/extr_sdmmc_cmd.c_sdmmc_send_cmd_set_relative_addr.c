#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  response; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
struct TYPE_7__ {scalar_t__ is_mmc; } ;
typedef  TYPE_2__ sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MMC_ARG_RCA (int) ; 
 int SCF_CMD_BCR ; 
 int SCF_RSP_R6 ; 
 int SD_R6_RCA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_SEND_RELATIVE_ADDR ; 
 int /*<<< orphan*/  assert (int*) ; 
 scalar_t__ sdmmc_send_cmd (TYPE_2__*,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_set_relative_addr(sdmmc_card_t* card, uint16_t* out_rca)
{
    assert(out_rca);
    sdmmc_command_t cmd = {
            .opcode = SD_SEND_RELATIVE_ADDR,
            .flags = SCF_CMD_BCR | SCF_RSP_R6
    };

    /* MMC cards expect us to set the RCA.
     * Set RCA to 1 since we don't support multiple cards on the same bus, for now.
     */
    uint16_t mmc_rca = 1;
    if (card->is_mmc) {
        cmd.arg = MMC_ARG_RCA(mmc_rca);
    }

    esp_err_t err = sdmmc_send_cmd(card, &cmd);
    if (err != ESP_OK) {
        return err;
    }
    *out_rca = (card->is_mmc) ? mmc_rca : SD_R6_RCA(cmd.response);
    return ESP_OK;
}