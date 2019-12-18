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
struct ktstate {int (* fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  rendez; int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PF_NOFREEZE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_user_nice (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int
kthread(void *vp)
{
	struct ktstate *k;
	DECLARE_WAITQUEUE(wait, current);
	int more;

	k = vp;
	current->flags |= PF_NOFREEZE;
	set_user_nice(current, -10);
	complete(&k->rendez);	/* tell spawner we're running */
	do {
		spin_lock_irq(k->lock);
		more = k->fn(k->id);
		if (!more) {
			add_wait_queue(k->waitq, &wait);
			__set_current_state(TASK_INTERRUPTIBLE);
		}
		spin_unlock_irq(k->lock);
		if (!more) {
			schedule();
			remove_wait_queue(k->waitq, &wait);
		} else
			cond_resched();
	} while (!kthread_should_stop());
	complete(&k->rendez);	/* tell spawner we're stopping */
	return 0;
}