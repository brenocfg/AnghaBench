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
struct task_struct {int ptrace; scalar_t__ parent; TYPE_1__* sighand; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int ESRCH ; 
 int PT_PTRACED ; 
 int /*<<< orphan*/  TASK_TRACED ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ task_is_stopped (struct task_struct*) ; 
 int /*<<< orphan*/  task_is_traced (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ wait_task_inactive (struct task_struct*,int /*<<< orphan*/ ) ; 

int ptrace_check_attach(struct task_struct *child, int kill)
{
	int ret = -ESRCH;

	/*
	 * We take the read lock around doing both checks to close a
	 * possible race where someone else was tracing our child and
	 * detached between these two checks.  After this locked check,
	 * we are sure that this is our traced child and that can only
	 * be changed by us so it's not changing right after this.
	 */
	read_lock(&tasklist_lock);
	if ((child->ptrace & PT_PTRACED) && child->parent == current) {
		ret = 0;
		/*
		 * child->sighand can't be NULL, release_task()
		 * does ptrace_unlink() before __exit_signal().
		 */
		spin_lock_irq(&child->sighand->siglock);
		if (task_is_stopped(child))
			child->state = TASK_TRACED;
		else if (!task_is_traced(child) && !kill)
			ret = -ESRCH;
		spin_unlock_irq(&child->sighand->siglock);
	}
	read_unlock(&tasklist_lock);

	if (!ret && !kill)
		ret = wait_task_inactive(child, TASK_TRACED) ? 0 : -ESRCH;

	/* All systems go.. */
	return ret;
}