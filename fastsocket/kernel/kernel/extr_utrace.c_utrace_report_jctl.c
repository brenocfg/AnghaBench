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
struct utrace {int dummy; } ;
struct task_struct {TYPE_1__* sighand; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_REPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JCTL ; 
 int /*<<< orphan*/  REPORT (struct task_struct*,struct utrace*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UTRACE_EVENT (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  report ; 
 int /*<<< orphan*/  report_jctl ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct utrace* task_utrace_struct (struct task_struct*) ; 

void utrace_report_jctl(int notify, int what)
{
	struct task_struct *task = current;
	struct utrace *utrace = task_utrace_struct(task);
	INIT_REPORT(report);

	spin_unlock_irq(&task->sighand->siglock);

	REPORT(task, utrace, &report, UTRACE_EVENT(JCTL),
	       report_jctl, what, notify);

	spin_lock_irq(&task->sighand->siglock);
}