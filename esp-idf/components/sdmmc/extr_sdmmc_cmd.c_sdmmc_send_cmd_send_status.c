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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  response; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
struct TYPE_7__ {int /*<<< orphan*/  rca; } ;
typedef  TYPE_2__ sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MMC_ARG_RCA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_R1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_SEND_STATUS ; 
 int SCF_CMD_AC ; 
 int SCF_RSP_R1 ; 
 scalar_t__ sdmmc_send_cmd (TYPE_2__*,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_send_status(sdmmc_card_t* card, uint32_t* out_status)
{
    sdmmc_command_t cmd = {
            .opcode = MMC_SEND_STATUS,
            .arg = MMC_ARG_RCA(card->rca),
            .flags = SCF_CMD_AC | SCF_RSP_R1
    };
    esp_err_t err = sdmmc_send_cmd(card, &cmd);
    if (err != ESP_OK) {
        return err;
    }
    if (out_status) {
        *out_status = MMC_R1(cmd.response);
    }
    return ESP_OK;
}