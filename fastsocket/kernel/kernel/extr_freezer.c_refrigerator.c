#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {long state; int /*<<< orphan*/  comm; int /*<<< orphan*/  flags; TYPE_1__* sighand; } ;
struct TYPE_7__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_FREEZING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (long) ; 
 TYPE_2__* current ; 
 scalar_t__ freezing (TYPE_2__*) ; 
 int /*<<< orphan*/  frozen (TYPE_2__*) ; 
 int /*<<< orphan*/  frozen_process () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 

void refrigerator(void)
{
	/* Hmm, should we be allowed to suspend when there are realtime
	   processes around? */
	long save;

	task_lock(current);
	if (freezing(current)) {
		frozen_process();
		task_unlock(current);
	} else {
		task_unlock(current);
		return;
	}
	save = current->state;
	pr_debug("%s entered refrigerator\n", current->comm);

	spin_lock_irq(&current->sighand->siglock);
	recalc_sigpending(); /* We sent fake signal, clean it up */
	spin_unlock_irq(&current->sighand->siglock);

	/* prevent accounting of that task to load */
	current->flags |= PF_FREEZING;

	for (;;) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		if (!frozen(current))
			break;
		schedule();
	}

	/* Remove the accounting blocker */
	current->flags &= ~PF_FREEZING;

	pr_debug("%s left refrigerator\n", current->comm);
	__set_current_state(save);
}