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
struct utrace_report {int action; } ;
struct utrace {int resume; int /*<<< orphan*/  lock; } ;
struct task_struct {int dummy; } ;
typedef  enum utrace_resume_action { ____Placeholder_utrace_resume_action } utrace_resume_action ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int UTRACE_INTERRUPT ; 
 int UTRACE_REPORT ; 
 int UTRACE_RESUME ; 
 int UTRACE_STOP ; 
 int /*<<< orphan*/  finish_report_reset (struct task_struct*,struct utrace*,struct utrace_report*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void finish_report(struct task_struct *task, struct utrace *utrace,
			  struct utrace_report *report, bool will_not_stop)
{
	enum utrace_resume_action resume = report->action;

	if (resume == UTRACE_STOP)
		resume = will_not_stop ? UTRACE_REPORT : UTRACE_RESUME;

	if (resume < utrace->resume) {
		spin_lock(&utrace->lock);
		utrace->resume = resume;
		if (resume == UTRACE_INTERRUPT)
			set_tsk_thread_flag(task, TIF_SIGPENDING);
		else
			set_tsk_thread_flag(task, TIF_NOTIFY_RESUME);
		spin_unlock(&utrace->lock);
	}

	finish_report_reset(task, utrace, report);
}