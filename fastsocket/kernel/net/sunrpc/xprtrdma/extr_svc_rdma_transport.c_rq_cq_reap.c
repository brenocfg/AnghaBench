#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xpt_flags; } ;
struct svcxprt_rdma {TYPE_1__ sc_xprt; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_rq_dto_lock; int /*<<< orphan*/  sc_rq_dto_q; int /*<<< orphan*/  sc_rq_cq; } ;
struct svc_rdma_op_ctxt {scalar_t__ wc_status; int /*<<< orphan*/  dto_q; int /*<<< orphan*/  byte_len; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  byte_len; scalar_t__ wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  RDMAXPRT_CONN_PENDING ; 
 int /*<<< orphan*/  RDMAXPRT_RQ_PENDING ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  XPT_DATA ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,struct svc_rdma_op_ctxt*) ; 
 int ib_poll_cq (int /*<<< orphan*/ ,int,struct ib_wc*) ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_stat_rq_poll ; 
 int /*<<< orphan*/  rdma_stat_rq_prod ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_rdma_put_context (struct svc_rdma_op_ctxt*,int) ; 
 int /*<<< orphan*/  svc_rdma_unmap_dma (struct svc_rdma_op_ctxt*) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (TYPE_1__*) ; 
 int /*<<< orphan*/  svc_xprt_put (TYPE_1__*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rq_cq_reap(struct svcxprt_rdma *xprt)
{
	int ret;
	struct ib_wc wc;
	struct svc_rdma_op_ctxt *ctxt = NULL;

	if (!test_and_clear_bit(RDMAXPRT_RQ_PENDING, &xprt->sc_flags))
		return;

	ib_req_notify_cq(xprt->sc_rq_cq, IB_CQ_NEXT_COMP);
	atomic_inc(&rdma_stat_rq_poll);

	while ((ret = ib_poll_cq(xprt->sc_rq_cq, 1, &wc)) > 0) {
		ctxt = (struct svc_rdma_op_ctxt *)(unsigned long)wc.wr_id;
		ctxt->wc_status = wc.status;
		ctxt->byte_len = wc.byte_len;
		svc_rdma_unmap_dma(ctxt);
		if (wc.status != IB_WC_SUCCESS) {
			/* Close the transport */
			dprintk("svcrdma: transport closing putting ctxt %p\n", ctxt);
			set_bit(XPT_CLOSE, &xprt->sc_xprt.xpt_flags);
			svc_rdma_put_context(ctxt, 1);
			svc_xprt_put(&xprt->sc_xprt);
			continue;
		}
		spin_lock_bh(&xprt->sc_rq_dto_lock);
		list_add_tail(&ctxt->dto_q, &xprt->sc_rq_dto_q);
		spin_unlock_bh(&xprt->sc_rq_dto_lock);
		svc_xprt_put(&xprt->sc_xprt);
	}

	if (ctxt)
		atomic_inc(&rdma_stat_rq_prod);

	set_bit(XPT_DATA, &xprt->sc_xprt.xpt_flags);
	/*
	 * If data arrived before established event,
	 * don't enqueue. This defers RPC I/O until the
	 * RDMA connection is complete.
	 */
	if (!test_bit(RDMAXPRT_CONN_PENDING, &xprt->sc_flags))
		svc_xprt_enqueue(&xprt->sc_xprt);
}