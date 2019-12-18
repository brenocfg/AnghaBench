#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {int flags; scalar_t__ group_stop_count; } ;

/* Variables and functions */
 int SIGNAL_STOP_STOPPED ; 
 int /*<<< orphan*/  TASK_STOPPED ; 
 int /*<<< orphan*/  __set_task_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_wake_up (struct task_struct*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ task_is_traced (struct task_struct*) ; 

__attribute__((used)) static void ptrace_untrace(struct task_struct *child)
{
	spin_lock(&child->sighand->siglock);
	if (task_is_traced(child)) {
		/*
		 * If the group stop is completed or in progress,
		 * this thread was already counted as stopped.
		 */
		if (child->signal->flags & SIGNAL_STOP_STOPPED ||
		    child->signal->group_stop_count)
			__set_task_state(child, TASK_STOPPED);
		else
			signal_wake_up(child, 1);
	}
	spin_unlock(&child->sighand->siglock);
}