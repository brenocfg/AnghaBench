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
struct qib_mregion {int lkey_published; size_t lkey; TYPE_1__* pd; } ;
struct qib_lkey_table {size_t next; int max; int gen; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** table; } ;
struct qib_ibdev {int /*<<< orphan*/ * dma_mr; struct qib_lkey_table lk_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ib_qib_lkey_table_size ; 
 int /*<<< orphan*/  qib_get_mr (struct qib_mregion*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct qib_mregion*) ; 
 struct qib_mregion* rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 

int qib_alloc_lkey(struct qib_mregion *mr, int dma_region)
{
	unsigned long flags;
	u32 r;
	u32 n;
	int ret = 0;
	struct qib_ibdev *dev = to_idev(mr->pd->device);
	struct qib_lkey_table *rkt = &dev->lk_table;

	spin_lock_irqsave(&rkt->lock, flags);

	/* special case for dma_mr lkey == 0 */
	if (dma_region) {
		struct qib_mregion *tmr;

		tmr = rcu_dereference(dev->dma_mr);
		if (!tmr) {
			qib_get_mr(mr);
			rcu_assign_pointer(dev->dma_mr, mr);
			mr->lkey_published = 1;
		}
		goto success;
	}

	/* Find the next available LKEY */
	r = rkt->next;
	n = r;
	for (;;) {
		if (rkt->table[r] == NULL)
			break;
		r = (r + 1) & (rkt->max - 1);
		if (r == n)
			goto bail;
	}
	rkt->next = (r + 1) & (rkt->max - 1);
	/*
	 * Make sure lkey is never zero which is reserved to indicate an
	 * unrestricted LKEY.
	 */
	rkt->gen++;
	mr->lkey = (r << (32 - ib_qib_lkey_table_size)) |
		((((1 << (24 - ib_qib_lkey_table_size)) - 1) & rkt->gen)
		 << 8);
	if (mr->lkey == 0) {
		mr->lkey |= 1 << 8;
		rkt->gen++;
	}
	qib_get_mr(mr);
	rcu_assign_pointer(rkt->table[r], mr);
	mr->lkey_published = 1;
success:
	spin_unlock_irqrestore(&rkt->lock, flags);
out:
	return ret;
bail:
	spin_unlock_irqrestore(&rkt->lock, flags);
	ret = -ENOMEM;
	goto out;
}