#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regs {scalar_t__ r_pc; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_rax; } ;
struct TYPE_4__ {size_t t_dtrace_npc; size_t t_dtrace_pc; int t_dtrace_on; scalar_t__ t_dtrace_scrpc; scalar_t__ t_dtrace_astpc; int t_dtrace_reg; int t_dtrace_step; int t_dtrace_ast; scalar_t__ t_dtrace_ft; int /*<<< orphan*/  t_dtrace_regv; } ;
typedef  TYPE_1__ kthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  REG_R8 131 
#define  REG_R9 130 
#define  REG_RAX 129 
#define  REG_RCX 128 
 TYPE_1__* curthread ; 
 struct regs* lwptoregs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttolwp (TYPE_1__*) ; 

int
dtrace_safe_defer_signal(void)
{
#if 0
	kthread_t *t = curthread;
	struct regs *rp = lwptoregs(ttolwp(t));
	size_t isz = t->t_dtrace_npc - t->t_dtrace_pc;

	ASSERT(t->t_dtrace_on);

	/*
	 * If we're not in the range of scratch addresses, we're not actually
	 * tracing user instructions so turn off the flags.
	 */
	if (rp->r_pc < t->t_dtrace_scrpc ||
			rp->r_pc > t->t_dtrace_astpc + isz) {
		t->t_dtrace_ft = 0;
		return (0);
	}

	/*
	 * If we've executed the original instruction, but haven't performed
	 * the jmp back to t->t_dtrace_npc or the clean up of any registers
	 * used to emulate %rip-relative instructions in 64-bit mode, do that
	 * here and take the signal right away. We detect this condition by
	 * seeing if the program counter is the range [scrpc + isz, astpc).
	 */
	if (t->t_dtrace_astpc - rp->r_pc <
			t->t_dtrace_astpc - t->t_dtrace_scrpc - isz) {
#ifdef __sol64
		/*
		 * If there is a scratch register and we're on the
		 * instruction immediately after the modified instruction,
		 * restore the value of that scratch register.
		 */
		if (t->t_dtrace_reg != 0 &&
				rp->r_pc == t->t_dtrace_scrpc + isz) {
			switch (t->t_dtrace_reg) {
				case REG_RAX:
					rp->r_rax = t->t_dtrace_regv;
					break;
				case REG_RCX:
					rp->r_rcx = t->t_dtrace_regv;
					break;
				case REG_R8:
					rp->r_r8 = t->t_dtrace_regv;
					break;
				case REG_R9:
					rp->r_r9 = t->t_dtrace_regv;
					break;
			}
		}
#endif
		rp->r_pc = t->t_dtrace_npc;
		t->t_dtrace_ft = 0;
		return (0);
	}

	/*
	 * Otherwise, make sure we'll return to the kernel after executing
	 * the copied out instruction and defer the signal.
	 */
	if (!t->t_dtrace_step) {
		ASSERT(rp->r_pc < t->t_dtrace_astpc);
		rp->r_pc += t->t_dtrace_astpc - t->t_dtrace_scrpc;
		t->t_dtrace_step = 1;
	}

	t->t_dtrace_ast = 1;

	return (1);

#endif /* 0 */

	return 0;
}