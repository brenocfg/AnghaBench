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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_ARG_RCA (scalar_t__) ; 
 int /*<<< orphan*/  MMC_SELECT_CARD ; 
 scalar_t__ SCF_CMD_AC ; 
 scalar_t__ SCF_RSP_R1 ; 
 int /*<<< orphan*/  sdmmc_send_cmd (int /*<<< orphan*/ *,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_select_card(sdmmc_card_t* card, uint32_t rca)
{
    /* Don't expect to see a response when de-selecting a card */
    uint32_t response = (rca == 0) ? 0 : SCF_RSP_R1;
    sdmmc_command_t cmd = {
            .opcode = MMC_SELECT_CARD,
            .arg = MMC_ARG_RCA(rca),
            .flags = SCF_CMD_AC | response
    };
    return sdmmc_send_cmd(card, &cmd);
}