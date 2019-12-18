#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  service_timeout; } ;
struct TYPE_17__ {TYPE_3__ mra_rcvd; } ;
struct TYPE_18__ {TYPE_4__ param; int /*<<< orphan*/ * private_data; } ;
struct cm_work {int /*<<< orphan*/  list; TYPE_9__* port; TYPE_5__ cm_event; TYPE_2__* mad_recv_wc; } ;
struct cm_mra_msg {int /*<<< orphan*/  private_data; } ;
struct TYPE_12__ {int state; int /*<<< orphan*/  lap_state; } ;
struct TYPE_20__ {TYPE_6__* port; int /*<<< orphan*/  timeout; } ;
struct cm_id_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_count; TYPE_10__ id; TYPE_11__* msg; TYPE_7__ av; } ;
struct TYPE_22__ {TYPE_8__* counter_group; } ;
struct TYPE_21__ {int /*<<< orphan*/ * counter; } ;
struct TYPE_19__ {int /*<<< orphan*/  mad_agent; } ;
struct TYPE_14__ {scalar_t__ mad; } ;
struct TYPE_15__ {TYPE_1__ recv_buf; } ;
struct TYPE_13__ {void** context; } ;

/* Variables and functions */
 size_t CM_MRA_COUNTER ; 
 int /*<<< orphan*/  CM_MSG_RESPONSE_OTHER ; 
 int /*<<< orphan*/  CM_MSG_RESPONSE_REP ; 
 int /*<<< orphan*/  CM_MSG_RESPONSE_REQ ; 
 size_t CM_RECV_DUPLICATES ; 
 int EINVAL ; 
#define  IB_CM_ESTABLISHED 132 
 int /*<<< orphan*/  IB_CM_LAP_SENT ; 
 int /*<<< orphan*/  IB_CM_MRA_LAP_RCVD ; 
#define  IB_CM_MRA_REP_RCVD 131 
#define  IB_CM_MRA_REQ_RCVD 130 
#define  IB_CM_REP_SENT 129 
#define  IB_CM_REQ_SENT 128 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct cm_id_private* cm_acquire_mraed_id (struct cm_mra_msg*) ; 
 int cm_convert_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_mra_get_msg_mraed (struct cm_mra_msg*) ; 
 int /*<<< orphan*/  cm_mra_get_service_timeout (struct cm_mra_msg*) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 int /*<<< orphan*/  ib_modify_mad (int /*<<< orphan*/ ,TYPE_11__*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_mra_handler(struct cm_work *work)
{
	struct cm_id_private *cm_id_priv;
	struct cm_mra_msg *mra_msg;
	int timeout, ret;

	mra_msg = (struct cm_mra_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_mraed_id(mra_msg);
	if (!cm_id_priv)
		return -EINVAL;

	work->cm_event.private_data = &mra_msg->private_data;
	work->cm_event.param.mra_rcvd.service_timeout =
					cm_mra_get_service_timeout(mra_msg);
	timeout = cm_convert_to_ms(cm_mra_get_service_timeout(mra_msg)) +
		  cm_convert_to_ms(cm_id_priv->av.timeout);

	spin_lock_irq(&cm_id_priv->lock);
	switch (cm_id_priv->id.state) {
	case IB_CM_REQ_SENT:
		if (cm_mra_get_msg_mraed(mra_msg) != CM_MSG_RESPONSE_REQ ||
		    ib_modify_mad(cm_id_priv->av.port->mad_agent,
				  cm_id_priv->msg, timeout))
			goto out;
		cm_id_priv->id.state = IB_CM_MRA_REQ_RCVD;
		break;
	case IB_CM_REP_SENT:
		if (cm_mra_get_msg_mraed(mra_msg) != CM_MSG_RESPONSE_REP ||
		    ib_modify_mad(cm_id_priv->av.port->mad_agent,
				  cm_id_priv->msg, timeout))
			goto out;
		cm_id_priv->id.state = IB_CM_MRA_REP_RCVD;
		break;
	case IB_CM_ESTABLISHED:
		if (cm_mra_get_msg_mraed(mra_msg) != CM_MSG_RESPONSE_OTHER ||
		    cm_id_priv->id.lap_state != IB_CM_LAP_SENT ||
		    ib_modify_mad(cm_id_priv->av.port->mad_agent,
				  cm_id_priv->msg, timeout)) {
			if (cm_id_priv->id.lap_state == IB_CM_MRA_LAP_RCVD)
				atomic_long_inc(&work->port->
						counter_group[CM_RECV_DUPLICATES].
						counter[CM_MRA_COUNTER]);
			goto out;
		}
		cm_id_priv->id.lap_state = IB_CM_MRA_LAP_RCVD;
		break;
	case IB_CM_MRA_REQ_RCVD:
	case IB_CM_MRA_REP_RCVD:
		atomic_long_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_MRA_COUNTER]);
		/* fall through */
	default:
		goto out;
	}

	cm_id_priv->msg->context[1] = (void *) (unsigned long)
				      cm_id_priv->id.state;
	ret = atomic_inc_and_test(&cm_id_priv->work_count);
	if (!ret)
		list_add_tail(&work->list, &cm_id_priv->work_list);
	spin_unlock_irq(&cm_id_priv->lock);

	if (ret)
		cm_process_work(cm_id_priv, work);
	else
		cm_deref_id(cm_id_priv);
	return 0;
out:
	spin_unlock_irq(&cm_id_priv->lock);
	cm_deref_id(cm_id_priv);
	return -EINVAL;
}