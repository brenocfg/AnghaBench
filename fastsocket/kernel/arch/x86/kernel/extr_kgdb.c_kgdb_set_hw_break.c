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
typedef  enum kgdb_bptype { ____Placeholder_kgdb_bptype } kgdb_bptype ;
struct TYPE_2__ {int enabled; int len; unsigned long addr; unsigned int type; } ;

/* Variables and functions */
#define  BP_ACCESS_WATCHPOINT 130 
#define  BP_HARDWARE_BREAKPOINT 129 
#define  BP_WRITE_WATCHPOINT 128 
 TYPE_1__* breakinfo ; 

__attribute__((used)) static int
kgdb_set_hw_break(unsigned long addr, int len, enum kgdb_bptype bptype)
{
	unsigned type;
	int i;

	for (i = 0; i < 4; i++)
		if (!breakinfo[i].enabled)
			break;
	if (i == 4)
		return -1;

	switch (bptype) {
	case BP_HARDWARE_BREAKPOINT:
		type = 0;
		len  = 1;
		break;
	case BP_WRITE_WATCHPOINT:
		type = 1;
		break;
	case BP_ACCESS_WATCHPOINT:
		type = 3;
		break;
	default:
		return -1;
	}

	if (len == 1 || len == 2 || len == 4)
		breakinfo[i].len  = len - 1;
	else
		return -1;

	breakinfo[i].enabled = 1;
	breakinfo[i].addr = addr;
	breakinfo[i].type = type;

	return 0;
}