#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct utrace_report {int result; int action; int resume_action; int detaches; int spurious; } ;
struct utrace {scalar_t__ resume; } ;
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_CALLBACKS (int /*<<< orphan*/ ,struct task_struct*,struct utrace*,struct utrace_report*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  SYSCALL_ENTRY ; 
 int /*<<< orphan*/  UTRACE_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ UTRACE_REPORT ; 
 int UTRACE_RESUME ; 
 int UTRACE_STOP ; 
 int UTRACE_SYSCALL_ABORT ; 
 int UTRACE_SYSCALL_RESUMED ; 
 int /*<<< orphan*/  _reverse ; 
 int /*<<< orphan*/  engine ; 
 scalar_t__ fatal_signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  finish_report (struct task_struct*,struct utrace*,struct utrace_report*,int) ; 
 int /*<<< orphan*/  report_syscall_entry ; 
 int /*<<< orphan*/  start_report (struct utrace*) ; 
 int /*<<< orphan*/  utrace_stop (struct task_struct*,struct utrace*,int) ; 

__attribute__((used)) static u32 do_report_syscall_entry(struct pt_regs *regs,
				   struct task_struct *task,
				   struct utrace *utrace,
				   struct utrace_report *report,
				   u32 resume_report)
{
	start_report(utrace);
	REPORT_CALLBACKS(_reverse, task, utrace, report,
			 UTRACE_EVENT(SYSCALL_ENTRY), report_syscall_entry,
			 resume_report | report->result | report->action,
			 engine, regs);
	finish_report(task, utrace, report, false);

	if (report->action != UTRACE_STOP)
		return 0;

	utrace_stop(task, utrace, report->resume_action);

	if (fatal_signal_pending(task)) {
		/*
		 * We are continuing despite UTRACE_STOP because of a
		 * SIGKILL.  Don't let the system call actually proceed.
		 */
		report->result = UTRACE_SYSCALL_ABORT;
	} else if (utrace->resume <= UTRACE_REPORT) {
		/*
		 * If we've been asked for another report after our stop,
		 * go back to report (and maybe stop) again before we run
		 * the system call.  The second (and later) reports are
		 * marked with the UTRACE_SYSCALL_RESUMED flag so that
		 * engines know this is a second report at the same
		 * entry.  This gives them the chance to examine the
		 * registers anew after they might have been changed
		 * while we were stopped.
		 */
		report->detaches = false;
		report->spurious = true;
		report->action = report->resume_action = UTRACE_RESUME;
		return UTRACE_SYSCALL_RESUMED;
	}

	return 0;
}