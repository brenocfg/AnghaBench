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
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 int FASTTRAP_T_VLDR_PC_IMMED ; 
 scalar_t__ REG_PC ; 

__attribute__((used)) static
int vfp_loadstore(uint32_t instr)
{
	int opcode = BITS(instr,20,0x1F);

	/* Instrument VLDR */
	if ((opcode & 0x13) == 0x11 && ARM_RN(instr) == REG_PC)
		return FASTTRAP_T_VLDR_PC_IMMED;
	
	/* These instructions all use RN only */
	if (ARM_RN(instr) != REG_PC)
		return FASTTRAP_T_COMMON;

	return FASTTRAP_T_INV;
}