#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ipath_sge {scalar_t__ length; scalar_t__ sge_length; unsigned int m; unsigned int n; void* vaddr; struct ipath_mregion* mr; } ;
struct TYPE_5__ {scalar_t__ pd; int /*<<< orphan*/  device; } ;
struct ipath_qp {TYPE_1__ ibqp; } ;
struct ipath_pd {scalar_t__ user; } ;
struct ipath_mregion {int lkey; scalar_t__ pd; size_t user_base; scalar_t__ length; int access_flags; TYPE_3__** map; scalar_t__ offset; } ;
struct ipath_lkey_table {struct ipath_mregion** table; } ;
struct ib_sge {int lkey; size_t addr; scalar_t__ length; } ;
struct TYPE_8__ {struct ipath_lkey_table lk_table; } ;
struct TYPE_7__ {TYPE_2__* segs; } ;
struct TYPE_6__ {size_t length; void* vaddr; } ;

/* Variables and functions */
 unsigned int IPATH_SEGSZ ; 
 int ib_ipath_lkey_table_size ; 
 TYPE_4__* to_idev (int /*<<< orphan*/ ) ; 
 struct ipath_pd* to_ipd (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int ipath_lkey_ok(struct ipath_qp *qp, struct ipath_sge *isge,
		  struct ib_sge *sge, int acc)
{
	struct ipath_lkey_table *rkt = &to_idev(qp->ibqp.device)->lk_table;
	struct ipath_mregion *mr;
	unsigned n, m;
	size_t off;
	int ret;

	/*
	 * We use LKEY == zero for kernel virtual addresses
	 * (see ipath_get_dma_mr and ipath_dma.c).
	 */
	if (sge->lkey == 0) {
		/* always a kernel port, no locking needed */
		struct ipath_pd *pd = to_ipd(qp->ibqp.pd);

		if (pd->user) {
			ret = 0;
			goto bail;
		}
		isge->mr = NULL;
		isge->vaddr = (void *) sge->addr;
		isge->length = sge->length;
		isge->sge_length = sge->length;
		ret = 1;
		goto bail;
	}
	mr = rkt->table[(sge->lkey >> (32 - ib_ipath_lkey_table_size))];
	if (unlikely(mr == NULL || mr->lkey != sge->lkey ||
		     qp->ibqp.pd != mr->pd)) {
		ret = 0;
		goto bail;
	}

	off = sge->addr - mr->user_base;
	if (unlikely(sge->addr < mr->user_base ||
		     off + sge->length > mr->length ||
		     (mr->access_flags & acc) != acc)) {
		ret = 0;
		goto bail;
	}

	off += mr->offset;
	m = 0;
	n = 0;
	while (off >= mr->map[m]->segs[n].length) {
		off -= mr->map[m]->segs[n].length;
		n++;
		if (n >= IPATH_SEGSZ) {
			m++;
			n = 0;
		}
	}
	isge->mr = mr;
	isge->vaddr = mr->map[m]->segs[n].vaddr + off;
	isge->length = mr->map[m]->segs[n].length - off;
	isge->sge_length = sge->length;
	isge->m = m;
	isge->n = n;

	ret = 1;

bail:
	return ret;
}