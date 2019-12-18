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
struct utrace {scalar_t__ resume; } ;
struct task_struct {TYPE_1__* sighand; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_TRACED ; 
 scalar_t__ UTRACE_REPORT ; 
 int /*<<< orphan*/  __set_task_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  set_notify_resume (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ task_is_stopped (struct task_struct*) ; 
 int task_is_traced (struct task_struct*) ; 

__attribute__((used)) static bool utrace_do_stop(struct task_struct *target, struct utrace *utrace)
{
	if (task_is_stopped(target)) {
		/*
		 * Stopped is considered quiescent; when it wakes up, it will
		 * go through utrace_finish_stop() before doing anything else.
		 */
		spin_lock_irq(&target->sighand->siglock);
		if (likely(task_is_stopped(target)))
			__set_task_state(target, TASK_TRACED);
		spin_unlock_irq(&target->sighand->siglock);
	} else if (utrace->resume > UTRACE_REPORT) {
		utrace->resume = UTRACE_REPORT;
		set_notify_resume(target);
	}

	return task_is_traced(target);
}