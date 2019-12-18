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
struct TYPE_7__ {int /*<<< orphan*/  ah; } ;
struct TYPE_8__ {TYPE_1__ ud; } ;
struct TYPE_9__ {unsigned int num_sge; TYPE_2__ wr; } ;
struct qib_swqe {TYPE_3__ wr; struct qib_sge* sg_list; } ;
struct qib_sge {int /*<<< orphan*/ * mr; } ;
struct TYPE_10__ {scalar_t__ qp_type; } ;
struct qib_qp {scalar_t__ s_last; scalar_t__ s_head; scalar_t__ s_size; struct qib_ack_entry* s_ack_queue; TYPE_4__ ibqp; int /*<<< orphan*/ * s_rdma_mr; int /*<<< orphan*/  r_sge; int /*<<< orphan*/  s_rdma_read_sge; int /*<<< orphan*/  r_aflags; } ;
struct TYPE_11__ {int /*<<< orphan*/ * mr; } ;
struct qib_ack_entry {scalar_t__ opcode; TYPE_5__ rdma_sge; } ;
struct TYPE_12__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct qib_ack_entry*) ; 
 scalar_t__ IB_OPCODE_RC_RDMA_READ_REQUEST ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_SMI ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  QIB_R_REWIND_SGE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct qib_swqe* get_swqe_ptr (struct qib_qp*,scalar_t__) ; 
 int /*<<< orphan*/  qib_put_mr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_put_ss (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* to_iah (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_mr_refs(struct qib_qp *qp, int clr_sends)
{
	unsigned n;

	if (test_and_clear_bit(QIB_R_REWIND_SGE, &qp->r_aflags))
		qib_put_ss(&qp->s_rdma_read_sge);

	qib_put_ss(&qp->r_sge);

	if (clr_sends) {
		while (qp->s_last != qp->s_head) {
			struct qib_swqe *wqe = get_swqe_ptr(qp, qp->s_last);
			unsigned i;

			for (i = 0; i < wqe->wr.num_sge; i++) {
				struct qib_sge *sge = &wqe->sg_list[i];

				qib_put_mr(sge->mr);
			}
			if (qp->ibqp.qp_type == IB_QPT_UD ||
			    qp->ibqp.qp_type == IB_QPT_SMI ||
			    qp->ibqp.qp_type == IB_QPT_GSI)
				atomic_dec(&to_iah(wqe->wr.wr.ud.ah)->refcount);
			if (++qp->s_last >= qp->s_size)
				qp->s_last = 0;
		}
		if (qp->s_rdma_mr) {
			qib_put_mr(qp->s_rdma_mr);
			qp->s_rdma_mr = NULL;
		}
	}

	if (qp->ibqp.qp_type != IB_QPT_RC)
		return;

	for (n = 0; n < ARRAY_SIZE(qp->s_ack_queue); n++) {
		struct qib_ack_entry *e = &qp->s_ack_queue[n];

		if (e->opcode == IB_OPCODE_RC_RDMA_READ_REQUEST &&
		    e->rdma_sge.mr) {
			qib_put_mr(e->rdma_sge.mr);
			e->rdma_sge.mr = NULL;
		}
	}
}