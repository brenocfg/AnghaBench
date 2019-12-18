#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
struct TYPE_2__ {scalar_t__ writebuff0; } ;
typedef  int INT32 ;

/* Variables and functions */
 scalar_t__ CHECK_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB940_PICOSTATESAVE2 ; 
 int /*<<< orphan*/ * YM2612GetRegs () ; 
 int /*<<< orphan*/  add_job_940 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* shared_ctl ; 
 int /*<<< orphan*/  wait_busy_940 (int /*<<< orphan*/ ) ; 

void YM2612PicoStateSave2_940(int tat, int tbt)
{
	UINT8 *ym_remote_regs, *ym_local_regs;
	add_job_940(JOB940_PICOSTATESAVE2);
	if (CHECK_BUSY(JOB940_PICOSTATESAVE2)) wait_busy_940(JOB940_PICOSTATESAVE2);

	ym_remote_regs = (UINT8 *) shared_ctl->writebuff0;
	ym_local_regs  = YM2612GetRegs();
	if (*(UINT32 *)(ym_remote_regs + 0x100) != 0x41534d59) {
		printf("code940 didn't return valid save data\n");
		return;
	}

	/* copy addin data only */
	memcpy(ym_local_regs,         ym_remote_regs,         0x20);
	memcpy(ym_local_regs + 0x100, ym_remote_regs + 0x100, 0x30);
	memcpy(ym_local_regs + 0x0b8, ym_remote_regs + 0x0b8, 0x48);
	memcpy(ym_local_regs + 0x1b8, ym_remote_regs + 0x1b8, 0x48);
	*(INT32 *)(ym_local_regs + 0x108) = tat;
	*(INT32 *)(ym_local_regs + 0x10c) = tbt;
}