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
struct bsg_device {scalar_t__ done_cmds; scalar_t__ queued_cmds; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq_done; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSG_F_BLOCK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENODATA ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int bsg_io_schedule(struct bsg_device *bd)
{
	DEFINE_WAIT(wait);
	int ret = 0;

	spin_lock_irq(&bd->lock);

	BUG_ON(bd->done_cmds > bd->queued_cmds);

	/*
	 * -ENOSPC or -ENODATA?  I'm going for -ENODATA, meaning "I have no
	 * work to do", even though we return -ENOSPC after this same test
	 * during bsg_write() -- there, it means our buffer can't have more
	 * bsg_commands added to it, thus has no space left.
	 */
	if (bd->done_cmds == bd->queued_cmds) {
		ret = -ENODATA;
		goto unlock;
	}

	if (!test_bit(BSG_F_BLOCK, &bd->flags)) {
		ret = -EAGAIN;
		goto unlock;
	}

	prepare_to_wait(&bd->wq_done, &wait, TASK_UNINTERRUPTIBLE);
	spin_unlock_irq(&bd->lock);
	io_schedule();
	finish_wait(&bd->wq_done, &wait);

	return ret;
unlock:
	spin_unlock_irq(&bd->lock);
	return ret;
}