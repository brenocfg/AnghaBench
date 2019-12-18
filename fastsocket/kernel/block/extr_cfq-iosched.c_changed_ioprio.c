#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct io_context {int dummy; } ;
struct cfq_queue {int dummy; } ;
struct cfq_io_context {struct cfq_queue** cfqq; int /*<<< orphan*/  ioc; struct cfq_data* key; } ;
struct cfq_data {TYPE_1__* queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct cfq_queue* cfq_get_queue (struct cfq_data*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_prio_changed (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void changed_ioprio(struct io_context *ioc, struct cfq_io_context *cic)
{
	struct cfq_data *cfqd = cic->key;
	struct cfq_queue *cfqq;
	unsigned long flags;

	if (unlikely(!cfqd))
		return;

	spin_lock_irqsave(cfqd->queue->queue_lock, flags);

	cfqq = cic->cfqq[BLK_RW_ASYNC];
	if (cfqq) {
		struct cfq_queue *new_cfqq;
		new_cfqq = cfq_get_queue(cfqd, BLK_RW_ASYNC, cic->ioc,
						GFP_ATOMIC);
		if (new_cfqq) {
			cic->cfqq[BLK_RW_ASYNC] = new_cfqq;
			cfq_put_queue(cfqq);
		}
	}

	cfqq = cic->cfqq[BLK_RW_SYNC];
	if (cfqq)
		cfq_mark_cfqq_prio_changed(cfqq);

	spin_unlock_irqrestore(cfqd->queue->queue_lock, flags);
}