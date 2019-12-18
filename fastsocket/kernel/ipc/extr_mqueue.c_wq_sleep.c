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
struct mqueue_inode_info {int /*<<< orphan*/  lock; } ;
struct ext_wait_queue {scalar_t__ state; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 scalar_t__ STATE_PENDING ; 
 scalar_t__ STATE_READY ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq_add (struct mqueue_inode_info*,int,struct ext_wait_queue*) ; 

__attribute__((used)) static int wq_sleep(struct mqueue_inode_info *info, int sr,
			long timeout, struct ext_wait_queue *ewp)
{
	int retval;
	signed long time;

	wq_add(info, sr, ewp);

	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);

		spin_unlock(&info->lock);
		time = schedule_timeout(timeout);

		while (ewp->state == STATE_PENDING)
			cpu_relax();

		if (ewp->state == STATE_READY) {
			retval = 0;
			goto out;
		}
		spin_lock(&info->lock);
		if (ewp->state == STATE_READY) {
			retval = 0;
			goto out_unlock;
		}
		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		}
		if (time == 0) {
			retval = -ETIMEDOUT;
			break;
		}
	}
	list_del(&ewp->list);
out_unlock:
	spin_unlock(&info->lock);
out:
	return retval;
}