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
struct request_queue {struct omap_mbox* queuedata; } ;
struct omap_mbox_queue {int /*<<< orphan*/  work; struct request_queue* queue; int /*<<< orphan*/  lock; } ;
struct omap_mbox {int dummy; } ;
typedef  int /*<<< orphan*/  request_fn_proc ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 struct request_queue* blk_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct omap_mbox_queue*) ; 
 struct omap_mbox_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct omap_mbox_queue *mbox_queue_alloc(struct omap_mbox *mbox,
					request_fn_proc * proc,
					void (*work) (struct work_struct *))
{
	struct request_queue *q;
	struct omap_mbox_queue *mq;

	mq = kzalloc(sizeof(struct omap_mbox_queue), GFP_KERNEL);
	if (!mq)
		return NULL;

	spin_lock_init(&mq->lock);

	q = blk_init_queue(proc, &mq->lock);
	if (!q)
		goto error;
	q->queuedata = mbox;
	mq->queue = q;

	INIT_WORK(&mq->work, work);

	return mq;
error:
	kfree(mq);
	return NULL;
}