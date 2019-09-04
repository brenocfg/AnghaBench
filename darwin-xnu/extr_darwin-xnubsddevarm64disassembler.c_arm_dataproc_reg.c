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
 int FASTTRAP_T_MOV_PC_REG ; 
 scalar_t__ REG_PC ; 

__attribute__((used)) static
int arm_dataproc_reg(uint32_t instr)
{
	int op1 = BITS(instr,20,0x1F), op2 = BITS(instr,7,0x1F), op3 = BITS(instr,5,0x3);

	if (op1 == 0x11 || op1 == 0x13 || op1 == 0x15 || op1 == 0x17) {
		/* These are comparison flag setting instructions and do not have RD */
		if (ARM_RN(instr) != REG_PC && ARM_RM(instr) != REG_PC)
			return FASTTRAP_T_COMMON;

		return FASTTRAP_T_INV;
	}

	/* The rest can, in theory, write or use the PC. The only one we instrument is mov pc, reg.
	 * movs pc, reg is a privileged instruction so we don't instrument that variant. The s bit
	 * is bit 0 of op1 and should be zero.
	 */
	if (op1 == 0x1A && op2 == 0 && op3 == 0 && ARM_RD(instr) == REG_PC)
		return FASTTRAP_T_MOV_PC_REG;

	/* Any instruction at this point is a three register instruction or two register instruction with RN = 0 */
	if (ARM_RN(instr) != REG_PC && ARM_RD(instr) != REG_PC && ARM_RM(instr) != REG_PC)
		return FASTTRAP_T_COMMON;

	return FASTTRAP_T_INV;
}