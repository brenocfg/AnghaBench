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
struct TYPE_2__ {int loopc; int* vstarts; int last_lr; int lastjob; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGS_Menu ; 
 int crashed_940 ; 
 int /*<<< orphan*/  engineState ; 
 int* memregl ; 
 int* memregs ; 
 int /*<<< orphan*/  menu_update_msg (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* shared_ctl ; 
 int /*<<< orphan*/  spend_cycles (int) ; 

__attribute__((used)) static void wait_busy_940(int job)
{
	int i;

	job--;
	for (i = 0; (memregs[0x3b46>>1] & (1<<job)) && i < 0x10000; i++)
		spend_cycles(8*1024); // tested to be best for mp3 dec
	if (i < 0x10000) return;

	/* 940 crashed */
	printf("940 crashed (cnt: %i, ve: ", shared_ctl->loopc);
	for (i = 0; i < 8; i++)
		printf("%i ", shared_ctl->vstarts[i]);
	printf(")\n");
	printf("irq pending flags: DUALCPU %04x, SRCPND %08x (see 26), INTPND %08x\n",
		memregs[0x3b46>>1], memregl[0x4500>>2], memregl[0x4510>>2]);
	printf("last lr: %08x, lastjob: %i\n", shared_ctl->last_lr, shared_ctl->lastjob);
	printf("trying to interrupt..\n");
	memregs[0x3B3E>>1] = 0xffff;
	for (i = 0; memregs[0x3b46>>1] && i < 0x10000; i++)
		spend_cycles(8*1024);
	printf("i = 0x%x\n", i);
	printf("irq pending flags: DUALCPU %04x, SRCPND %08x (see 26), INTPND %08x\n",
		memregs[0x3b46>>1], memregl[0x4500>>2], memregl[0x4510>>2]);
	printf("last lr: %08x, lastjob: %i\n", shared_ctl->last_lr, shared_ctl->lastjob);

	menu_update_msg("940 crashed, too much overclock?");
	engineState = PGS_Menu;
	crashed_940 = 1;
}