#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct cm_rej_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  ari; int /*<<< orphan*/  reason; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  remote_comm_id; int /*<<< orphan*/  hdr; } ;
struct TYPE_2__ {int state; int /*<<< orphan*/  local_id; int /*<<< orphan*/  remote_id; } ;
struct cm_id_private {TYPE_1__ id; int /*<<< orphan*/  tid; } ;
typedef  enum ib_cm_rej_reason { ____Placeholder_ib_cm_rej_reason } ib_cm_rej_reason ;

/* Variables and functions */
 int /*<<< orphan*/  CM_MSG_RESPONSE_OTHER ; 
 int /*<<< orphan*/  CM_MSG_RESPONSE_REP ; 
 int /*<<< orphan*/  CM_MSG_RESPONSE_REQ ; 
 int /*<<< orphan*/  CM_REJ_ATTR_ID ; 
#define  IB_CM_MRA_REP_SENT 131 
#define  IB_CM_MRA_REQ_SENT 130 
#define  IB_CM_REP_RCVD 129 
#define  IB_CM_REQ_RCVD 128 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rej_set_msg_rejected (struct cm_rej_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rej_set_reject_info_len (struct cm_rej_msg*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static void cm_format_rej(struct cm_rej_msg *rej_msg,
			  struct cm_id_private *cm_id_priv,
			  enum ib_cm_rej_reason reason,
			  void *ari,
			  u8 ari_length,
			  const void *private_data,
			  u8 private_data_len)
{
	cm_format_mad_hdr(&rej_msg->hdr, CM_REJ_ATTR_ID, cm_id_priv->tid);
	rej_msg->remote_comm_id = cm_id_priv->id.remote_id;

	switch(cm_id_priv->id.state) {
	case IB_CM_REQ_RCVD:
		rej_msg->local_comm_id = 0;
		cm_rej_set_msg_rejected(rej_msg, CM_MSG_RESPONSE_REQ);
		break;
	case IB_CM_MRA_REQ_SENT:
		rej_msg->local_comm_id = cm_id_priv->id.local_id;
		cm_rej_set_msg_rejected(rej_msg, CM_MSG_RESPONSE_REQ);
		break;
	case IB_CM_REP_RCVD:
	case IB_CM_MRA_REP_SENT:
		rej_msg->local_comm_id = cm_id_priv->id.local_id;
		cm_rej_set_msg_rejected(rej_msg, CM_MSG_RESPONSE_REP);
		break;
	default:
		rej_msg->local_comm_id = cm_id_priv->id.local_id;
		cm_rej_set_msg_rejected(rej_msg, CM_MSG_RESPONSE_OTHER);
		break;
	}

	rej_msg->reason = cpu_to_be16(reason);
	if (ari && ari_length) {
		cm_rej_set_reject_info_len(rej_msg, ari_length);
		memcpy(rej_msg->ari, ari, ari_length);
	}

	if (private_data && private_data_len)
		memcpy(rej_msg->private_data, private_data, private_data_len);
}