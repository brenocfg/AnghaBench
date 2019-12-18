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
struct multipath {int /*<<< orphan*/  pg_init_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  pg_init_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void multipath_wait_for_pg_init_completion(struct multipath *m)
{
	DECLARE_WAITQUEUE(wait, current);
	unsigned long flags;

	add_wait_queue(&m->pg_init_wait, &wait);

	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);

		spin_lock_irqsave(&m->lock, flags);
		if (!m->pg_init_in_progress) {
			spin_unlock_irqrestore(&m->lock, flags);
			break;
		}
		spin_unlock_irqrestore(&m->lock, flags);

		io_schedule();
	}
	set_current_state(TASK_RUNNING);

	remove_wait_queue(&m->pg_init_wait, &wait);
}