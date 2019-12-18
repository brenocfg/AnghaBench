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
 int /*<<< orphan*/  PT_BPC ; 
 int /*<<< orphan*/  check_condition_bit (struct task_struct*) ; 
 unsigned long get_stack_long (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reg_offset ; 

__attribute__((used)) static void
compute_next_pc_for_16bit_insn(unsigned long insn, unsigned long pc,
			       unsigned long *next_pc,
			       struct task_struct *child)
{
	unsigned long op, op2, op3;
	unsigned long disp;
	unsigned long regno;
	int parallel = 0;

	if (insn & 0x00008000)
		parallel = 1;
	if (pc & 3)
		insn &= 0x7fff;	/* right slot */
	else
		insn >>= 16;	/* left slot */

	op = (insn >> 12) & 0xf;
	op2 = (insn >> 8) & 0xf;
	op3 = (insn >> 4) & 0xf;

	if (op == 0x7) {
		switch (op2) {
		case 0xd: /* BNC */
		case 0x9: /* BNCL */
			if (!check_condition_bit(child)) {
				disp = (long)(insn << 24) >> 22;
				*next_pc = (pc & ~0x3) + disp;
				return;
			}
			break;
		case 0x8: /* BCL */
		case 0xc: /* BC */
			if (check_condition_bit(child)) {
				disp = (long)(insn << 24) >> 22;
				*next_pc = (pc & ~0x3) + disp;
				return;
			}
			break;
		case 0xe: /* BL */
		case 0xf: /* BRA */
			disp = (long)(insn << 24) >> 22;
			*next_pc = (pc & ~0x3) + disp;
			return;
			break;
		}
	} else if (op == 0x1) {
		switch (op2) {
		case 0x0:
			if (op3 == 0xf) { /* TRAP */
#if 1
				/* pass through */
#else
 				/* kernel space is not allowed as next_pc */
				unsigned long evb;
				unsigned long trapno;
				trapno = insn & 0xf;
				__asm__ __volatile__ (
					"mvfc %0, cr5\n"
		 			:"=r"(evb)
		 			:
				);
				*next_pc = evb + (trapno << 2);
				return;
#endif
			} else if (op3 == 0xd) { /* RTE */
				*next_pc = get_stack_long(child, PT_BPC);
				return;
			}
			break;
		case 0xc: /* JC */
			if (op3 == 0xc && check_condition_bit(child)) {
				regno = insn & 0xf;
				*next_pc = get_stack_long(child,
							  reg_offset[regno]);
				return;
			}
			break;
		case 0xd: /* JNC */
			if (op3 == 0xc && !check_condition_bit(child)) {
				regno = insn & 0xf;
				*next_pc = get_stack_long(child,
							  reg_offset[regno]);
				return;
			}
			break;
		case 0xe: /* JL */
		case 0xf: /* JMP */
			if (op3 == 0xc) { /* JMP */
				regno = insn & 0xf;
				*next_pc = get_stack_long(child,
							  reg_offset[regno]);
				return;
			}
			break;
		}
	}
	if (parallel)
		*next_pc = pc + 4;
	else
		*next_pc = pc + 2;
}