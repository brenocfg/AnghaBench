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
struct utrace {int dummy; } ;
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_REPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPORT (struct task_struct*,struct utrace*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  SYSCALL_EXIT ; 
 int /*<<< orphan*/  UTRACE_EVENT (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  report ; 
 int /*<<< orphan*/  report_syscall_exit ; 
 struct utrace* task_utrace_struct (struct task_struct*) ; 

void utrace_report_syscall_exit(struct pt_regs *regs)
{
	struct task_struct *task = current;
	struct utrace *utrace = task_utrace_struct(task);
	INIT_REPORT(report);

	REPORT(task, utrace, &report, UTRACE_EVENT(SYSCALL_EXIT),
	       report_syscall_exit, regs);
}