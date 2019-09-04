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
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 scalar_t__ REG_PC ; 
 scalar_t__ THUMB32_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ THUMB32_RM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ THUMB32_RN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int thumb32_dataproc_regshift(uint16_t instr1, uint16_t instr2)
{
	int op = BITS(instr1,5,0xF), S = BITS(instr1,4,0x1);

	if (op == 0 || op == 0x4 || op == 0x8 || op == 0xD) {
		/* These become test instructions if S is 1 and Rd is PC, otherwise they are data instructions. */
		if (S == 1) {
			if (THUMB32_RM(instr1,instr2) != REG_PC && THUMB32_RN(instr1,instr2) != REG_PC)
				return FASTTRAP_T_COMMON;
		} else {
			if (THUMB32_RM(instr1,instr2) != REG_PC && THUMB32_RD(instr1,instr2) != REG_PC &&
			    THUMB32_RN(instr1,instr2) != REG_PC)
				return FASTTRAP_T_COMMON;
		}
	} else if (op == 0x2 || op == 0x3) {
		/* These become moves if RN is PC, otherwise they are data insts. We don't instrument mov pc, reg here */
		if (THUMB32_RM(instr1,instr2) != REG_PC && THUMB32_RD(instr1,instr2) != REG_PC)
			return FASTTRAP_T_COMMON;
	} else {
		/* Normal three register instruction */
		if (THUMB32_RM(instr1,instr2) != REG_PC && THUMB32_RD(instr1,instr2) != REG_PC && THUMB32_RN(instr1,instr2) != REG_PC)
			return FASTTRAP_T_COMMON;
	}

	return FASTTRAP_T_INV;
}