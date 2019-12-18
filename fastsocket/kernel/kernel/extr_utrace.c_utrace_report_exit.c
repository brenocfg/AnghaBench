#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct utrace {int dummy; } ;
struct task_struct {int dummy; } ;
struct TYPE_4__ {scalar_t__ action; int /*<<< orphan*/  resume_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT ; 
 int /*<<< orphan*/  INIT_REPORT (TYPE_1__) ; 
 int /*<<< orphan*/  REPORT (struct task_struct*,struct utrace*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long*) ; 
 int /*<<< orphan*/  UTRACE_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ UTRACE_STOP ; 
 struct task_struct* current ; 
 TYPE_1__ report ; 
 int /*<<< orphan*/  report_exit ; 
 struct utrace* task_utrace_struct (struct task_struct*) ; 
 int /*<<< orphan*/  utrace_stop (struct task_struct*,struct utrace*,int /*<<< orphan*/ ) ; 

void utrace_report_exit(long *exit_code)
{
	struct task_struct *task = current;
	struct utrace *utrace = task_utrace_struct(task);
	INIT_REPORT(report);
	long orig_code = *exit_code;

	REPORT(task, utrace, &report, UTRACE_EVENT(EXIT),
	       report_exit, orig_code, exit_code);

	if (report.action == UTRACE_STOP)
		utrace_stop(task, utrace, report.resume_action);
}