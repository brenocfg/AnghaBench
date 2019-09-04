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
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 int vfp_64transfer (int /*<<< orphan*/ ) ; 
 int vfp_loadstore (int /*<<< orphan*/ ) ; 
 int vfp_transfer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int arm_syscall_coproc(uint32_t instr)
{
	/* Instrument any VFP data processing instructions, ignore the rest */

	int op1 = BITS(instr,20,0x3F), coproc = BITS(instr,8,0xF), op = BITS(instr,4,0x1);

	if ((op1 & 0x3E) == 0 || (op1 & 0x30) == 0x30) {
		/* Undefined or swi */
		return FASTTRAP_T_INV;
	}

	if ((coproc & 0xE) == 0xA) {
		/* VFP instruction */

		if ((op1 & 0x20) == 0 && (op1 & 0x3A) != 0)
			return vfp_loadstore(instr);

		if ((op1 & 0x3E) == 0x04)
			return vfp_64transfer(instr);

		if ((op1 & 0x30) == 0x20) {
			/* VFP data processing or 8, 16, or 32 bit move between ARM reg and VFP reg */
			if (op == 0) {
				/* VFP data processing uses its own registers */
				return FASTTRAP_T_COMMON;
			} else {
				return vfp_transfer(instr);
			}
		}
	}

	return FASTTRAP_T_INV;
}