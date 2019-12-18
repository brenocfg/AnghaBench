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
typedef  int instr ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (int) ; 
 int MEM_OFF ; 
 int MEM_REG ; 
 scalar_t__ STK_PUSH_MATCH (int) ; 
 int /*<<< orphan*/  printk (char*,int*,...) ; 
 int /*<<< orphan*/ * reg_name ; 

__attribute__((used)) static instr *
display_stored_regs(instr * pro_pc, unsigned char * sp)
{
	instr * ret_pc = 0;
	int reg;
	unsigned long value;

	printk("Prologue [<%p>], Frame %p:\n", pro_pc, sp);
	while (!BB_END(*pro_pc))
		if (STK_PUSH_MATCH(*pro_pc)) {
			reg = (*pro_pc & MEM_REG) >> 21;
			value = *(unsigned long *)(sp + (*pro_pc & MEM_OFF));
			if (reg == 26)
				ret_pc = (instr *)value;
			printk("\t\t%s / 0x%016lx\n", reg_name[reg], value);
		}
	return ret_pc;
}