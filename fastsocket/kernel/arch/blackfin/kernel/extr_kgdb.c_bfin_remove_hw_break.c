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
struct TYPE_2__ {int type; unsigned long addr; scalar_t__ enabled; scalar_t__ occupied; } ;

/* Variables and functions */
#define  BP_ACCESS_WATCHPOINT 131 
#define  BP_HARDWARE_BREAKPOINT 130 
#define  BP_READ_WATCHPOINT 129 
#define  BP_WRITE_WATCHPOINT 128 
 int HW_WATCHPOINT_NUM ; 
 int TYPE_DATA_WATCHPOINT ; 
 int TYPE_INST_WATCHPOINT ; 
 TYPE_1__* breakinfo ; 

int bfin_remove_hw_break(unsigned long addr, int len, enum kgdb_bptype type)
{
	int breakno;
	int bfin_type;

	switch (type) {
	case BP_HARDWARE_BREAKPOINT:
		bfin_type = TYPE_INST_WATCHPOINT;
		break;
	case BP_WRITE_WATCHPOINT:
	case BP_READ_WATCHPOINT:
	case BP_ACCESS_WATCHPOINT:
		bfin_type = TYPE_DATA_WATCHPOINT;
		break;
	default:
		return 0;
	}
	for (breakno = 0; breakno < HW_WATCHPOINT_NUM; breakno++)
		if (bfin_type == breakinfo[breakno].type
			&& breakinfo[breakno].occupied
			&& breakinfo[breakno].addr == addr) {
			breakinfo[breakno].occupied = 0;
			breakinfo[breakno].enabled = 0;
		}

	return 0;
}