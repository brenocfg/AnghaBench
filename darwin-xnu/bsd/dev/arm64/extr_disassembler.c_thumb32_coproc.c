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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 int /*<<< orphan*/  thumb32_instword_to_arm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfp_64transfer (int /*<<< orphan*/ ) ; 
 int vfp_loadstore (int /*<<< orphan*/ ) ; 
 int vfp_transfer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int thumb32_coproc(uint16_t instr1, uint16_t instr2)
{
	/* Instrument any VFP data processing instructions, ignore the rest */

	int op1 = BITS(instr1,4,0x3F), coproc = BITS(instr2,8,0xF), op = BITS(instr2,4,0x1);

	if ((op1 & 0x3E) == 0) {
		/* Undefined */
		return FASTTRAP_T_INV;
	}

	if ((coproc & 0xE) == 0xA || (op1 & 0x30) == 0x30) {
		/* VFP instruction */
		uint32_t instr = thumb32_instword_to_arm(instr1,instr2);

		if ((op1 & 0x30) == 0x30) {
			/* VFP data processing uses its own registers */
			return FASTTRAP_T_COMMON;
		}

		if ((op1 & 0x3A) == 0x02 || (op1 & 0x38) == 0x08 || (op1 & 0x30) == 0x10)
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