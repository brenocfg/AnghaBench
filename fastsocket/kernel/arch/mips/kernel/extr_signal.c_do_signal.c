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
struct pt_regs {scalar_t__* regs; int cp0_epc; } ;
struct k_sigaction {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_5__ {TYPE_1__* abi; } ;
struct TYPE_6__ {int /*<<< orphan*/  saved_sigmask; TYPE_2__ thread; int /*<<< orphan*/  blocked; } ;
struct TYPE_4__ {scalar_t__ restart; } ;

/* Variables and functions */
 scalar_t__ ERESTARTNOHAND ; 
 scalar_t__ ERESTARTNOINTR ; 
 scalar_t__ ERESTARTSYS ; 
 scalar_t__ ERESTART_RESTARTBLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TIF_RESTORE_SIGMASK ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int get_signal_to_deliver (int /*<<< orphan*/ *,struct k_sigaction*,struct pt_regs*,int /*<<< orphan*/ *) ; 
 scalar_t__ handle_signal (int,int /*<<< orphan*/ *,struct k_sigaction*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static void do_signal(struct pt_regs *regs)
{
	struct k_sigaction ka;
	sigset_t *oldset;
	siginfo_t info;
	int signr;

	/*
	 * We want the common case to go fast, which is why we may in certain
	 * cases get here from kernel mode. Just return without doing anything
	 * if so.
	 */
	if (!user_mode(regs))
		return;

	if (test_thread_flag(TIF_RESTORE_SIGMASK))
		oldset = &current->saved_sigmask;
	else
		oldset = &current->blocked;

	signr = get_signal_to_deliver(&info, &ka, regs, NULL);
	if (signr > 0) {
		/* Whee!  Actually deliver the signal.  */
		if (handle_signal(signr, &info, &ka, oldset, regs) == 0) {
			/*
			 * A signal was successfully delivered; the saved
			 * sigmask will have been stored in the signal frame,
			 * and will be restored by sigreturn, so we can simply
			 * clear the TIF_RESTORE_SIGMASK flag.
			 */
			if (test_thread_flag(TIF_RESTORE_SIGMASK))
				clear_thread_flag(TIF_RESTORE_SIGMASK);
		}

		return;
	}

	/*
	 * Who's code doesn't conform to the restartable syscall convention
	 * dies here!!!  The li instruction, a single machine instruction,
	 * must directly be followed by the syscall instruction.
	 */
	if (regs->regs[0]) {
		if (regs->regs[2] == ERESTARTNOHAND ||
		    regs->regs[2] == ERESTARTSYS ||
		    regs->regs[2] == ERESTARTNOINTR) {
			regs->regs[7] = regs->regs[26];
			regs->cp0_epc -= 8;
		}
		if (regs->regs[2] == ERESTART_RESTARTBLOCK) {
			regs->regs[2] = current->thread.abi->restart;
			regs->regs[7] = regs->regs[26];
			regs->cp0_epc -= 4;
		}
		regs->regs[0] = 0;	/* Don't deal with this again.  */
	}

	/*
	 * If there's no signal to deliver, we just put the saved sigmask
	 * back
	 */
	if (test_thread_flag(TIF_RESTORE_SIGMASK)) {
		clear_thread_flag(TIF_RESTORE_SIGMASK);
		sigprocmask(SIG_SETMASK, &current->saved_sigmask, NULL);
	}
}