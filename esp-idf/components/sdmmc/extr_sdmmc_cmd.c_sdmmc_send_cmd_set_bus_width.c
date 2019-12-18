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
struct TYPE_3__ {int flags; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int SCF_CMD_AC ; 
 int SCF_RSP_R1 ; 
 int /*<<< orphan*/  SD_APP_SET_BUS_WIDTH ; 
 int /*<<< orphan*/  SD_ARG_BUS_WIDTH_1 ; 
 int /*<<< orphan*/  SD_ARG_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  sdmmc_send_app_cmd (int /*<<< orphan*/ *,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_set_bus_width(sdmmc_card_t* card, int width)
{
    sdmmc_command_t cmd = {
            .opcode = SD_APP_SET_BUS_WIDTH,
            .flags = SCF_RSP_R1 | SCF_CMD_AC,
            .arg = (width == 4) ? SD_ARG_BUS_WIDTH_4 : SD_ARG_BUS_WIDTH_1,
    };

    return sdmmc_send_app_cmd(card, &cmd);
}