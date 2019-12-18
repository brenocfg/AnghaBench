#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dlid; } ;
struct ib_qp_attr {TYPE_4__ alt_ah_attr; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; void* rq_psn; void* dest_qp_num; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  ah_attr; } ;
struct TYPE_10__ {TYPE_4__ ah_attr; int /*<<< orphan*/  timeout; int /*<<< orphan*/  pkey_index; TYPE_3__* port; } ;
struct TYPE_7__ {int /*<<< orphan*/  ah_attr; } ;
struct TYPE_6__ {int state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; TYPE_5__ alt_av; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  path_mtu; TYPE_2__ av; TYPE_1__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_CM_ESTABLISHED 134 
#define  IB_CM_MRA_REP_RCVD 133 
#define  IB_CM_MRA_REP_SENT 132 
#define  IB_CM_MRA_REQ_SENT 131 
#define  IB_CM_REP_RCVD 130 
#define  IB_CM_REP_SENT 129 
#define  IB_CM_REQ_RCVD 128 
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_QPT_XRC_TGT ; 
 int IB_QP_ALT_PATH ; 
 int IB_QP_AV ; 
 int IB_QP_DEST_QPN ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MIN_RNR_TIMER ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_RQ_PSN ; 
 int IB_QP_STATE ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cm_init_qp_rtr_attr(struct cm_id_private *cm_id_priv,
			       struct ib_qp_attr *qp_attr,
			       int *qp_attr_mask)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	switch (cm_id_priv->id.state) {
	case IB_CM_REQ_RCVD:
	case IB_CM_MRA_REQ_SENT:
	case IB_CM_REP_RCVD:
	case IB_CM_MRA_REP_SENT:
	case IB_CM_REP_SENT:
	case IB_CM_MRA_REP_RCVD:
	case IB_CM_ESTABLISHED:
		*qp_attr_mask = IB_QP_STATE | IB_QP_AV | IB_QP_PATH_MTU |
				IB_QP_DEST_QPN | IB_QP_RQ_PSN;
		qp_attr->ah_attr = cm_id_priv->av.ah_attr;
		qp_attr->path_mtu = cm_id_priv->path_mtu;
		qp_attr->dest_qp_num = be32_to_cpu(cm_id_priv->remote_qpn);
		qp_attr->rq_psn = be32_to_cpu(cm_id_priv->rq_psn);
		if (cm_id_priv->qp_type == IB_QPT_RC ||
		    cm_id_priv->qp_type == IB_QPT_XRC_TGT) {
			*qp_attr_mask |= IB_QP_MAX_DEST_RD_ATOMIC |
					 IB_QP_MIN_RNR_TIMER;
			qp_attr->max_dest_rd_atomic =
					cm_id_priv->responder_resources;
			qp_attr->min_rnr_timer = 0;
		}
		if (cm_id_priv->alt_av.ah_attr.dlid) {
			*qp_attr_mask |= IB_QP_ALT_PATH;
			qp_attr->alt_port_num = cm_id_priv->alt_av.port->port_num;
			qp_attr->alt_pkey_index = cm_id_priv->alt_av.pkey_index;
			qp_attr->alt_timeout = cm_id_priv->alt_av.timeout;
			qp_attr->alt_ah_attr = cm_id_priv->alt_av.ah_attr;
		}
		ret = 0;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	return ret;
}