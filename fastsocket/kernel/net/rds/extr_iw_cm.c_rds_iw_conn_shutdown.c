#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int w_nr; } ;
struct rds_iw_connection {int /*<<< orphan*/ * i_recvs; int /*<<< orphan*/ * i_sends; TYPE_1__* i_iwinc; TYPE_2__ i_recv_ring; TYPE_2__ i_send_ring; int /*<<< orphan*/  i_credits; scalar_t__ i_flowctl; scalar_t__ i_ack_recv; scalar_t__ i_ack_next; int /*<<< orphan*/  i_ack_flags; int /*<<< orphan*/ * i_rm; scalar_t__ rds_iwdev; int /*<<< orphan*/ * i_ack; int /*<<< orphan*/ * i_recv_hdrs; int /*<<< orphan*/ * i_send_hdrs; int /*<<< orphan*/ * i_recv_cq; int /*<<< orphan*/ * i_send_cq; int /*<<< orphan*/ * i_mr; int /*<<< orphan*/ * i_pd; TYPE_4__* i_cm_id; int /*<<< orphan*/  i_ack_dma; int /*<<< orphan*/  i_recv_hdrs_dma; int /*<<< orphan*/  i_send_hdrs_dma; } ;
struct rds_header {int dummy; } ;
struct rds_connection {struct rds_iw_connection* c_transport_data; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * qp; struct ib_device* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  ii_inc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 int /*<<< orphan*/  IB_ACK_IN_FLIGHT ; 
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int /*<<< orphan*/  atomic64_set (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dma_free_coherent (struct ib_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_modify_qp (int /*<<< orphan*/ *,struct ib_qp_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_4__*) ; 
 int /*<<< orphan*/  rdma_destroy_qp (TYPE_4__*) ; 
 int rdma_disconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  rds_inc_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_iw_recv_clear_ring (struct rds_iw_connection*) ; 
 int /*<<< orphan*/  rds_iw_remove_conn (scalar_t__,struct rds_connection*) ; 
 scalar_t__ rds_iw_ring_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  rds_iw_ring_empty_wait ; 
 int /*<<< orphan*/  rds_iw_ring_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_send_clear_ring (struct rds_iw_connection*) ; 
 int /*<<< orphan*/  rds_iw_sysctl_max_recv_wr ; 
 int /*<<< orphan*/  rds_iw_sysctl_max_send_wr ; 
 int /*<<< orphan*/  rds_message_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,...) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void rds_iw_conn_shutdown(struct rds_connection *conn)
{
	struct rds_iw_connection *ic = conn->c_transport_data;
	int err = 0;
	struct ib_qp_attr qp_attr;

	rdsdebug("cm %p pd %p cq %p %p qp %p\n", ic->i_cm_id,
		 ic->i_pd, ic->i_send_cq, ic->i_recv_cq,
		 ic->i_cm_id ? ic->i_cm_id->qp : NULL);

	if (ic->i_cm_id) {
		struct ib_device *dev = ic->i_cm_id->device;

		rdsdebug("disconnecting cm %p\n", ic->i_cm_id);
		err = rdma_disconnect(ic->i_cm_id);
		if (err) {
			/* Actually this may happen quite frequently, when
			 * an outgoing connect raced with an incoming connect.
			 */
			rdsdebug("rds_iw_conn_shutdown: failed to disconnect,"
				   " cm: %p err %d\n", ic->i_cm_id, err);
		}

		if (ic->i_cm_id->qp) {
			qp_attr.qp_state = IB_QPS_ERR;
			ib_modify_qp(ic->i_cm_id->qp, &qp_attr, IB_QP_STATE);
		}

		wait_event(rds_iw_ring_empty_wait,
			rds_iw_ring_empty(&ic->i_send_ring) &&
			rds_iw_ring_empty(&ic->i_recv_ring));

		if (ic->i_send_hdrs)
			ib_dma_free_coherent(dev,
					   ic->i_send_ring.w_nr *
						sizeof(struct rds_header),
					   ic->i_send_hdrs,
					   ic->i_send_hdrs_dma);

		if (ic->i_recv_hdrs)
			ib_dma_free_coherent(dev,
					   ic->i_recv_ring.w_nr *
						sizeof(struct rds_header),
					   ic->i_recv_hdrs,
					   ic->i_recv_hdrs_dma);

		if (ic->i_ack)
			ib_dma_free_coherent(dev, sizeof(struct rds_header),
					     ic->i_ack, ic->i_ack_dma);

		if (ic->i_sends)
			rds_iw_send_clear_ring(ic);
		if (ic->i_recvs)
			rds_iw_recv_clear_ring(ic);

		if (ic->i_cm_id->qp)
			rdma_destroy_qp(ic->i_cm_id);
		if (ic->i_send_cq)
			ib_destroy_cq(ic->i_send_cq);
		if (ic->i_recv_cq)
			ib_destroy_cq(ic->i_recv_cq);

		/*
		 * If associated with an rds_iw_device:
		 * 	Move connection back to the nodev list.
		 * 	Remove cm_id from the device cm_id list.
		 */
		if (ic->rds_iwdev)
			rds_iw_remove_conn(ic->rds_iwdev, conn);

		rdma_destroy_id(ic->i_cm_id);

		ic->i_cm_id = NULL;
		ic->i_pd = NULL;
		ic->i_mr = NULL;
		ic->i_send_cq = NULL;
		ic->i_recv_cq = NULL;
		ic->i_send_hdrs = NULL;
		ic->i_recv_hdrs = NULL;
		ic->i_ack = NULL;
	}
	BUG_ON(ic->rds_iwdev);

	/* Clear pending transmit */
	if (ic->i_rm) {
		rds_message_put(ic->i_rm);
		ic->i_rm = NULL;
	}

	/* Clear the ACK state */
	clear_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags);
#ifdef KERNEL_HAS_ATOMIC64
	atomic64_set(&ic->i_ack_next, 0);
#else
	ic->i_ack_next = 0;
#endif
	ic->i_ack_recv = 0;

	/* Clear flow control state */
	ic->i_flowctl = 0;
	atomic_set(&ic->i_credits, 0);

	rds_iw_ring_init(&ic->i_send_ring, rds_iw_sysctl_max_send_wr);
	rds_iw_ring_init(&ic->i_recv_ring, rds_iw_sysctl_max_recv_wr);

	if (ic->i_iwinc) {
		rds_inc_put(&ic->i_iwinc->ii_inc);
		ic->i_iwinc = NULL;
	}

	vfree(ic->i_sends);
	ic->i_sends = NULL;
	vfree(ic->i_recvs);
	ic->i_recvs = NULL;
	rdsdebug("shutdown complete\n");
}