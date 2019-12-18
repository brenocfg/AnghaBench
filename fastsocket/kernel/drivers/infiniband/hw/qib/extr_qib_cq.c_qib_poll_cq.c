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
typedef  size_t u32 ;
struct qib_cq_wc {size_t tail; size_t head; struct ib_wc* kqueue; } ;
struct TYPE_2__ {size_t cqe; } ;
struct qib_cq {int /*<<< orphan*/  lock; TYPE_1__ ibcq; struct qib_cq_wc* queue; scalar_t__ ip; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qib_cq* to_icq (struct ib_cq*) ; 

int qib_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *entry)
{
	struct qib_cq *cq = to_icq(ibcq);
	struct qib_cq_wc *wc;
	unsigned long flags;
	int npolled;
	u32 tail;

	/* The kernel can only poll a kernel completion queue */
	if (cq->ip) {
		npolled = -EINVAL;
		goto bail;
	}

	spin_lock_irqsave(&cq->lock, flags);

	wc = cq->queue;
	tail = wc->tail;
	if (tail > (u32) cq->ibcq.cqe)
		tail = (u32) cq->ibcq.cqe;
	for (npolled = 0; npolled < num_entries; ++npolled, ++entry) {
		if (tail == wc->head)
			break;
		/* The kernel doesn't need a RMB since it has the lock. */
		*entry = wc->kqueue[tail];
		if (tail >= cq->ibcq.cqe)
			tail = 0;
		else
			tail++;
	}
	wc->tail = tail;

	spin_unlock_irqrestore(&cq->lock, flags);

bail:
	return npolled;
}