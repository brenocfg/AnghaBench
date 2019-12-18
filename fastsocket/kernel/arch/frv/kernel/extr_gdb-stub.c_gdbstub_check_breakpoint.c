#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pc; } ;
struct TYPE_3__ {unsigned long addr; } ;

/* Variables and functions */
 TYPE_2__* __debug_frame ; 
 TYPE_1__* gdbstub_bkpts ; 

__attribute__((used)) static void gdbstub_check_breakpoint(void)
{
	unsigned long addr = __debug_frame->pc - 4;
	int bkpt;

	for (bkpt = 255; bkpt >= 0; bkpt--)
		if (gdbstub_bkpts[bkpt].addr == addr)
			break;
	if (bkpt >= 0)
		__debug_frame->pc = addr;

	//gdbstub_printk("alter pc [%d] %08lx\n", bkpt, __debug_frame->pc);

}