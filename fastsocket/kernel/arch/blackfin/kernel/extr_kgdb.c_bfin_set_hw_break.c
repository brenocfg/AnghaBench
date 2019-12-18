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
struct TYPE_2__ {int type; int occupied; int enabled; unsigned long addr; int dataacc; scalar_t__ count; scalar_t__ skip; } ;

/* Variables and functions */
#define  BP_ACCESS_WATCHPOINT 131 
#define  BP_HARDWARE_BREAKPOINT 130 
#define  BP_READ_WATCHPOINT 129 
#define  BP_WRITE_WATCHPOINT 128 
 int ENOSPC ; 
 int HW_INST_WATCHPOINT_NUM ; 
 int TYPE_DATA_WATCHPOINT ; 
 int TYPE_INST_WATCHPOINT ; 
 TYPE_1__* breakinfo ; 

int bfin_set_hw_break(unsigned long addr, int len, enum kgdb_bptype type)
{
	int breakno;
	int bfin_type;
	int dataacc = 0;

	switch (type) {
	case BP_HARDWARE_BREAKPOINT:
		bfin_type = TYPE_INST_WATCHPOINT;
		break;
	case BP_WRITE_WATCHPOINT:
		dataacc = 1;
		bfin_type = TYPE_DATA_WATCHPOINT;
		break;
	case BP_READ_WATCHPOINT:
		dataacc = 2;
		bfin_type = TYPE_DATA_WATCHPOINT;
		break;
	case BP_ACCESS_WATCHPOINT:
		dataacc = 3;
		bfin_type = TYPE_DATA_WATCHPOINT;
		break;
	default:
		return -ENOSPC;
	}

	/* Becasue hardware data watchpoint impelemented in current
	 * Blackfin can not trigger an exception event as the hardware
	 * instrction watchpoint does, we ignaore all data watch point here.
	 * They can be turned on easily after future blackfin design
	 * supports this feature.
	 */
	for (breakno = 0; breakno < HW_INST_WATCHPOINT_NUM; breakno++)
		if (bfin_type == breakinfo[breakno].type
			&& !breakinfo[breakno].occupied) {
			breakinfo[breakno].occupied = 1;
			breakinfo[breakno].skip = 0;
			breakinfo[breakno].enabled = 1;
			breakinfo[breakno].addr = addr;
			breakinfo[breakno].dataacc = dataacc;
			breakinfo[breakno].count = 0;
			return 0;
		}

	return -ENOSPC;
}