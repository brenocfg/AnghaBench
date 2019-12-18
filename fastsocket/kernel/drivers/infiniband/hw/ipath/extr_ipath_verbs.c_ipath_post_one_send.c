#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_8__ {TYPE_1__* ah; } ;
struct TYPE_9__ {TYPE_2__ ud; } ;
struct ib_send_wr {int num_sge; scalar_t__ opcode; TYPE_6__* sg_list; TYPE_3__ wr; } ;
struct ipath_swqe {int length; scalar_t__ ssn; struct ib_send_wr wr; int /*<<< orphan*/ * sg_list; } ;
struct TYPE_10__ {scalar_t__ qp_type; scalar_t__ pd; int /*<<< orphan*/  device; } ;
struct ipath_qp {size_t state; int s_max_sge; scalar_t__ s_head; scalar_t__ s_size; scalar_t__ s_last; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_ssn; TYPE_4__ ibqp; int /*<<< orphan*/  s_max_rd_atomic; } ;
struct ipath_devdata {int ipath_flags; int ipath_ibmtu; } ;
struct TYPE_12__ {int length; int addr; } ;
struct TYPE_11__ {struct ipath_devdata* dd; } ;
struct TYPE_7__ {scalar_t__ pd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_SMI ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ IB_QPT_UD ; 
 scalar_t__ IB_WR_ATOMIC_CMP_AND_SWP ; 
 unsigned int IB_WR_ATOMIC_FETCH_AND_ADD ; 
 unsigned int IB_WR_RDMA_READ ; 
 scalar_t__ IB_WR_SEND ; 
 scalar_t__ IB_WR_SEND_WITH_IMM ; 
 int IPATH_LINKACTIVE ; 
 int IPATH_POST_SEND_OK ; 
 struct ipath_swqe* get_swqe_ptr (struct ipath_qp*,scalar_t__) ; 
 int* ib_ipath_state_ops ; 
 int ipath_lkey_ok (struct ipath_qp*,int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_5__* to_idev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipath_post_one_send(struct ipath_qp *qp, struct ib_send_wr *wr)
{
	struct ipath_swqe *wqe;
	u32 next;
	int i;
	int j;
	int acc;
	int ret;
	unsigned long flags;
	struct ipath_devdata *dd = to_idev(qp->ibqp.device)->dd;

	spin_lock_irqsave(&qp->s_lock, flags);

	if (qp->ibqp.qp_type != IB_QPT_SMI &&
	    !(dd->ipath_flags & IPATH_LINKACTIVE)) {
		ret = -ENETDOWN;
		goto bail;
	}

	/* Check that state is OK to post send. */
	if (unlikely(!(ib_ipath_state_ops[qp->state] & IPATH_POST_SEND_OK)))
		goto bail_inval;

	/* IB spec says that num_sge == 0 is OK. */
	if (wr->num_sge > qp->s_max_sge)
		goto bail_inval;

	/*
	 * Don't allow RDMA reads or atomic operations on UC or
	 * undefined operations.
	 * Make sure buffer is large enough to hold the result for atomics.
	 */
	if (qp->ibqp.qp_type == IB_QPT_UC) {
		if ((unsigned) wr->opcode >= IB_WR_RDMA_READ)
			goto bail_inval;
	} else if (qp->ibqp.qp_type == IB_QPT_UD) {
		/* Check UD opcode */
		if (wr->opcode != IB_WR_SEND &&
		    wr->opcode != IB_WR_SEND_WITH_IMM)
			goto bail_inval;
		/* Check UD destination address PD */
		if (qp->ibqp.pd != wr->wr.ud.ah->pd)
			goto bail_inval;
	} else if ((unsigned) wr->opcode > IB_WR_ATOMIC_FETCH_AND_ADD)
		goto bail_inval;
	else if (wr->opcode >= IB_WR_ATOMIC_CMP_AND_SWP &&
		   (wr->num_sge == 0 ||
		    wr->sg_list[0].length < sizeof(u64) ||
		    wr->sg_list[0].addr & (sizeof(u64) - 1)))
		goto bail_inval;
	else if (wr->opcode >= IB_WR_RDMA_READ && !qp->s_max_rd_atomic)
		goto bail_inval;

	next = qp->s_head + 1;
	if (next >= qp->s_size)
		next = 0;
	if (next == qp->s_last) {
		ret = -ENOMEM;
		goto bail;
	}

	wqe = get_swqe_ptr(qp, qp->s_head);
	wqe->wr = *wr;
	wqe->length = 0;
	if (wr->num_sge) {
		acc = wr->opcode >= IB_WR_RDMA_READ ?
			IB_ACCESS_LOCAL_WRITE : 0;
		for (i = 0, j = 0; i < wr->num_sge; i++) {
			u32 length = wr->sg_list[i].length;
			int ok;

			if (length == 0)
				continue;
			ok = ipath_lkey_ok(qp, &wqe->sg_list[j],
					   &wr->sg_list[i], acc);
			if (!ok)
				goto bail_inval;
			wqe->length += length;
			j++;
		}
		wqe->wr.num_sge = j;
	}
	if (qp->ibqp.qp_type == IB_QPT_UC ||
	    qp->ibqp.qp_type == IB_QPT_RC) {
		if (wqe->length > 0x80000000U)
			goto bail_inval;
	} else if (wqe->length > to_idev(qp->ibqp.device)->dd->ipath_ibmtu)
		goto bail_inval;
	wqe->ssn = qp->s_ssn++;
	qp->s_head = next;

	ret = 0;
	goto bail;

bail_inval:
	ret = -EINVAL;
bail:
	spin_unlock_irqrestore(&qp->s_lock, flags);
	return ret;
}