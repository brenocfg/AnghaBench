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

__attribute__((used)) static
int arm_signed_multiplies(uint32_t instr)
{
	int op1 = BITS(instr,20,0x7), op2 = BITS(instr,5,0x7);

	/* smlald, smlsld, smmls use RD in addition to RM, RS, and RN */
	if ((op1 == 0x4 && (op2 & 0x4) == 0) || (op1 == 0x5 && (op2 & 0x6) == 0x6)) {
		if (ARM_RD(instr) == REG_PC)
			return FASTTRAP_T_INV;
	}

	if (ARM_RM(instr) != REG_PC && ARM_RS(instr) != REG_PC && ARM_RN(instr) != REG_PC)
		return FASTTRAP_T_COMMON;

	return FASTTRAP_T_INV;
}