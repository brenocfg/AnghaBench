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
 scalar_t__ THUMB32_RN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int thumb32_dataproc_plain_immed(uint16_t instr1, uint16_t instr2)
{
	int op = BITS(instr1,4,0x1F);

	if (op == 0x04 || op == 0x0C || op == 0x16) {
		/* mov, movt, bfi, bfc */
		/* These use only RD */
		if (THUMB32_RD(instr1,instr2) != REG_PC)
			return FASTTRAP_T_COMMON;
	} else {
		if (THUMB32_RD(instr1,instr2) != REG_PC && THUMB32_RN(instr1,instr2) != REG_PC)
			return FASTTRAP_T_COMMON;
	}

	return FASTTRAP_T_INV;
}