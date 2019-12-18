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
struct regs {scalar_t__ r_pc; } ;
struct TYPE_4__ {size_t t_dtrace_npc; size_t t_dtrace_pc; scalar_t__ t_dtrace_scrpc; scalar_t__ t_dtrace_astpc; scalar_t__ t_dtrace_ft; int /*<<< orphan*/  t_dtrace_on; } ;
typedef  TYPE_1__ kthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 struct regs* lwptoregs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttolwp (TYPE_1__*) ; 

void
dtrace_safe_synchronous_signal(void)
{
#if 0
	kthread_t *t = curthread;
	struct regs *rp = lwptoregs(ttolwp(t));
	size_t isz = t->t_dtrace_npc - t->t_dtrace_pc;

	ASSERT(t->t_dtrace_on);

	/*
	 * If we're not in the range of scratch addresses, we're not actually
	 * tracing user instructions so turn off the flags. If the instruction
	 * we copied out caused a synchonous trap, reset the pc back to its
	 * original value and turn off the flags.
	 */
	if (rp->r_pc < t->t_dtrace_scrpc ||
			rp->r_pc > t->t_dtrace_astpc + isz) {
		t->t_dtrace_ft = 0;
	} else if (rp->r_pc == t->t_dtrace_scrpc ||
			rp->r_pc == t->t_dtrace_astpc) {
		rp->r_pc = t->t_dtrace_pc;
		t->t_dtrace_ft = 0;
	}
#endif /* 0 */
}