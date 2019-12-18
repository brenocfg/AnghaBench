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
struct task_struct {int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  sr; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_BREAKPOINT ; 
 int /*<<< orphan*/  TIF_SINGLE_STEP ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 TYPE_1__* task_pt_regs (struct task_struct*) ; 

__attribute__((used)) static void ptrace_single_step(struct task_struct *tsk)
{
	pr_debug("ptrace_single_step: pid=%u, PC=0x%08lx, SR=0x%08lx\n",
		 tsk->pid, task_pt_regs(tsk)->pc, task_pt_regs(tsk)->sr);

	/*
	 * We can't schedule in Debug mode, so when TIF_BREAKPOINT is
	 * set, the system call or exception handler will do a
	 * breakpoint to enter monitor mode before returning to
	 * userspace.
	 *
	 * The monitor code will then notice that TIF_SINGLE_STEP is
	 * set and return to userspace with single stepping enabled.
	 * The CPU will then enter monitor mode again after exactly
	 * one instruction has been executed, and the monitor code
	 * will then send a SIGTRAP to the process.
	 */
	set_tsk_thread_flag(tsk, TIF_BREAKPOINT);
	set_tsk_thread_flag(tsk, TIF_SINGLE_STEP);
}