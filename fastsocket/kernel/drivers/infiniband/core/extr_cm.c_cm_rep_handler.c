#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct cm_work {int /*<<< orphan*/  list; TYPE_7__* mad_recv_wc; int /*<<< orphan*/  port; } ;
struct cm_rep_msg {int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  resp_resources; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  local_ca_guid; int /*<<< orphan*/  remote_comm_id; } ;
struct TYPE_17__ {TYPE_5__* port; void* timeout; } ;
struct TYPE_15__ {void* timeout; } ;
struct TYPE_14__ {int state; int /*<<< orphan*/  remote_id; } ;
struct cm_id_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_count; int /*<<< orphan*/  msg; TYPE_6__ av; TYPE_4__ alt_av; int /*<<< orphan*/  target_ack_delay; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  qp_type; void* remote_qpn; TYPE_3__ id; TYPE_8__* timewait_info; } ;
struct TYPE_13__ {int /*<<< orphan*/  remote_id; } ;
struct TYPE_19__ {scalar_t__ inserted_remote_id; int /*<<< orphan*/  remote_id_node; void* remote_qpn; int /*<<< orphan*/  remote_ca_guid; TYPE_2__ work; } ;
struct TYPE_12__ {scalar_t__ mad; } ;
struct TYPE_18__ {TYPE_1__ recv_buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  mad_agent; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  remote_id_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_MSG_RESPONSE_REP ; 
 int EINVAL ; 
#define  IB_CM_MRA_REQ_RCVD 129 
 int /*<<< orphan*/  IB_CM_REJ_STALE_CONN ; 
 int IB_CM_REP_RCVD ; 
#define  IB_CM_REQ_SENT 128 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 TYPE_10__ cm ; 
 void* cm_ack_timeout (int /*<<< orphan*/ ,void*) ; 
 struct cm_id_private* cm_acquire_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_dup_rep_handler (struct cm_work*) ; 
 int /*<<< orphan*/  cm_format_rep_event (struct cm_work*,int /*<<< orphan*/ ) ; 
 scalar_t__ cm_insert_remote_id (TYPE_8__*) ; 
 scalar_t__ cm_insert_remote_qpn (TYPE_8__*) ; 
 int /*<<< orphan*/  cm_issue_rej (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 void* cm_rep_get_qpn (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_get_rnr_retry_count (struct cm_rep_msg*) ; 
 int /*<<< orphan*/  cm_rep_get_starting_psn (struct cm_rep_msg*) ; 
 int /*<<< orphan*/  cm_rep_get_target_ack_delay (struct cm_rep_msg*) ; 
 int /*<<< orphan*/  ib_cancel_mad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_rep_handler(struct cm_work *work)
{
	struct cm_id_private *cm_id_priv;
	struct cm_rep_msg *rep_msg;
	int ret;

	rep_msg = (struct cm_rep_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(rep_msg->remote_comm_id, 0);
	if (!cm_id_priv) {
		cm_dup_rep_handler(work);
		return -EINVAL;
	}

	cm_format_rep_event(work, cm_id_priv->qp_type);

	spin_lock_irq(&cm_id_priv->lock);
	switch (cm_id_priv->id.state) {
	case IB_CM_REQ_SENT:
	case IB_CM_MRA_REQ_RCVD:
		break;
	default:
		spin_unlock_irq(&cm_id_priv->lock);
		ret = -EINVAL;
		goto error;
	}

	cm_id_priv->timewait_info->work.remote_id = rep_msg->local_comm_id;
	cm_id_priv->timewait_info->remote_ca_guid = rep_msg->local_ca_guid;
	cm_id_priv->timewait_info->remote_qpn = cm_rep_get_qpn(rep_msg, cm_id_priv->qp_type);

	spin_lock(&cm.lock);
	/* Check for duplicate REP. */
	if (cm_insert_remote_id(cm_id_priv->timewait_info)) {
		spin_unlock(&cm.lock);
		spin_unlock_irq(&cm_id_priv->lock);
		ret = -EINVAL;
		goto error;
	}
	/* Check for a stale connection. */
	if (cm_insert_remote_qpn(cm_id_priv->timewait_info)) {
		rb_erase(&cm_id_priv->timewait_info->remote_id_node,
			 &cm.remote_id_table);
		cm_id_priv->timewait_info->inserted_remote_id = 0;
		spin_unlock(&cm.lock);
		spin_unlock_irq(&cm_id_priv->lock);
		cm_issue_rej(work->port, work->mad_recv_wc,
			     IB_CM_REJ_STALE_CONN, CM_MSG_RESPONSE_REP,
			     NULL, 0);
		ret = -EINVAL;
		goto error;
	}
	spin_unlock(&cm.lock);

	cm_id_priv->id.state = IB_CM_REP_RCVD;
	cm_id_priv->id.remote_id = rep_msg->local_comm_id;
	cm_id_priv->remote_qpn = cm_rep_get_qpn(rep_msg, cm_id_priv->qp_type);
	cm_id_priv->initiator_depth = rep_msg->resp_resources;
	cm_id_priv->responder_resources = rep_msg->initiator_depth;
	cm_id_priv->sq_psn = cm_rep_get_starting_psn(rep_msg);
	cm_id_priv->rnr_retry_count = cm_rep_get_rnr_retry_count(rep_msg);
	cm_id_priv->target_ack_delay = cm_rep_get_target_ack_delay(rep_msg);
	cm_id_priv->av.timeout =
			cm_ack_timeout(cm_id_priv->target_ack_delay,
				       cm_id_priv->av.timeout - 1);
	cm_id_priv->alt_av.timeout =
			cm_ack_timeout(cm_id_priv->target_ack_delay,
				       cm_id_priv->alt_av.timeout - 1);

	/* todo: handle peer_to_peer */

	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	ret = atomic_inc_and_test(&cm_id_priv->work_count);
	if (!ret)
		list_add_tail(&work->list, &cm_id_priv->work_list);
	spin_unlock_irq(&cm_id_priv->lock);

	if (ret)
		cm_process_work(cm_id_priv, work);
	else
		cm_deref_id(cm_id_priv);
	return 0;

error:
	cm_deref_id(cm_id_priv);
	return ret;
}