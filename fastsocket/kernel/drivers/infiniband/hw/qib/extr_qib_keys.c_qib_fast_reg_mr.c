#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ pd; int /*<<< orphan*/  device; } ;
struct qib_qp {TYPE_1__ ibqp; } ;
struct qib_pd {scalar_t__ user; } ;
struct qib_mregion {scalar_t__ pd; size_t max_segs; int lkey; size_t length; TYPE_6__** map; int /*<<< orphan*/  access_flags; int /*<<< orphan*/  iova; int /*<<< orphan*/  user_base; } ;
struct qib_lkey_table {int /*<<< orphan*/  lock; int /*<<< orphan*/ * table; } ;
struct TYPE_10__ {int rkey; size_t page_list_len; unsigned long page_shift; size_t length; TYPE_2__* page_list; int /*<<< orphan*/  access_flags; int /*<<< orphan*/  iova_start; } ;
struct TYPE_11__ {TYPE_3__ fast_reg; } ;
struct ib_send_wr {TYPE_4__ wr; } ;
struct TYPE_14__ {struct qib_lkey_table lk_table; } ;
struct TYPE_13__ {TYPE_5__* segs; } ;
struct TYPE_12__ {size_t length; void* vaddr; } ;
struct TYPE_9__ {scalar_t__* page_list; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int QIB_SEGSZ ; 
 int ib_qib_lkey_table_size ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct qib_mregion* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_7__* to_idev (int /*<<< orphan*/ ) ; 
 struct qib_pd* to_ipd (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int qib_fast_reg_mr(struct qib_qp *qp, struct ib_send_wr *wr)
{
	struct qib_lkey_table *rkt = &to_idev(qp->ibqp.device)->lk_table;
	struct qib_pd *pd = to_ipd(qp->ibqp.pd);
	struct qib_mregion *mr;
	u32 rkey = wr->wr.fast_reg.rkey;
	unsigned i, n, m;
	int ret = -EINVAL;
	unsigned long flags;
	u64 *page_list;
	size_t ps;

	spin_lock_irqsave(&rkt->lock, flags);
	if (pd->user || rkey == 0)
		goto bail;

	mr = rcu_dereference_protected(
		rkt->table[(rkey >> (32 - ib_qib_lkey_table_size))],
		lockdep_is_held(&rkt->lock));
	if (unlikely(mr == NULL || qp->ibqp.pd != mr->pd))
		goto bail;

	if (wr->wr.fast_reg.page_list_len > mr->max_segs)
		goto bail;

	ps = 1UL << wr->wr.fast_reg.page_shift;
	if (wr->wr.fast_reg.length > ps * wr->wr.fast_reg.page_list_len)
		goto bail;

	mr->user_base = wr->wr.fast_reg.iova_start;
	mr->iova = wr->wr.fast_reg.iova_start;
	mr->lkey = rkey;
	mr->length = wr->wr.fast_reg.length;
	mr->access_flags = wr->wr.fast_reg.access_flags;
	page_list = wr->wr.fast_reg.page_list->page_list;
	m = 0;
	n = 0;
	for (i = 0; i < wr->wr.fast_reg.page_list_len; i++) {
		mr->map[m]->segs[n].vaddr = (void *) page_list[i];
		mr->map[m]->segs[n].length = ps;
		if (++n == QIB_SEGSZ) {
			m++;
			n = 0;
		}
	}

	ret = 0;
bail:
	spin_unlock_irqrestore(&rkt->lock, flags);
	return ret;
}