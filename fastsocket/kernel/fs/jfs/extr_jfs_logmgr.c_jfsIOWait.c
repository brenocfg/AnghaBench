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
struct lbuf {struct lbuf* l_redrive_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_info (char*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  lbmStartIO (struct lbuf*) ; 
 struct lbuf* log_redrive_list ; 
 int /*<<< orphan*/  log_redrive_lock ; 
 int /*<<< orphan*/  refrigerator () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int jfsIOWait(void *arg)
{
	struct lbuf *bp;

	do {
		spin_lock_irq(&log_redrive_lock);
		while ((bp = log_redrive_list)) {
			log_redrive_list = bp->l_redrive_next;
			bp->l_redrive_next = NULL;
			spin_unlock_irq(&log_redrive_lock);
			lbmStartIO(bp);
			spin_lock_irq(&log_redrive_lock);
		}

		if (freezing(current)) {
			spin_unlock_irq(&log_redrive_lock);
			refrigerator();
		} else {
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&log_redrive_lock);
			schedule();
			__set_current_state(TASK_RUNNING);
		}
	} while (!kthread_should_stop());

	jfs_info("jfsIOWait being killed!");
	return 0;
}