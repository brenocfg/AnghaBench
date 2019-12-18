#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ptrace_context {int signr; TYPE_2__* siginfo; } ;
struct k_sigaction {int dummy; } ;
struct TYPE_7__ {int si_signo; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; scalar_t__ si_errno; } ;
typedef  TYPE_2__ siginfo_t ;
typedef  enum utrace_signal_action { ____Placeholder_utrace_signal_action } utrace_signal_action ;
struct TYPE_8__ {TYPE_1__* sighand; int /*<<< orphan*/  blocked; int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  siglock; struct k_sigaction* action; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI_USER ; 
 int UTRACE_SIGNAL_DELIVER ; 
 int UTRACE_SIGNAL_IGN ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  send_sig_info (int,TYPE_2__*,TYPE_4__*) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_vnr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_uid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum utrace_signal_action resume_signal(struct ptrace_context *ctx,
					       struct k_sigaction *return_ka)
{
	siginfo_t *info = ctx->siginfo;
	int signr = ctx->signr;

	ctx->siginfo = NULL;
	ctx->signr = 0;

	/* Did the debugger cancel the sig? */
	if (!signr)
		return UTRACE_SIGNAL_IGN;
	/*
	 * Update the siginfo structure if the signal has changed.
	 * If the debugger wanted something specific in the siginfo
	 * then it should have updated *info via PTRACE_SETSIGINFO.
	 */
	if (info->si_signo != signr) {
		info->si_signo = signr;
		info->si_errno = 0;
		info->si_code = SI_USER;
		info->si_pid = task_pid_vnr(current->parent);
		info->si_uid = task_uid(current->parent);
	}

	/* If the (new) signal is now blocked, requeue it. */
	if (sigismember(&current->blocked, signr)) {
		send_sig_info(signr, info, current);
		return UTRACE_SIGNAL_IGN;
	}

	spin_lock_irq(&current->sighand->siglock);
	*return_ka = current->sighand->action[signr - 1];
	spin_unlock_irq(&current->sighand->siglock);

	return UTRACE_SIGNAL_DELIVER;
}