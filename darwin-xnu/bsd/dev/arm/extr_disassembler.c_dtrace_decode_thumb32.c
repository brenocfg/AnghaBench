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
 int FASTTRAP_T_INV ; 
 int thumb32_b_misc_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_coproc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_dataproc_mod_immed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_dataproc_plain_immed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_dataproc_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_dataproc_regshift (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thumb32_instword_to_arm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_loadbyte_memhint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_loadhalfword_memhint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_loadstore_double_exclusive_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_loadstore_multiple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_loadword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_longmultiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thumb32_store_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfp_struct_loadstore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int dtrace_decode_thumb32(uint16_t instr1, uint16_t instr2)
{
	int op1 = BITS(instr1,11,0x3), op2 = BITS(instr1,4,0x7F), op = BITS(instr2,15,0x1);

	if (op1 == 0x1) {
		if ((op2 & 0x64) == 0)
			return thumb32_loadstore_multiple(instr1,instr2);

		if ((op2 & 0x64) == 0x04)
			return thumb32_loadstore_double_exclusive_table(instr1,instr2);

		if ((op2 & 0x60) == 0x20)
			return thumb32_dataproc_regshift(instr1,instr2);

		if ((op2 & 0x40) == 0x40)
			return thumb32_coproc(instr1,instr2);
	}

	if (op1 == 0x2) {
		if ((op2 & 0x20) == 0 && op == 0)
			return thumb32_dataproc_mod_immed(instr1,instr2);

		if ((op2 & 0x20) == 0x20 && op == 0)
			return thumb32_dataproc_plain_immed(instr1,instr2);

		if (op == 1)
			return thumb32_b_misc_control(instr1,instr2);
	}

	if (op1 == 0x3) {
		if ((op2 & 0x71) == 0)
			return thumb32_store_single(instr1,instr2);

		if ((op2 & 0x71) == 0x10) {
			return vfp_struct_loadstore(thumb32_instword_to_arm(instr1,instr2));
		}

		if ((op2 & 0x67) == 0x01)
			return thumb32_loadbyte_memhint(instr1,instr2);

		if ((op2 & 0x67) == 0x03)
			return thumb32_loadhalfword_memhint(instr1,instr2);

		if ((op2 & 0x67) == 0x05)
			return thumb32_loadword(instr1,instr2);

		if ((op2 & 0x67) == 0x07) {
			/* Undefined instruction */
			return FASTTRAP_T_INV;
		}

		if ((op2 & 0x70) == 0x20)
			return thumb32_dataproc_reg(instr1,instr2);

		if ((op2 & 0x78) == 0x30)
			return thumb32_multiply(instr1,instr2);

		if ((op2 & 0x78) == 0x38)
			return thumb32_longmultiply(instr1,instr2);

		if ((op2 & 0x40) == 0x40)
			return thumb32_coproc(instr1,instr2);
	}

	return FASTTRAP_T_INV;
}