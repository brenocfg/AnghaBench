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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2x_virtf {int /*<<< orphan*/  leading_rss; int /*<<< orphan*/  filter_state; int /*<<< orphan*/  mcast_obj; int /*<<< orphan*/  abs_vfid; } ;
struct TYPE_2__ {int /*<<< orphan*/  func_id; } ;
struct bnx2x_vf_queue {int /*<<< orphan*/  cid; int /*<<< orphan*/  vlan_obj; int /*<<< orphan*/  mac_obj; TYPE_1__ sp_obj; } ;
struct bnx2x {int /*<<< orphan*/  vlans_pool; int /*<<< orphan*/  macs_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FILTER_MAC_PENDING ; 
 int /*<<< orphan*/  BNX2X_FILTER_MCAST_PENDING ; 
 int /*<<< orphan*/  BNX2X_FILTER_VLAN_PENDING ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BNX2X_OBJ_TYPE_RX_TX ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_RX ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_TX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_VF_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_mac_obj (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_init_mcast_obj (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_queue_obj (struct bnx2x*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bnx2x_init_vlan_obj (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_vf_sp (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_sp_map (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_rdata ; 
 int /*<<< orphan*/  mcast_rdata ; 
 int /*<<< orphan*/  q_data ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  vfq_cl_id (struct bnx2x_virtf*,struct bnx2x_vf_queue*) ; 
 scalar_t__ vfq_is_leading (struct bnx2x_vf_queue*) ; 
 int /*<<< orphan*/  vlan_rdata ; 

__attribute__((used)) static void bnx2x_vfq_init(struct bnx2x *bp, struct bnx2x_virtf *vf,
			   struct bnx2x_vf_queue *q)
{
	u8 cl_id = vfq_cl_id(vf, q);
	u8 func_id = FW_VF_HANDLE(vf->abs_vfid);
	unsigned long q_type = 0;

	set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);
	set_bit(BNX2X_Q_TYPE_HAS_RX, &q_type);

	/* Queue State object */
	bnx2x_init_queue_obj(bp, &q->sp_obj,
			     cl_id, &q->cid, 1, func_id,
			     bnx2x_vf_sp(bp, vf, q_data),
			     bnx2x_vf_sp_map(bp, vf, q_data),
			     q_type);

	DP(BNX2X_MSG_IOV,
	   "initialized vf %d's queue object. func id set to %d\n",
	   vf->abs_vfid, q->sp_obj.func_id);

	/* mac/vlan objects are per queue, but only those
	 * that belong to the leading queue are initialized
	 */
	if (vfq_is_leading(q)) {
		/* mac */
		bnx2x_init_mac_obj(bp, &q->mac_obj,
				   cl_id, q->cid, func_id,
				   bnx2x_vf_sp(bp, vf, mac_rdata),
				   bnx2x_vf_sp_map(bp, vf, mac_rdata),
				   BNX2X_FILTER_MAC_PENDING,
				   &vf->filter_state,
				   BNX2X_OBJ_TYPE_RX_TX,
				   &bp->macs_pool);
		/* vlan */
		bnx2x_init_vlan_obj(bp, &q->vlan_obj,
				    cl_id, q->cid, func_id,
				    bnx2x_vf_sp(bp, vf, vlan_rdata),
				    bnx2x_vf_sp_map(bp, vf, vlan_rdata),
				    BNX2X_FILTER_VLAN_PENDING,
				    &vf->filter_state,
				    BNX2X_OBJ_TYPE_RX_TX,
				    &bp->vlans_pool);

		/* mcast */
		bnx2x_init_mcast_obj(bp, &vf->mcast_obj, cl_id,
				     q->cid, func_id, func_id,
				     bnx2x_vf_sp(bp, vf, mcast_rdata),
				     bnx2x_vf_sp_map(bp, vf, mcast_rdata),
				     BNX2X_FILTER_MCAST_PENDING,
				     &vf->filter_state,
				     BNX2X_OBJ_TYPE_RX_TX);

		vf->leading_rss = cl_id;
	}
}