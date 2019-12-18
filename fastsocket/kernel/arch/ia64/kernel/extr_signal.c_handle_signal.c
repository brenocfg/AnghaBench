#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sigscratch {int /*<<< orphan*/  pt; } ;
struct TYPE_4__ {int sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct k_sigaction {TYPE_1__ sa; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_6__ {TYPE_2__* sighand; int /*<<< orphan*/  blocked; } ;
struct TYPE_5__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 scalar_t__ IS_IA32_PROCESS (int /*<<< orphan*/ *) ; 
 int SA_NODEFER ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  ia32_setup_frame1 (unsigned long,struct k_sigaction*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  setup_frame (unsigned long,struct k_sigaction*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sigscratch*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sigorsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_signal_handler (unsigned long,int /*<<< orphan*/ *,struct k_sigaction*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
handle_signal (unsigned long sig, struct k_sigaction *ka, siginfo_t *info, sigset_t *oldset,
	       struct sigscratch *scr)
{
	if (IS_IA32_PROCESS(&scr->pt)) {
		/* send signal to IA-32 process */
		if (!ia32_setup_frame1(sig, ka, info, oldset, &scr->pt))
			return 0;
	} else
		/* send signal to IA-64 process */
		if (!setup_frame(sig, ka, info, oldset, scr))
			return 0;

	spin_lock_irq(&current->sighand->siglock);
	sigorsets(&current->blocked, &current->blocked, &ka->sa.sa_mask);
	if (!(ka->sa.sa_flags & SA_NODEFER))
		sigaddset(&current->blocked, sig);
	recalc_sigpending();
	spin_unlock_irq(&current->sighand->siglock);

	/*
	 * Let tracing know that we've done the handler setup.
	 */
	tracehook_signal_handler(sig, info, ka, &scr->pt,
				 test_thread_flag(TIF_SINGLESTEP));

	return 1;
}