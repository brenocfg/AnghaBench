#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  length; } ;
struct TYPE_13__ {TYPE_4__ tl; } ;
struct vfpf_q_op_tlv {int vf_qid; TYPE_6__ first_tlv; } ;
struct TYPE_12__ {int status; } ;
struct pfvf_general_resp_tlv {TYPE_5__ hdr; } ;
struct channel_list_end_tlv {int dummy; } ;
struct bnx2x {int /*<<< orphan*/  vf2pf_mbox_mapping; TYPE_3__* vf2pf_mbox; } ;
struct TYPE_9__ {struct pfvf_general_resp_tlv general_resp; } ;
struct TYPE_8__ {struct vfpf_q_op_tlv q_op; } ;
struct TYPE_10__ {TYPE_2__ resp; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int,int) ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  CHANNEL_TLV_TEARDOWN_Q ; 
 int EINVAL ; 
 int PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  bnx2x_add_tlv (struct bnx2x*,struct vfpf_q_op_tlv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_dp_tlv_list (struct bnx2x*,struct vfpf_q_op_tlv*) ; 
 int bnx2x_send_msg2pf (struct bnx2x*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfpf_finalize (struct bnx2x*,TYPE_6__*) ; 
 int /*<<< orphan*/  bnx2x_vfpf_prep (struct bnx2x*,TYPE_6__*,int /*<<< orphan*/ ,int) ; 

int bnx2x_vfpf_teardown_queue(struct bnx2x *bp, int qidx)
{
	struct vfpf_q_op_tlv *req = &bp->vf2pf_mbox->req.q_op;
	struct pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	int rc;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_TEARDOWN_Q,
			sizeof(*req));

	req->vf_qid = qidx;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);

	if (rc) {
		BNX2X_ERR("Sending TEARDOWN for queue %d failed: %d\n", qidx,
			  rc);
		goto out;
	}

	/* PF failed the transaction */
	if (resp->hdr.status != PFVF_STATUS_SUCCESS) {
		BNX2X_ERR("TEARDOWN for queue %d failed: %d\n", qidx,
			  resp->hdr.status);
		rc = -EINVAL;
	}

out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);
	return rc;
}