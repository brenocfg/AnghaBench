#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_mask; scalar_t__ sa_handler; } ;
struct k_sigaction {int flags; int /*<<< orphan*/  mask; scalar_t__ handler; int /*<<< orphan*/  restorer; } ;
struct TYPE_2__ {int /*<<< orphan*/  threaded; } ;

/* Variables and functions */
 int SA_RESTORER ; 
 int SA_SIGINFO ; 
 int /*<<< orphan*/  SIGPT_SET ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  SYS_rt_sigaction ; 
 int /*<<< orphan*/  SYS_rt_sigprocmask ; 
 int _NSIG ; 
 int /*<<< orphan*/  __restore ; 
 int /*<<< orphan*/  __restore_rt ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  a_or_l (scalar_t__,unsigned long) ; 
 scalar_t__ handler_set ; 
 TYPE_1__ libc ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int,struct k_sigaction*,struct k_sigaction*,int) ; 
 int unmask_done ; 

int __libc_sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
	struct k_sigaction ksa, ksa_old;
	if (sa) {
		if ((uintptr_t)sa->sa_handler > 1UL) {
			a_or_l(handler_set+(sig-1)/(8*sizeof(long)),
				1UL<<(sig-1)%(8*sizeof(long)));

			/* If pthread_create has not yet been called,
			 * implementation-internal signals might not
			 * yet have been unblocked. They must be
			 * unblocked before any signal handler is
			 * installed, so that an application cannot
			 * receive an illegal sigset_t (with them
			 * blocked) as part of the ucontext_t passed
			 * to the signal handler. */
			if (!libc.threaded && !unmask_done) {
				__syscall(SYS_rt_sigprocmask, SIG_UNBLOCK,
					SIGPT_SET, 0, _NSIG/8);
				unmask_done = 1;
			}
		}
		ksa.handler = sa->sa_handler;
		ksa.flags = sa->sa_flags | SA_RESTORER;
		ksa.restorer = (sa->sa_flags & SA_SIGINFO) ? __restore_rt : __restore;
		memcpy(&ksa.mask, &sa->sa_mask, sizeof ksa.mask);
	}
	if (syscall(SYS_rt_sigaction, sig, sa?&ksa:0, old?&ksa_old:0, sizeof ksa.mask))
		return -1;
	if (old) {
		old->sa_handler = ksa_old.handler;
		old->sa_flags = ksa_old.flags;
		memcpy(&old->sa_mask, &ksa_old.mask, sizeof ksa_old.mask);
	}
	return 0;
}