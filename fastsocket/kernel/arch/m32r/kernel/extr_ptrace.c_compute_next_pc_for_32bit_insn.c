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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_condition_bit (struct task_struct*) ; 
 int /*<<< orphan*/  check_condition_src (unsigned long,unsigned long,unsigned long,struct task_struct*) ; 

__attribute__((used)) static void
compute_next_pc_for_32bit_insn(unsigned long insn, unsigned long pc,
			       unsigned long *next_pc,
			       struct task_struct *child)
{
	unsigned long op;
	unsigned long op2;
	unsigned long disp;
	unsigned long regno1, regno2;

	op = (insn >> 28) & 0xf;
	if (op == 0xf) { 	/* branch 24-bit relative */
		op2 = (insn >> 24) & 0xf;
		switch (op2) {
		case 0xd:	/* BNC */
		case 0x9:	/* BNCL */
			if (!check_condition_bit(child)) {
				disp = (long)(insn << 8) >> 6;
				*next_pc = (pc & ~0x3) + disp;
				return;
			}
			break;
		case 0x8:	/* BCL */
		case 0xc:	/* BC */
			if (check_condition_bit(child)) {
				disp = (long)(insn << 8) >> 6;
				*next_pc = (pc & ~0x3) + disp;
				return;
			}
			break;
		case 0xe:	/* BL */
		case 0xf:	/* BRA */
			disp = (long)(insn << 8) >> 6;
			*next_pc = (pc & ~0x3) + disp;
			return;
		}
	} else if (op == 0xb) { /* branch 16-bit relative */
		op2 = (insn >> 20) & 0xf;
		switch (op2) {
		case 0x0: /* BEQ */
		case 0x1: /* BNE */
		case 0x8: /* BEQZ */
		case 0x9: /* BNEZ */
		case 0xa: /* BLTZ */
		case 0xb: /* BGEZ */
		case 0xc: /* BLEZ */
		case 0xd: /* BGTZ */
			regno1 = ((insn >> 24) & 0xf);
			regno2 = ((insn >> 16) & 0xf);
			if (check_condition_src(op2, regno1, regno2, child)) {
				disp = (long)(insn << 16) >> 14;
				*next_pc = (pc & ~0x3) + disp;
				return;
			}
			break;
		}
	}
	*next_pc = pc + 4;
}