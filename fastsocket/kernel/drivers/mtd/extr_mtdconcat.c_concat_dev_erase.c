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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct mtd_info {int (* erase ) (struct mtd_info*,struct erase_info*) ;} ;
struct erase_info {unsigned long priv; scalar_t__ state; int /*<<< orphan*/  callback; struct mtd_info* mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ MTD_ERASE_DONE ; 
 scalar_t__ MTD_ERASE_FAILED ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  concat_erase_callback ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int stub1 (struct mtd_info*,struct erase_info*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int concat_dev_erase(struct mtd_info *mtd, struct erase_info *erase)
{
	int err;
	wait_queue_head_t waitq;
	DECLARE_WAITQUEUE(wait, current);

	/*
	 * This code was stol^H^H^H^Hinspired by mtdchar.c
	 */
	init_waitqueue_head(&waitq);

	erase->mtd = mtd;
	erase->callback = concat_erase_callback;
	erase->priv = (unsigned long) &waitq;

	/*
	 * FIXME: Allow INTERRUPTIBLE. Which means
	 * not having the wait_queue head on the stack.
	 */
	err = mtd->erase(mtd, erase);
	if (!err) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_wait_queue(&waitq, &wait);
		if (erase->state != MTD_ERASE_DONE
		    && erase->state != MTD_ERASE_FAILED)
			schedule();
		remove_wait_queue(&waitq, &wait);
		set_current_state(TASK_RUNNING);

		err = (erase->state == MTD_ERASE_FAILED) ? -EIO : 0;
	}
	return err;
}