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
struct ib_qp_attr {void* path_mig_state; TYPE_4__ alt_ah_attr; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  sq_psn; } ;
struct TYPE_10__ {TYPE_4__ ah_attr; int /*<<< orphan*/  timeout; int /*<<< orphan*/  pkey_index; TYPE_3__* port; } ;
struct TYPE_7__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_6__ {int state; int /*<<< orphan*/  lap_state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; TYPE_5__ alt_av; TYPE_2__ av; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_psn; TYPE_1__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_CM_ESTABLISHED 137 
 int /*<<< orphan*/  IB_CM_LAP_UNINIT ; 
#define  IB_CM_MRA_REP_RCVD 136 
#define  IB_CM_MRA_REP_SENT 135 
#define  IB_CM_MRA_REQ_SENT 134 
#define  IB_CM_REP_RCVD 133 
#define  IB_CM_REP_SENT 132 
#define  IB_CM_REQ_RCVD 131 
 void* IB_MIG_REARM ; 
#define  IB_QPT_RC 130 
#define  IB_QPT_XRC_INI 129 
#define  IB_QPT_XRC_TGT 128 
 int IB_QP_ALT_PATH ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_PATH_MIG_STATE ; 
 int IB_QP_RETRY_CNT ; 
 int IB_QP_RNR_RETRY ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int IB_QP_TIMEOUT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cm_init_qp_rts_attr(struct cm_id_private *cm_id_priv,
			       struct ib_qp_attr *qp_attr,
			       int *qp_attr_mask)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	switch (cm_id_priv->id.state) {
	/* Allow transition to RTS before sending REP */
	case IB_CM_REQ_RCVD:
	case IB_CM_MRA_REQ_SENT:

	case IB_CM_REP_RCVD:
	case IB_CM_MRA_REP_SENT:
	case IB_CM_REP_SENT:
	case IB_CM_MRA_REP_RCVD:
	case IB_CM_ESTABLISHED:
		if (cm_id_priv->id.lap_state == IB_CM_LAP_UNINIT) {
			*qp_attr_mask = IB_QP_STATE | IB_QP_SQ_PSN;
			qp_attr->sq_psn = be32_to_cpu(cm_id_priv->sq_psn);
			switch (cm_id_priv->qp_type) {
			case IB_QPT_RC:
			case IB_QPT_XRC_INI:
				*qp_attr_mask |= IB_QP_RETRY_CNT | IB_QP_RNR_RETRY |
						 IB_QP_MAX_QP_RD_ATOMIC;
				qp_attr->retry_cnt = cm_id_priv->retry_count;
				qp_attr->rnr_retry = cm_id_priv->rnr_retry_count;
				qp_attr->max_rd_atomic = cm_id_priv->initiator_depth;
				/* fall through */
			case IB_QPT_XRC_TGT:
				*qp_attr_mask |= IB_QP_TIMEOUT;
				qp_attr->timeout = cm_id_priv->av.timeout;
				break;
			default:
				break;
			}
			if (cm_id_priv->alt_av.ah_attr.dlid) {
				*qp_attr_mask |= IB_QP_PATH_MIG_STATE;
				qp_attr->path_mig_state = IB_MIG_REARM;
			}
		} else {
			*qp_attr_mask = IB_QP_ALT_PATH | IB_QP_PATH_MIG_STATE;
			qp_attr->alt_port_num = cm_id_priv->alt_av.port->port_num;
			qp_attr->alt_pkey_index = cm_id_priv->alt_av.pkey_index;
			qp_attr->alt_timeout = cm_id_priv->alt_av.timeout;
			qp_attr->alt_ah_attr = cm_id_priv->alt_av.ah_attr;
			qp_attr->path_mig_state = IB_MIG_REARM;
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