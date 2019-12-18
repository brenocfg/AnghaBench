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
struct TYPE_8__ {size_t tail; } ;
struct TYPE_7__ {scalar_t__ srq; } ;
struct ocrdma_qp {scalar_t__ qp_type; TYPE_4__ rq; int /*<<< orphan*/ * rqe_wr_id_tbl; TYPE_3__ ibqp; } ;
struct TYPE_6__ {int /*<<< orphan*/  lkey_immdt; int /*<<< orphan*/  rxlen; } ;
struct ocrdma_cqe {TYPE_2__ rq; } ;
struct TYPE_5__ {void* invalidate_rkey; void* imm_data; } ;
struct ib_wc {int /*<<< orphan*/  wr_id; int /*<<< orphan*/  wc_flags; TYPE_1__ ex; int /*<<< orphan*/  opcode; void* byte_len; int /*<<< orphan*/  status; TYPE_3__* qp; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  IB_WC_RECV_RDMA_WITH_IMM ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WITH_IMM ; 
 int /*<<< orphan*/  IB_WC_WITH_INVALIDATE ; 
 void* htonl (void*) ; 
 scalar_t__ is_cqe_imm (struct ocrdma_cqe*) ; 
 scalar_t__ is_cqe_invalidated (struct ocrdma_cqe*) ; 
 scalar_t__ is_cqe_wr_imm (struct ocrdma_cqe*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_hwq_inc_tail (TYPE_4__*) ; 
 int /*<<< orphan*/  ocrdma_update_free_srq_cqe (struct ib_wc*,struct ocrdma_cqe*,struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_update_ud_rcqe (struct ib_wc*,struct ocrdma_cqe*) ; 

__attribute__((used)) static void ocrdma_poll_success_rcqe(struct ocrdma_qp *qp,
				     struct ocrdma_cqe *cqe, struct ib_wc *ibwc)
{
	ibwc->opcode = IB_WC_RECV;
	ibwc->qp = &qp->ibqp;
	ibwc->status = IB_WC_SUCCESS;

	if (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI)
		ocrdma_update_ud_rcqe(ibwc, cqe);
	else
		ibwc->byte_len = le32_to_cpu(cqe->rq.rxlen);

	if (is_cqe_imm(cqe)) {
		ibwc->ex.imm_data = htonl(le32_to_cpu(cqe->rq.lkey_immdt));
		ibwc->wc_flags |= IB_WC_WITH_IMM;
	} else if (is_cqe_wr_imm(cqe)) {
		ibwc->opcode = IB_WC_RECV_RDMA_WITH_IMM;
		ibwc->ex.imm_data = htonl(le32_to_cpu(cqe->rq.lkey_immdt));
		ibwc->wc_flags |= IB_WC_WITH_IMM;
	} else if (is_cqe_invalidated(cqe)) {
		ibwc->ex.invalidate_rkey = le32_to_cpu(cqe->rq.lkey_immdt);
		ibwc->wc_flags |= IB_WC_WITH_INVALIDATE;
	}
	if (qp->ibqp.srq)
		ocrdma_update_free_srq_cqe(ibwc, cqe, qp);
	else {
		ibwc->wr_id = qp->rqe_wr_id_tbl[qp->rq.tail];
		ocrdma_hwq_inc_tail(&qp->rq);
	}
}