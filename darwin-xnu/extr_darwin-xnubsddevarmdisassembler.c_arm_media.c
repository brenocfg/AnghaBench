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
 scalar_t__ ARM_RS (int /*<<< orphan*/ ) ; 
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 scalar_t__ REG_PC ; 
 int arm_pack_unpack_sat_reversal (int /*<<< orphan*/ ) ; 
 int arm_parallel_addsub_signed (int /*<<< orphan*/ ) ; 
 int arm_parallel_addsub_unsigned (int /*<<< orphan*/ ) ; 
 int arm_signed_multiplies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int arm_media(uint32_t instr)
{
	int op1 = BITS(instr,20,0x1F), op2 = BITS(instr,5,0x7);

	if ((op1 & 0x1C) == 0)
		return arm_parallel_addsub_signed(instr);

	if ((op1 & 0x1C) == 0x04)
		return arm_parallel_addsub_unsigned(instr);

	if ((op1 & 0x18) == 0x08)
		return arm_pack_unpack_sat_reversal(instr);

	if ((op1 & 0x18) == 0x10)
		return arm_signed_multiplies(instr);

	if (op1 == 0x1F && op2 == 0x7) {
		/* Undefined instruction */
		return FASTTRAP_T_INV;
	}

	if (op1 == 0x18 && op2 == 0) {
		/* usad8 usada8 */
		/* The registers are named differently in the reference manual for this instruction
		 * but the following positions are correct */

		if (ARM_RM(instr) != REG_PC && ARM_RS(instr) != REG_PC && ARM_RN(instr) != REG_PC)
			return FASTTRAP_T_COMMON;

		return FASTTRAP_T_INV;
	}

	if ((op1 & 0x1E) == 0x1C && (op2 & 0x3) == 0) {
		/* bfc bfi */
		if (ARM_RD(instr) != REG_PC)
			return FASTTRAP_T_COMMON;

		return FASTTRAP_T_INV;
	}

	if (((op1 & 0x1E) == 0x1A || (op1 & 0x1E) == 0x1E) && ((op2 & 0x3) == 0x2)) {
		/* sbfx ubfx */
		if (ARM_RM(instr) != REG_PC && ARM_RD(instr) != REG_PC)
			return FASTTRAP_T_COMMON;

		return FASTTRAP_T_INV;
	}

	return FASTTRAP_T_INV;
}