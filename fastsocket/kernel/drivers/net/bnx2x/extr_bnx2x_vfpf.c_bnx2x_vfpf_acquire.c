#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_27__ {int /*<<< orphan*/  length; } ;
struct TYPE_24__ {TYPE_3__ tl; } ;
struct TYPE_29__ {int num_sbs; int /*<<< orphan*/  num_mc_filters; int /*<<< orphan*/  num_vlan_filters; int /*<<< orphan*/  num_mac_filters; void* num_rxqs; void* num_txqs; } ;
struct TYPE_26__ {scalar_t__ vf_os; int /*<<< orphan*/  vf_id; } ;
struct vfpf_acquire_tlv {TYPE_16__ first_tlv; TYPE_5__ resc_request; int /*<<< orphan*/  bulletin_addr; TYPE_2__ vfdev_info; } ;
struct TYPE_28__ {int /*<<< orphan*/  status; } ;
struct pfvf_acquire_resp_tlv {TYPE_4__ hdr; } ;
struct channel_list_end_tlv {int dummy; } ;
struct TYPE_21__ {int num_sbs; struct pfvf_acquire_resp_tlv* current_mac_addr; TYPE_10__* hw_sbs; int /*<<< orphan*/  num_mc_filters; int /*<<< orphan*/  num_vlan_filters; int /*<<< orphan*/  num_mac_filters; void* num_rxqs; void* num_txqs; } ;
struct TYPE_19__ {int chip_num; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  db_size; } ;
struct TYPE_31__ {scalar_t__ status; } ;
struct TYPE_23__ {TYPE_13__ resc; TYPE_11__ pfdev_info; TYPE_7__ hdr; } ;
struct TYPE_33__ {int chip_id; scalar_t__ flash_size; int /*<<< orphan*/  chip_port_mode; int /*<<< orphan*/  int_block; } ;
struct TYPE_32__ {int chip_id; } ;
struct bnx2x {int igu_sb_cnt; int igu_dsb_id; int flags; TYPE_15__ acquire_resp; TYPE_12__* dev; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  igu_base_sb; TYPE_9__ common; scalar_t__ mf_mode; scalar_t__ mf_ov; int /*<<< orphan*/  db_size; TYPE_8__ link_params; TYPE_6__* vf2pf_mbox; int /*<<< orphan*/  vf2pf_mbox_mapping; int /*<<< orphan*/  pf2vf_bulletin_mapping; } ;
struct TYPE_22__ {struct pfvf_acquire_resp_tlv acquire_resp; } ;
struct TYPE_25__ {struct vfpf_acquire_tlv acquire; } ;
struct TYPE_30__ {TYPE_14__ resp; TYPE_1__ req; } ;
struct TYPE_20__ {TYPE_15__* dev_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  hw_sb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  CHANNEL_TLV_ACQUIRE ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  CHIP_2_PORT_MODE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EAGAIN ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  INT_BLOCK_IGU ; 
 int NO_FCOE_FLAG ; 
 int NO_ISCSI_FLAG ; 
 int NO_ISCSI_OOO_FLAG ; 
 int NO_WOL_FLAG ; 
 scalar_t__ PFVF_STATUS_NO_RESOURCE ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  VF_ACQUIRE_MAC_FILTERS ; 
 int /*<<< orphan*/  VF_ACQUIRE_MC_FILTERS ; 
 int VF_ACQUIRE_THRESH ; 
 int /*<<< orphan*/  bnx2x_add_tlv (struct bnx2x*,struct vfpf_acquire_tlv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_dp_tlv_list (struct bnx2x*,struct vfpf_acquire_tlv*) ; 
 scalar_t__ bnx2x_get_vf_id (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int bnx2x_send_msg2pf (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfpf_finalize (struct bnx2x*,TYPE_16__*) ; 
 int /*<<< orphan*/  bnx2x_vfpf_prep (struct bnx2x*,TYPE_16__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_valid_ether_addr (struct pfvf_acquire_resp_tlv*) ; 
 int /*<<< orphan*/  memcpy (TYPE_15__*,struct pfvf_acquire_resp_tlv*,int) ; 
 int /*<<< orphan*/  memset (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bnx2x_vfpf_acquire(struct bnx2x *bp, u8 tx_count, u8 rx_count)
{
	int rc = 0, attempts = 0;
	struct vfpf_acquire_tlv *req = &bp->vf2pf_mbox->req.acquire;
	struct pfvf_acquire_resp_tlv *resp = &bp->vf2pf_mbox->resp.acquire_resp;
	u32 vf_id;
	bool resources_acquired = false;

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_ACQUIRE, sizeof(*req));

	if (bnx2x_get_vf_id(bp, &vf_id)) {
		rc = -EAGAIN;
		goto out;
	}

	req->vfdev_info.vf_id = vf_id;
	req->vfdev_info.vf_os = 0;

	req->resc_request.num_rxqs = rx_count;
	req->resc_request.num_txqs = tx_count;
	req->resc_request.num_sbs = bp->igu_sb_cnt;
	req->resc_request.num_mac_filters = VF_ACQUIRE_MAC_FILTERS;
	req->resc_request.num_mc_filters = VF_ACQUIRE_MC_FILTERS;

	/* pf 2 vf bulletin board address */
	req->bulletin_addr = bp->pf2vf_bulletin_mapping;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	while (!resources_acquired) {
		DP(BNX2X_MSG_SP, "attempting to acquire resources\n");

		/* send acquire request */
		rc = bnx2x_send_msg2pf(bp,
				       &resp->hdr.status,
				       bp->vf2pf_mbox_mapping);

		/* PF timeout */
		if (rc)
			goto out;

		/* copy acquire response from buffer to bp */
		memcpy(&bp->acquire_resp, resp, sizeof(bp->acquire_resp));

		attempts++;

		/* test whether the PF accepted our request. If not, humble
		 * the request and try again.
		 */
		if (bp->acquire_resp.hdr.status == PFVF_STATUS_SUCCESS) {
			DP(BNX2X_MSG_SP, "resources acquired\n");
			resources_acquired = true;
		} else if (bp->acquire_resp.hdr.status ==
			   PFVF_STATUS_NO_RESOURCE &&
			   attempts < VF_ACQUIRE_THRESH) {
			DP(BNX2X_MSG_SP,
			   "PF unwilling to fulfill resource request. Try PF recommended amount\n");

			/* humble our request */
			req->resc_request.num_txqs =
				bp->acquire_resp.resc.num_txqs;
			req->resc_request.num_rxqs =
				bp->acquire_resp.resc.num_rxqs;
			req->resc_request.num_sbs =
				bp->acquire_resp.resc.num_sbs;
			req->resc_request.num_mac_filters =
				bp->acquire_resp.resc.num_mac_filters;
			req->resc_request.num_vlan_filters =
				bp->acquire_resp.resc.num_vlan_filters;
			req->resc_request.num_mc_filters =
				bp->acquire_resp.resc.num_mc_filters;

			/* Clear response buffer */
			memset(&bp->vf2pf_mbox->resp, 0,
			       sizeof(union pfvf_tlvs));
		} else {
			/* PF reports error */
			BNX2X_ERR("Failed to get the requested amount of resources: %d. Breaking...\n",
				  bp->acquire_resp.hdr.status);
			rc = -EAGAIN;
			goto out;
		}
	}

	/* get HW info */
	bp->common.chip_id |= (bp->acquire_resp.pfdev_info.chip_num & 0xffff);
	bp->link_params.chip_id = bp->common.chip_id;
	bp->db_size = bp->acquire_resp.pfdev_info.db_size;
	bp->common.int_block = INT_BLOCK_IGU;
	bp->common.chip_port_mode = CHIP_2_PORT_MODE;
	bp->igu_dsb_id = -1;
	bp->mf_ov = 0;
	bp->mf_mode = 0;
	bp->common.flash_size = 0;
	bp->flags |=
		NO_WOL_FLAG | NO_ISCSI_OOO_FLAG | NO_ISCSI_FLAG | NO_FCOE_FLAG;
	bp->igu_sb_cnt = 1;
	bp->igu_base_sb = bp->acquire_resp.resc.hw_sbs[0].hw_sb_id;
	strlcpy(bp->fw_ver, bp->acquire_resp.pfdev_info.fw_ver,
		sizeof(bp->fw_ver));

	if (is_valid_ether_addr(bp->acquire_resp.resc.current_mac_addr))
		memcpy(bp->dev->dev_addr,
		       bp->acquire_resp.resc.current_mac_addr,
		       ETH_ALEN);

out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);
	return rc;
}