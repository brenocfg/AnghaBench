#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_15__ {int /*<<< orphan*/  length; } ;
struct TYPE_19__ {TYPE_5__ tl; } ;
struct vfpf_set_q_filters_tlv {int n_mac_vlan_filters; TYPE_9__ first_tlv; TYPE_6__* filters; int /*<<< orphan*/  vf_qid; int /*<<< orphan*/  flags; } ;
struct TYPE_18__ {int status; } ;
struct pfvf_general_resp_tlv {TYPE_8__ hdr; } ;
struct pf_vf_bulletin_content {int /*<<< orphan*/ * mac; } ;
struct channel_list_end_tlv {int dummy; } ;
struct bnx2x {int /*<<< orphan*/  vf2pf_mbox_mapping; TYPE_7__* dev; TYPE_4__* pf2vf_bulletin; TYPE_3__* vf2pf_mbox; } ;
struct TYPE_17__ {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_16__ {int /*<<< orphan*/ * mac; int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {struct pf_vf_bulletin_content content; } ;
struct TYPE_12__ {struct pfvf_general_resp_tlv general_resp; } ;
struct TYPE_11__ {struct vfpf_set_q_filters_tlv set_q_filters; } ;
struct TYPE_13__ {TYPE_2__ resp; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  CHANNEL_TLV_SET_Q_FILTERS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ PFVF_BULLETIN_UPDATED ; 
 int PFVF_STATUS_FAILURE ; 
 int PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  VFPF_Q_FILTER_DEST_MAC_VALID ; 
 int /*<<< orphan*/  VFPF_Q_FILTER_SET_MAC ; 
 int /*<<< orphan*/  VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED ; 
 int /*<<< orphan*/  bnx2x_add_tlv (struct bnx2x*,struct vfpf_set_q_filters_tlv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_dp_tlv_list (struct bnx2x*,struct vfpf_set_q_filters_tlv*) ; 
 scalar_t__ bnx2x_sample_bulletin (struct bnx2x*) ; 
 int bnx2x_send_msg2pf (struct bnx2x*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfpf_finalize (struct bnx2x*,TYPE_9__*) ; 
 int /*<<< orphan*/  bnx2x_vfpf_prep (struct bnx2x*,TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int bnx2x_vfpf_config_mac(struct bnx2x *bp, u8 *addr, u8 vf_qid, bool set)
{
	struct vfpf_set_q_filters_tlv *req = &bp->vf2pf_mbox->req.set_q_filters;
	struct pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	struct pf_vf_bulletin_content bulletin = bp->pf2vf_bulletin->content;
	int rc = 0;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SET_Q_FILTERS,
			sizeof(*req));

	req->flags = VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED;
	req->vf_qid = vf_qid;
	req->n_mac_vlan_filters = 1;

	req->filters[0].flags = VFPF_Q_FILTER_DEST_MAC_VALID;
	if (set)
		req->filters[0].flags |= VFPF_Q_FILTER_SET_MAC;

	/* sample bulletin board for new mac */
	bnx2x_sample_bulletin(bp);

	/* copy mac from device to request */
	memcpy(req->filters[0].mac, addr, ETH_ALEN);

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	/* send message to pf */
	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	if (rc) {
		BNX2X_ERR("failed to send message to pf. rc was %d\n", rc);
		goto out;
	}

	/* failure may mean PF was configured with a new mac for us */
	while (resp->hdr.status == PFVF_STATUS_FAILURE) {
		DP(BNX2X_MSG_IOV,
		   "vfpf SET MAC failed. Check bulletin board for new posts\n");

		/* copy mac from bulletin to device */
		memcpy(bp->dev->dev_addr, bulletin.mac, ETH_ALEN);

		/* check if bulletin board was updated */
		if (bnx2x_sample_bulletin(bp) == PFVF_BULLETIN_UPDATED) {
			/* copy mac from device to request */
			memcpy(req->filters[0].mac, bp->dev->dev_addr,
			       ETH_ALEN);

			/* send message to pf */
			rc = bnx2x_send_msg2pf(bp, &resp->hdr.status,
					       bp->vf2pf_mbox_mapping);
		} else {
			/* no new info in bulletin */
			break;
		}
	}

	if (resp->hdr.status != PFVF_STATUS_SUCCESS) {
		BNX2X_ERR("vfpf SET MAC failed: %d\n", resp->hdr.status);
		rc = -EINVAL;
	}
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	return 0;
}