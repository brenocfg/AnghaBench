#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  ss_sp; scalar_t__ ss_size; int /*<<< orphan*/  ss_flags; } ;
struct uthread {int uu_siglist; int /*<<< orphan*/  uu_flag; TYPE_1__ uu_sigstk; } ;
struct sigacts {scalar_t__ ps_sigonstack; int /*<<< orphan*/  ps_sigreturn_token; int /*<<< orphan*/  ps_sigreturn_validation; int /*<<< orphan*/ * ps_sigact; } ;
typedef  TYPE_2__* proc_t ;
struct TYPE_5__ {int p_siglist; int p_sigcatch; int p_sigignore; struct sigacts* p_sigacts; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_SIGRETURN_VALIDATION_DEFAULT ; 
 int /*<<< orphan*/  SA_DISABLE ; 
 int SA_IGNORE ; 
 int SIGCONT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int /*<<< orphan*/  UT_ALTSTACK ; 
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffs (long) ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  read_random (int /*<<< orphan*/ *,int) ; 
 int sigmask (int) ; 
 int* sigprop ; 

void
execsigs(proc_t p, thread_t thread)
{
	struct sigacts *ps = p->p_sigacts;
	int nc, mask;
	struct uthread *ut;

	ut = (struct uthread *)get_bsdthread_info(thread);

	/*
	 * transfer saved signal states from the process
	 * back to the current thread.
	 *
	 * NOTE: We do this without the process locked,
	 * because we are guaranteed to be single-threaded
	 * by this point in exec and the p_siglist is
	 * only accessed by threads inside the process.
	 */
	ut->uu_siglist |= p->p_siglist;
	p->p_siglist = 0;

	/*
	 * Reset caught signals.  Held signals remain held
	 * through p_sigmask (unless they were caught,
	 * and are now ignored by default).
	 */
	while (p->p_sigcatch) {
		nc = ffs((long)p->p_sigcatch);
		mask = sigmask(nc);
		p->p_sigcatch &= ~mask;
		if (sigprop[nc] & SA_IGNORE) {
			if (nc != SIGCONT)
				p->p_sigignore |= mask;
			ut->uu_siglist &= ~mask;
		}
		ps->ps_sigact[nc] = SIG_DFL;
	}

	atomic_store_explicit(&ps->ps_sigreturn_validation,
			PS_SIGRETURN_VALIDATION_DEFAULT, memory_order_relaxed);
	/* Generate random token value used to validate sigreturn arguments */
	read_random(&ps->ps_sigreturn_token, sizeof(ps->ps_sigreturn_token));

	/*
	 * Reset stack state to the user stack.
	 * Clear set of signals caught on the signal stack.
	 */
	/* thread */
	ut->uu_sigstk.ss_flags = SA_DISABLE;
	ut->uu_sigstk.ss_size = 0;
	ut->uu_sigstk.ss_sp = USER_ADDR_NULL;
	ut->uu_flag &= ~UT_ALTSTACK;
	/* process */
	ps->ps_sigonstack = 0;
}