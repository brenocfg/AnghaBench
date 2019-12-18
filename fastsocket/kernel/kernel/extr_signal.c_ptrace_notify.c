#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int si_signo; int si_code; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; } ;
typedef  TYPE_2__ siginfo_t ;
struct TYPE_9__ {TYPE_1__* sighand; } ;
struct TYPE_7__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SIGTRAP ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptrace_stop (int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_vnr (TYPE_3__*) ; 

void ptrace_notify(int exit_code)
{
	siginfo_t info;

	BUG_ON((exit_code & (0x7f | ~0xffff)) != SIGTRAP);

	memset(&info, 0, sizeof info);
	info.si_signo = SIGTRAP;
	info.si_code = exit_code;
	info.si_pid = task_pid_vnr(current);
	info.si_uid = current_uid();

	/* Let the debugger run.  */
	spin_lock_irq(&current->sighand->siglock);
	ptrace_stop(exit_code, 1, &info);
	spin_unlock_irq(&current->sighand->siglock);
}