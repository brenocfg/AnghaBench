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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ARM_RD (int /*<<< orphan*/ ) ; 
 scalar_t__ ARM_RM (int /*<<< orphan*/ ) ; 
 scalar_t__ ARM_RN (int /*<<< orphan*/ ) ; 
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 int FASTTRAP_T_LDR_PC_IMMED ; 
 scalar_t__ REG_PC ; 

__attribute__((used)) static
int arm_loadstore_wordbyte(uint32_t instr)
{
	/* Instrument PC relative load with immediate, ignore any other uses of the PC */
	int R = BITS(instr,25,0x1), L = BITS(instr,20,0x1);

	if (R == 1) {
		/* Three register load/store */
		if (ARM_RM(instr) != REG_PC && ARM_RD(instr) != REG_PC && ARM_RN(instr) != REG_PC)
			return FASTTRAP_T_COMMON;
	} else {
		/* Immediate load/store, but still do not support ldr pc, [pc...] */
		if (L == 1 && ARM_RN(instr) == REG_PC && ARM_RD(instr) != REG_PC)
			return FASTTRAP_T_LDR_PC_IMMED;

		if (ARM_RD(instr) != REG_PC && ARM_RN(instr) != REG_PC)
			return FASTTRAP_T_COMMON;
	}

	return FASTTRAP_T_INV;
}