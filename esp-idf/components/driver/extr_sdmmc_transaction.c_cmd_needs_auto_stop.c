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
struct TYPE_3__ {scalar_t__ datalen; scalar_t__ opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;

/* Variables and functions */
 scalar_t__ MMC_READ_BLOCK_MULTIPLE ; 
 scalar_t__ MMC_READ_DAT_UNTIL_STOP ; 
 scalar_t__ MMC_WRITE_BLOCK_MULTIPLE ; 
 scalar_t__ MMC_WRITE_DAT_UNTIL_STOP ; 

__attribute__((used)) static bool cmd_needs_auto_stop(const sdmmc_command_t* cmd)
{
    /* SDMMC host needs an "auto stop" flag for the following commands: */
    return cmd->datalen > 0 &&
           (cmd->opcode == MMC_WRITE_BLOCK_MULTIPLE ||
            cmd->opcode == MMC_READ_BLOCK_MULTIPLE ||
            cmd->opcode == MMC_WRITE_DAT_UNTIL_STOP ||
            cmd->opcode == MMC_READ_DAT_UNTIL_STOP);
}