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
 int /*<<< orphan*/  PT_ERP ; 
 int /*<<< orphan*/  PT_SPC ; 
 unsigned long get_reg (struct task_struct*,int /*<<< orphan*/ ) ; 
 int insn_size (struct task_struct*,unsigned long) ; 

__attribute__((used)) static unsigned long get_pseudo_pc(struct task_struct *child)
{
	/* Default value for PC is ERP. */
	unsigned long pc = get_reg(child, PT_ERP);

	if (pc & 0x1) {
		unsigned long spc = get_reg(child, PT_SPC);
		/* Delay slot bit set. Report as stopped on proper
		   instruction. */
		if (spc) {
			/* Rely on SPC if set. FIXME: We might want to check
			   that EXS indicates we stopped due to a single-step
			   exception. */
			pc = spc;
		} else {
			/* Calculate the PC from the size of the instruction
			   that the delay slot we're in belongs to. */
			pc += insn_size(child, pc & ~1) - 1;
		}
	}
	return pc;
}