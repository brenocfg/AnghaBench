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
struct utrace {int /*<<< orphan*/  lock; } ;
struct task_struct {TYPE_1__* sighand; int /*<<< orphan*/  state; TYPE_2__* signal; } ;
struct TYPE_4__ {int flags; scalar_t__ group_stop_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int SIGNAL_STOP_STOPPED ; 
 int /*<<< orphan*/  TASK_STOPPED ; 
 int /*<<< orphan*/  __TASK_TRACED ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void utrace_wakeup(struct task_struct *target, struct utrace *utrace)
{
	lockdep_assert_held(&utrace->lock);
	spin_lock_irq(&target->sighand->siglock);
	if (target->signal->flags & SIGNAL_STOP_STOPPED ||
	    target->signal->group_stop_count)
		target->state = TASK_STOPPED;
	else
		wake_up_state(target, __TASK_TRACED);
	spin_unlock_irq(&target->sighand->siglock);
}