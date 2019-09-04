#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct TYPE_6__ {int t_flags; } ;

/* Variables and functions */
 int TF_LRETURNWAIT ; 
 int TF_LRETURNWAITER ; 
 int /*<<< orphan*/  task_get_return_wait_event (TYPE_1__*) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

void
task_clear_return_wait(task_t task)
{
	task_lock(task);

	task->t_flags &= ~TF_LRETURNWAIT;

	if (task->t_flags & TF_LRETURNWAITER) {
		thread_wakeup(task_get_return_wait_event(task));
		task->t_flags &= ~TF_LRETURNWAITER;
	}

	task_unlock(task);
}