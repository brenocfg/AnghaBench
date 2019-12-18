#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_8__ {int si_signo; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; scalar_t__ si_errno; } ;
typedef  TYPE_1__ siginfo_t ;
struct TYPE_9__ {int exit_code; int /*<<< orphan*/  blocked; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int PT_PTRACED ; 
 int /*<<< orphan*/  SI_USER ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ptrace_signal_deliver (struct pt_regs*,void*) ; 
 int /*<<< orphan*/  ptrace_stop (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  specific_send_sig_info (int,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  task_pid_vnr (int /*<<< orphan*/ ) ; 
 int task_ptrace (TYPE_2__*) ; 
 int /*<<< orphan*/  task_uid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptrace_signal(int signr, siginfo_t *info,
			 struct pt_regs *regs, void *cookie)
{
	if (!(task_ptrace(current) & PT_PTRACED))
		return signr;

	ptrace_signal_deliver(regs, cookie);

	/* Let the debugger run.  */
	ptrace_stop(signr, 0, info);

	/* We're back.  Did the debugger cancel the sig?  */
	signr = current->exit_code;
	if (signr == 0)
		return signr;

	current->exit_code = 0;

	/* Update the siginfo structure if the signal has
	   changed.  If the debugger wanted something
	   specific in the siginfo structure then it should
	   have updated *info via PTRACE_SETSIGINFO.  */
	if (signr != info->si_signo) {
		info->si_signo = signr;
		info->si_errno = 0;
		info->si_code = SI_USER;
		info->si_pid = task_pid_vnr(current->parent);
		info->si_uid = task_uid(current->parent);
	}

	/* If the (new) signal is now blocked, requeue it.  */
	if (sigismember(&current->blocked, signr)) {
		specific_send_sig_info(signr, info, current);
		signr = 0;
	}

	return signr;
}