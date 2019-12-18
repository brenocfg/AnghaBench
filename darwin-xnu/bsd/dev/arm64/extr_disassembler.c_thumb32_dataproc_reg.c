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
 int thumb32_misc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_parallel_addsub_signed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_parallel_addsub_unsigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int thumb32_dataproc_reg(uint16_t instr1, uint16_t instr2)
{
	int op1 = BITS(instr1,4,0xF), op2 = BITS(instr2,4,0xF);

	if (((0 <= op1) && (op1 <= 5)) && (op2 & 0x8) == 0x8) {
		if (THUMB32_RM(instr1,instr2) != REG_PC && THUMB32_RD(instr1,instr2) != REG_PC)
			return FASTTRAP_T_COMMON;
	}

	if ((op1 & 0x8) == 0 && op2 == 0) {
		if (THUMB32_RM(instr1,instr2) != REG_PC && THUMB32_RD(instr1,instr2) != REG_PC && THUMB32_RN(instr1,instr2) != REG_PC)
			return FASTTRAP_T_COMMON;
	}

	if ((op1 & 0x8) == 0x8 && (op2 & 0xC) == 0)
		return thumb32_parallel_addsub_signed(instr1,instr2);

	if ((op1 & 0x8) == 0x8 && (op2 & 0xC) == 0x4)
		return thumb32_parallel_addsub_unsigned(instr1,instr2);

	if ((op1 & 0xC) == 0x8 && (op2 & 0xC) == 0x8)
		return thumb32_misc(instr1,instr2);

	return FASTTRAP_T_INV;
}