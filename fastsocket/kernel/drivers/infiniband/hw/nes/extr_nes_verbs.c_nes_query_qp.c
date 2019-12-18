#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct TYPE_4__ {int /*<<< orphan*/  rq_size; int /*<<< orphan*/  sq_size; } ;
struct nes_qp {TYPE_2__ ibqp; TYPE_1__ hwqp; } ;
struct TYPE_6__ {int max_recv_sge; int max_inline_data; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {TYPE_3__ cap; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct ib_qp_attr {TYPE_3__ cap; scalar_t__ qp_access_flags; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_QP ; 
 int NES_DRV_OPT_NO_INLINE_DATA ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 
 int nes_drv_opt ; 
 struct nes_qp* to_nesqp (struct ib_qp*) ; 

__attribute__((used)) static int nes_query_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
		int attr_mask, struct ib_qp_init_attr *init_attr)
{
	struct nes_qp *nesqp = to_nesqp(ibqp);

	nes_debug(NES_DBG_QP, "\n");

	attr->qp_access_flags = 0;
	attr->cap.max_send_wr = nesqp->hwqp.sq_size;
	attr->cap.max_recv_wr = nesqp->hwqp.rq_size;
	attr->cap.max_recv_sge = 1;
	if (nes_drv_opt & NES_DRV_OPT_NO_INLINE_DATA)
		attr->cap.max_inline_data = 0;
	else
		attr->cap.max_inline_data = 64;

	init_attr->event_handler = nesqp->ibqp.event_handler;
	init_attr->qp_context = nesqp->ibqp.qp_context;
	init_attr->send_cq = nesqp->ibqp.send_cq;
	init_attr->recv_cq = nesqp->ibqp.recv_cq;
	init_attr->srq = nesqp->ibqp.srq = nesqp->ibqp.srq;
	init_attr->cap = attr->cap;

	return 0;
}