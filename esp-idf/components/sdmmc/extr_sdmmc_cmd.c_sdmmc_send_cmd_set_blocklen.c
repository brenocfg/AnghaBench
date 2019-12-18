#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sector_size; } ;
typedef  TYPE_1__ sdmmc_csd_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_2__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_SET_BLOCKLEN ; 
 int SCF_CMD_AC ; 
 int SCF_RSP_R1 ; 
 int /*<<< orphan*/  sdmmc_send_cmd (int /*<<< orphan*/ *,TYPE_2__*) ; 

esp_err_t sdmmc_send_cmd_set_blocklen(sdmmc_card_t* card, sdmmc_csd_t* csd)
{
    sdmmc_command_t cmd = {
            .opcode = MMC_SET_BLOCKLEN,
            .arg = csd->sector_size,
            .flags = SCF_CMD_AC | SCF_RSP_R1
    };
    return sdmmc_send_cmd(card, &cmd);
}