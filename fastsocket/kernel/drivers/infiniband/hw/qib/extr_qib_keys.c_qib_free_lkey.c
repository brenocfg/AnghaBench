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
typedef  int u32 ;
struct qib_mregion {int lkey; scalar_t__ lkey_published; TYPE_1__* pd; } ;
struct qib_lkey_table {int /*<<< orphan*/  lock; int /*<<< orphan*/ * table; } ;
struct qib_ibdev {int /*<<< orphan*/  dma_mr; struct qib_lkey_table lk_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ib_qib_lkey_table_size ; 
 int /*<<< orphan*/  qib_put_mr (struct qib_mregion*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 

void qib_free_lkey(struct qib_mregion *mr)
{
	unsigned long flags;
	u32 lkey = mr->lkey;
	u32 r;
	struct qib_ibdev *dev = to_idev(mr->pd->device);
	struct qib_lkey_table *rkt = &dev->lk_table;

	spin_lock_irqsave(&rkt->lock, flags);
	if (!mr->lkey_published)
		goto out;
	if (lkey == 0)
		rcu_assign_pointer(dev->dma_mr, NULL);
	else {
		r = lkey >> (32 - ib_qib_lkey_table_size);
		rcu_assign_pointer(rkt->table[r], NULL);
	}
	qib_put_mr(mr);
	mr->lkey_published = 0;
out:
	spin_unlock_irqrestore(&rkt->lock, flags);
}