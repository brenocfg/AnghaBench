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
 int FASTTRAP_T_B_UNCOND ; 
 int FASTTRAP_T_COMMON ; 
 int FASTTRAP_T_INV ; 
 int FASTTRAP_T_LDR_PC_IMMED ; 
 int thumb16_cond_supervisor (int /*<<< orphan*/ ) ; 
 int thumb16_data_proc (int /*<<< orphan*/ ) ; 
 int thumb16_data_special_and_branch (int /*<<< orphan*/ ) ; 
 int thumb16_loadstore_single (int /*<<< orphan*/ ) ; 
 int thumb16_misc (int /*<<< orphan*/ ) ; 
 int thumb16_shift_addsub_move_compare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int dtrace_decode_thumb16(uint16_t instr)
{
	int opcode = BITS(instr,10,0x3F);

	if ((opcode & 0x30) == 0)
		return thumb16_shift_addsub_move_compare(instr);

	if (opcode == 0x10)
		return thumb16_data_proc(instr);

	if (opcode == 0x11)
		return thumb16_data_special_and_branch(instr);

	if ((opcode & 0x3E) == 0x12) {
		/* ldr (literal) */
		return FASTTRAP_T_LDR_PC_IMMED;
	}

	if ((opcode & 0x3C) == 0x14 || (opcode & 0x38) == 0x18 || (opcode & 0x38) == 0x20)
		return thumb16_loadstore_single(instr);

	if ((opcode & 0x3E) == 0x28) {
		/* adr, uses the pc */
		return FASTTRAP_T_INV;
	}

	if ((opcode & 0x3E) == 0x2A) {
		/* add (sp plus immediate) */
		return FASTTRAP_T_COMMON;
	}

	if ((opcode & 0x3C) == 0x2C)
		return thumb16_misc(instr);

	if ((opcode & 0x3E) == 0x30) {
		/* stm - can't access high registers */
		return FASTTRAP_T_COMMON;
	}

	if ((opcode & 0x3E) == 0x32) {
		/* ldm - can't access high registers */
		return FASTTRAP_T_COMMON;
	}

	if ((opcode & 0x3C) == 0x34) {
		return thumb16_cond_supervisor(instr);
	}

	if ((opcode & 0x3E) == 0x38) {
		/* b unconditional */
		return FASTTRAP_T_B_UNCOND;
	}

	return FASTTRAP_T_INV;
}