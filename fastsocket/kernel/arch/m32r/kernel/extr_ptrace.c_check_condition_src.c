#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int dummy; } ;

/* Variables and functions */
 unsigned long get_stack_long (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reg_offset ; 

__attribute__((used)) static int
check_condition_src(unsigned long op, unsigned long regno1,
		    unsigned long regno2, struct task_struct *child)
{
	unsigned long reg1, reg2;

	reg2 = get_stack_long(child, reg_offset[regno2]);

	switch (op) {
	case 0x0: /* BEQ */
		reg1 = get_stack_long(child, reg_offset[regno1]);
		return reg1 == reg2;
	case 0x1: /* BNE */
		reg1 = get_stack_long(child, reg_offset[regno1]);
		return reg1 != reg2;
	case 0x8: /* BEQZ */
		return reg2 == 0;
	case 0x9: /* BNEZ */
		return reg2 != 0;
	case 0xa: /* BLTZ */
		return (int)reg2 < 0;
	case 0xb: /* BGEZ */
		return (int)reg2 >= 0;
	case 0xc: /* BLEZ */
		return (int)reg2 <= 0;
	case 0xd: /* BGTZ */
		return (int)reg2 > 0;
	default:
		/* never reached */
		return 0;
	}
}