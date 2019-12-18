#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int card_num; int update_clk_reg; int wait_complete; } ;
typedef  TYPE_3__ sdmmc_hw_cmd_t ;
struct TYPE_7__ {scalar_t__ start_command; } ;
struct TYPE_6__ {int hle; } ;
struct TYPE_9__ {TYPE_2__ cmd; TYPE_1__ rintsts; } ;

/* Variables and functions */
 TYPE_5__ SDMMC ; 
 int /*<<< orphan*/  sdmmc_host_start_command (int,TYPE_3__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdmmc_host_clock_update_command(int slot)
{
    // Clock update command (not a real command; just updates CIU registers)
    sdmmc_hw_cmd_t cmd_val = {
        .card_num = slot,
        .update_clk_reg = 1,
        .wait_complete = 1
    };
    bool repeat = true;
    while(repeat) {
        sdmmc_host_start_command(slot, cmd_val, 0);
        while (true) {
            // Sending clock update command to the CIU can generate HLE error.
            // According to the manual, this is okay and we must retry the command.
            if (SDMMC.rintsts.hle) {
                SDMMC.rintsts.hle = 1;
                repeat = true;
                break;
            }
            // When the command is accepted by CIU, start_command bit will be
            // cleared in SDMMC.cmd register.
            if (SDMMC.cmd.start_command == 0) {
                repeat = false;
                break;
            }
        }
    }
}