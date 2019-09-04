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
 scalar_t__ ARM_RN (int /*<<< orphan*/ ) ; 
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_B_COND ; 
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 int FASTTRAP_T_LDM_PC ; 
 int FASTTRAP_T_STM_LR ; 
 scalar_t__ REG_PC ; 
 scalar_t__ REG_SP ; 

__attribute__((used)) static
int arm_branch_link_blockdata(uint32_t instr)
{
	int branch = BITS(instr,25,0x1), link = BITS(instr,24,0x1), op = BITS(instr,20,0x1F), uses_pc = BITS(instr,15,0x1), uses_lr = BITS(instr,14,0x1);

	if (branch == 1) {
		if (link == 0)
			return FASTTRAP_T_B_COND;
		return FASTTRAP_T_INV;
	} else {
		/* Only emulate a use of the pc if it's a return from function: ldmia sp!, { ... pc } */
		if (op == 0x0B && ARM_RN(instr) == REG_SP && uses_pc == 1)
			return FASTTRAP_T_LDM_PC;

		/* stmia sp!, { ... lr } doesn't touch the pc, but it is very common, so special case it */
		if (op == 0x12 && ARM_RN(instr) == REG_SP && uses_lr == 1)
			return FASTTRAP_T_STM_LR;

		if (ARM_RN(instr) != REG_PC && uses_pc == 0)
			return FASTTRAP_T_COMMON;
	}

	return FASTTRAP_T_INV;
}