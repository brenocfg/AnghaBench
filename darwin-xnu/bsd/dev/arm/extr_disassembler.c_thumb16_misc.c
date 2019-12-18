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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_CB_N_Z ; 
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 int FASTTRAP_T_POP_PC ; 
 int FASTTRAP_T_PUSH_LR ; 

__attribute__((used)) static
int thumb16_misc(uint16_t instr)
{
	int opcode = BITS(instr,5,0x7F);

	if ((opcode & 0x70) == 0x30 || (opcode & 0x70) == 0x70) {
		/* setend, cps, breakpoint, or if-then, not instrumentable */
		return FASTTRAP_T_INV;
	} else if ((opcode & 0x78) == 0x28) {
		/* Doesn't modify pc, but this happens a lot so make this a special case for emulation */
		return FASTTRAP_T_PUSH_LR;
	} else if ((opcode & 0x78) == 0x68) {
		return FASTTRAP_T_POP_PC;
	} else if ((opcode & 0x28) == 0x08) {
		return FASTTRAP_T_CB_N_Z;
	}

	/* All other instructions work on low regs only and are instrumentable */
	return FASTTRAP_T_COMMON;
}