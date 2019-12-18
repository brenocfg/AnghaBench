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
struct request_queue {scalar_t__ elevator; int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  __queue_lock; int /*<<< orphan*/ * queue_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_DEAD ; 
 int /*<<< orphan*/  QUEUE_FLAG_NOMERGES ; 
 int /*<<< orphan*/  blk_drain_queue (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_sync_queue (struct request_queue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void blk_cleanup_queue(struct request_queue *q)
{
	spinlock_t *lock = q->queue_lock;

	/* mark @q DEAD, no new request or merges will be allowed afterwards */
	mutex_lock(&q->sysfs_lock);
	queue_flag_set_unlocked(QUEUE_FLAG_DEAD, q);

	spin_lock_irq(lock);
	queue_flag_set(QUEUE_FLAG_NOMERGES, q);
	queue_flag_set(QUEUE_FLAG_DEAD, q);

	if (q->queue_lock != &q->__queue_lock)
		q->queue_lock = &q->__queue_lock;

	spin_unlock_irq(lock);
	mutex_unlock(&q->sysfs_lock);

	/*
	 * Drain all requests queued before DEAD marking.  The caller might
	 * be trying to tear down @q before its elevator is initialized, in
	 * which case we don't want to call into draining.
	 */
	if (q->elevator)
		blk_drain_queue(q, true);

	/* @q won't process any more reuqest, flush async actions */
	blk_sync_queue(q);

	/* @q is and will stay empty, shutdown and put */
	blk_put_queue(q);
}