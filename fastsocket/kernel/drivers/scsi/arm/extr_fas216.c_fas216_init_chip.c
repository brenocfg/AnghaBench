#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int* cfg; unsigned int async_stp; } ;
struct TYPE_6__ {int clockrate; unsigned int select_timeout; } ;
struct TYPE_8__ {TYPE_2__ scsi; TYPE_1__ ifcfg; } ;
typedef  TYPE_3__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CLKF ; 
 int /*<<< orphan*/  REG_CNTL1 ; 
 int /*<<< orphan*/  REG_CNTL2 ; 
 int /*<<< orphan*/  REG_CNTL3 ; 
 int /*<<< orphan*/  REG_SOF ; 
 int /*<<< orphan*/  REG_STIM ; 
 int /*<<< orphan*/  REG_STP ; 
 int /*<<< orphan*/  fas216_writeb (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void fas216_init_chip(FAS216_Info *info)
{
	unsigned int clock = ((info->ifcfg.clockrate - 1) / 5 + 1) & 7;
	fas216_writeb(info, REG_CLKF, clock);
	fas216_writeb(info, REG_CNTL1, info->scsi.cfg[0]);
	fas216_writeb(info, REG_CNTL2, info->scsi.cfg[1]);
	fas216_writeb(info, REG_CNTL3, info->scsi.cfg[2]);
	fas216_writeb(info, REG_STIM, info->ifcfg.select_timeout);
	fas216_writeb(info, REG_SOF, 0);
	fas216_writeb(info, REG_STP, info->scsi.async_stp);
	fas216_writeb(info, REG_CNTL1, info->scsi.cfg[0]);
}