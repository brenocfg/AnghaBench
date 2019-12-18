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
struct TYPE_6__ {int /*<<< orphan*/  qp_type; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  max_sge; } ;
struct ipath_qp {int s_flags; TYPE_3__ ibqp; int /*<<< orphan*/  s_rnr_retry_cnt; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  r_min_rnr_timer; int /*<<< orphan*/  r_max_rd_atomic; int /*<<< orphan*/  s_max_rd_atomic; int /*<<< orphan*/  s_draining; int /*<<< orphan*/  s_pkey_index; int /*<<< orphan*/  remote_ah_attr; TYPE_1__ r_rq; int /*<<< orphan*/  s_max_sge; scalar_t__ s_size; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  s_next_psn; int /*<<< orphan*/  r_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int max_recv_wr; scalar_t__ max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; scalar_t__ max_send_wr; } ;
struct ib_qp_init_attr {int port_num; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; TYPE_2__ cap; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct ib_qp_attr {int port_num; TYPE_2__ cap; scalar_t__ alt_timeout; scalar_t__ alt_port_num; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  sq_draining; scalar_t__ en_sqd_async_notify; scalar_t__ alt_pkey_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  qkey; scalar_t__ path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  cur_qp_state; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 int /*<<< orphan*/  IB_SIGNAL_REQ_WR ; 
 int IPATH_S_SIGNAL_REQ_WR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ipath_qp* to_iqp (struct ib_qp*) ; 

int ipath_query_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
		   int attr_mask, struct ib_qp_init_attr *init_attr)
{
	struct ipath_qp *qp = to_iqp(ibqp);

	attr->qp_state = qp->state;
	attr->cur_qp_state = attr->qp_state;
	attr->path_mtu = qp->path_mtu;
	attr->path_mig_state = 0;
	attr->qkey = qp->qkey;
	attr->rq_psn = qp->r_psn;
	attr->sq_psn = qp->s_next_psn;
	attr->dest_qp_num = qp->remote_qpn;
	attr->qp_access_flags = qp->qp_access_flags;
	attr->cap.max_send_wr = qp->s_size - 1;
	attr->cap.max_recv_wr = qp->ibqp.srq ? 0 : qp->r_rq.size - 1;
	attr->cap.max_send_sge = qp->s_max_sge;
	attr->cap.max_recv_sge = qp->r_rq.max_sge;
	attr->cap.max_inline_data = 0;
	attr->ah_attr = qp->remote_ah_attr;
	memset(&attr->alt_ah_attr, 0, sizeof(attr->alt_ah_attr));
	attr->pkey_index = qp->s_pkey_index;
	attr->alt_pkey_index = 0;
	attr->en_sqd_async_notify = 0;
	attr->sq_draining = qp->s_draining;
	attr->max_rd_atomic = qp->s_max_rd_atomic;
	attr->max_dest_rd_atomic = qp->r_max_rd_atomic;
	attr->min_rnr_timer = qp->r_min_rnr_timer;
	attr->port_num = 1;
	attr->timeout = qp->timeout;
	attr->retry_cnt = qp->s_retry_cnt;
	attr->rnr_retry = qp->s_rnr_retry_cnt;
	attr->alt_port_num = 0;
	attr->alt_timeout = 0;

	init_attr->event_handler = qp->ibqp.event_handler;
	init_attr->qp_context = qp->ibqp.qp_context;
	init_attr->send_cq = qp->ibqp.send_cq;
	init_attr->recv_cq = qp->ibqp.recv_cq;
	init_attr->srq = qp->ibqp.srq;
	init_attr->cap = attr->cap;
	if (qp->s_flags & IPATH_S_SIGNAL_REQ_WR)
		init_attr->sq_sig_type = IB_SIGNAL_REQ_WR;
	else
		init_attr->sq_sig_type = IB_SIGNAL_ALL_WR;
	init_attr->qp_type = qp->ibqp.qp_type;
	init_attr->port_num = 1;
	return 0;
}