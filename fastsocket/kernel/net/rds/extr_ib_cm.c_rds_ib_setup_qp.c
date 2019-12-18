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
struct rds_ib_send_work {int dummy; } ;
struct rds_ib_recv_work {int dummy; } ;
struct rds_ib_device {int max_wrs; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  mr; int /*<<< orphan*/  pd; } ;
struct TYPE_5__ {int w_nr; } ;
struct rds_ib_connection {int /*<<< orphan*/ * i_recv_cq; int /*<<< orphan*/ * i_send_cq; int /*<<< orphan*/  i_mr; int /*<<< orphan*/  i_pd; void* i_recvs; TYPE_2__ i_recv_ring; void* i_sends; TYPE_2__ i_send_ring; void* i_ack; int /*<<< orphan*/  i_ack_dma; void* i_recv_hdrs; int /*<<< orphan*/  i_recv_hdrs_dma; void* i_send_hdrs; int /*<<< orphan*/  i_send_hdrs_dma; TYPE_3__* i_cm_id; } ;
struct rds_header {int dummy; } ;
struct rds_connection {struct rds_ib_connection* c_transport_data; } ;
struct TYPE_4__ {int max_send_wr; int max_recv_wr; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; } ;
struct ib_qp_init_attr {int /*<<< orphan*/ * recv_cq; int /*<<< orphan*/ * send_cq; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; TYPE_1__ cap; struct rds_connection* qp_context; int /*<<< orphan*/  event_handler; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;
struct TYPE_6__ {struct ib_device* device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  IB_CQ_SOLICITED ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_SIGNAL_REQ_WR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDS_IB_RECV_SGE ; 
 void* ib_create_cq (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rds_connection*,int,int /*<<< orphan*/ ) ; 
 void* ib_dma_alloc_coherent (struct ib_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ib_req_notify_cq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_to_node (struct ib_device*) ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int rdma_create_qp (TYPE_3__*,int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  rds_ib_add_conn (struct rds_ib_device*,struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_cq_event_handler ; 
 int /*<<< orphan*/  rds_ib_dev_put (struct rds_ib_device*) ; 
 struct rds_ib_device* rds_ib_get_client_data (struct ib_device*) ; 
 int /*<<< orphan*/  rds_ib_qp_event_handler ; 
 int /*<<< orphan*/  rds_ib_recv_cq_comp_handler ; 
 int /*<<< orphan*/  rds_ib_recv_init_ack (struct rds_ib_connection*) ; 
 int /*<<< orphan*/  rds_ib_ring_resize (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rds_ib_send_cq_comp_handler ; 
 int /*<<< orphan*/  rdsdebug (char*,...) ; 
 void* vzalloc_node (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rds_ib_setup_qp(struct rds_connection *conn)
{
	struct rds_ib_connection *ic = conn->c_transport_data;
	struct ib_device *dev = ic->i_cm_id->device;
	struct ib_qp_init_attr attr;
	struct rds_ib_device *rds_ibdev;
	int ret;

	/*
	 * It's normal to see a null device if an incoming connection races
	 * with device removal, so we don't print a warning.
	 */
	rds_ibdev = rds_ib_get_client_data(dev);
	if (!rds_ibdev)
		return -EOPNOTSUPP;

	/* add the conn now so that connection establishment has the dev */
	rds_ib_add_conn(rds_ibdev, conn);

	if (rds_ibdev->max_wrs < ic->i_send_ring.w_nr + 1)
		rds_ib_ring_resize(&ic->i_send_ring, rds_ibdev->max_wrs - 1);
	if (rds_ibdev->max_wrs < ic->i_recv_ring.w_nr + 1)
		rds_ib_ring_resize(&ic->i_recv_ring, rds_ibdev->max_wrs - 1);

	/* Protection domain and memory range */
	ic->i_pd = rds_ibdev->pd;
	ic->i_mr = rds_ibdev->mr;

	ic->i_send_cq = ib_create_cq(dev, rds_ib_send_cq_comp_handler,
				     rds_ib_cq_event_handler, conn,
				     ic->i_send_ring.w_nr + 1, 0);
	if (IS_ERR(ic->i_send_cq)) {
		ret = PTR_ERR(ic->i_send_cq);
		ic->i_send_cq = NULL;
		rdsdebug("ib_create_cq send failed: %d\n", ret);
		goto out;
	}

	ic->i_recv_cq = ib_create_cq(dev, rds_ib_recv_cq_comp_handler,
				     rds_ib_cq_event_handler, conn,
				     ic->i_recv_ring.w_nr, 0);
	if (IS_ERR(ic->i_recv_cq)) {
		ret = PTR_ERR(ic->i_recv_cq);
		ic->i_recv_cq = NULL;
		rdsdebug("ib_create_cq recv failed: %d\n", ret);
		goto out;
	}

	ret = ib_req_notify_cq(ic->i_send_cq, IB_CQ_NEXT_COMP);
	if (ret) {
		rdsdebug("ib_req_notify_cq send failed: %d\n", ret);
		goto out;
	}

	ret = ib_req_notify_cq(ic->i_recv_cq, IB_CQ_SOLICITED);
	if (ret) {
		rdsdebug("ib_req_notify_cq recv failed: %d\n", ret);
		goto out;
	}

	/* XXX negotiate max send/recv with remote? */
	memset(&attr, 0, sizeof(attr));
	attr.event_handler = rds_ib_qp_event_handler;
	attr.qp_context = conn;
	/* + 1 to allow for the single ack message */
	attr.cap.max_send_wr = ic->i_send_ring.w_nr + 1;
	attr.cap.max_recv_wr = ic->i_recv_ring.w_nr + 1;
	attr.cap.max_send_sge = rds_ibdev->max_sge;
	attr.cap.max_recv_sge = RDS_IB_RECV_SGE;
	attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	attr.qp_type = IB_QPT_RC;
	attr.send_cq = ic->i_send_cq;
	attr.recv_cq = ic->i_recv_cq;

	/*
	 * XXX this can fail if max_*_wr is too large?  Are we supposed
	 * to back off until we get a value that the hardware can support?
	 */
	ret = rdma_create_qp(ic->i_cm_id, ic->i_pd, &attr);
	if (ret) {
		rdsdebug("rdma_create_qp failed: %d\n", ret);
		goto out;
	}

	ic->i_send_hdrs = ib_dma_alloc_coherent(dev,
					   ic->i_send_ring.w_nr *
						sizeof(struct rds_header),
					   &ic->i_send_hdrs_dma, GFP_KERNEL);
	if (!ic->i_send_hdrs) {
		ret = -ENOMEM;
		rdsdebug("ib_dma_alloc_coherent send failed\n");
		goto out;
	}

	ic->i_recv_hdrs = ib_dma_alloc_coherent(dev,
					   ic->i_recv_ring.w_nr *
						sizeof(struct rds_header),
					   &ic->i_recv_hdrs_dma, GFP_KERNEL);
	if (!ic->i_recv_hdrs) {
		ret = -ENOMEM;
		rdsdebug("ib_dma_alloc_coherent recv failed\n");
		goto out;
	}

	ic->i_ack = ib_dma_alloc_coherent(dev, sizeof(struct rds_header),
				       &ic->i_ack_dma, GFP_KERNEL);
	if (!ic->i_ack) {
		ret = -ENOMEM;
		rdsdebug("ib_dma_alloc_coherent ack failed\n");
		goto out;
	}

	ic->i_sends = vzalloc_node(ic->i_send_ring.w_nr * sizeof(struct rds_ib_send_work),
				   ibdev_to_node(dev));
	if (!ic->i_sends) {
		ret = -ENOMEM;
		rdsdebug("send allocation failed\n");
		goto out;
	}

	ic->i_recvs = vzalloc_node(ic->i_recv_ring.w_nr * sizeof(struct rds_ib_recv_work),
				   ibdev_to_node(dev));
	if (!ic->i_recvs) {
		ret = -ENOMEM;
		rdsdebug("recv allocation failed\n");
		goto out;
	}

	rds_ib_recv_init_ack(ic);

	rdsdebug("conn %p pd %p mr %p cq %p %p\n", conn, ic->i_pd, ic->i_mr,
		 ic->i_send_cq, ic->i_recv_cq);

out:
	rds_ib_dev_put(rds_ibdev);
	return ret;
}