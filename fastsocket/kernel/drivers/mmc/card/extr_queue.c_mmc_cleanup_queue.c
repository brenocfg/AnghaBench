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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/ * queuedata; } ;
struct mmc_queue {int /*<<< orphan*/ * card; int /*<<< orphan*/ * bounce_buf; int /*<<< orphan*/ * sg; int /*<<< orphan*/ * bounce_sg; int /*<<< orphan*/  thread; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_start_queue (struct request_queue*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_queue_resume (struct mmc_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void mmc_cleanup_queue(struct mmc_queue *mq)
{
	struct request_queue *q = mq->queue;
	unsigned long flags;

	/* Make sure the queue isn't suspended, as that will deadlock */
	mmc_queue_resume(mq);

	/* Then terminate our worker thread */
	kthread_stop(mq->thread);

	/* Empty the queue */
	spin_lock_irqsave(q->queue_lock, flags);
	q->queuedata = NULL;
	blk_start_queue(q);
	spin_unlock_irqrestore(q->queue_lock, flags);

 	if (mq->bounce_sg)
 		kfree(mq->bounce_sg);
 	mq->bounce_sg = NULL;

	kfree(mq->sg);
	mq->sg = NULL;

	if (mq->bounce_buf)
		kfree(mq->bounce_buf);
	mq->bounce_buf = NULL;

	mq->card = NULL;
}