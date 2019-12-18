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
struct vfpf_set_q_filters_tlv {int flags; int rx_mask; int /*<<< orphan*/  vf_qid; int /*<<< orphan*/  n_multicast; int /*<<< orphan*/  multicast; } ;
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; int /*<<< orphan*/  index; } ;
struct bnx2x_vfop_filters {int dummy; } ;
struct bnx2x_vfop_cmd {void (* done ) (struct bnx2x*,struct bnx2x_virtf*) ;int block; } ;
struct bnx2x_vfop {int state; scalar_t__ rc; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vfop_filters_state { ____Placeholder_bnx2x_vfop_filters_state } bnx2x_vfop_filters_state ;
struct TYPE_6__ {TYPE_2__* msg; } ;
struct TYPE_4__ {struct vfpf_set_q_filters_tlv set_q_filters; } ;
struct TYPE_5__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ACCEPT_ALL_MULTICAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_ALL_UNICAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_ANY_VLAN ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_BROADCAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_MULTICAST ; 
 int /*<<< orphan*/  BNX2X_ACCEPT_UNICAST ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
#define  BNX2X_VFOP_MBX_Q_FILTERS_DONE 132 
#define  BNX2X_VFOP_MBX_Q_FILTERS_MACS 131 
#define  BNX2X_VFOP_MBX_Q_FILTERS_MCAST 130 
#define  BNX2X_VFOP_MBX_Q_FILTERS_RXMODE 129 
#define  BNX2X_VFOP_MBX_Q_FILTERS_VLANS 128 
 TYPE_3__* BP_VF_MBX (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VFPF_MAC_FILTER ; 
 int VFPF_RX_MASK_ACCEPT_ALL_MULTICAST ; 
 int VFPF_RX_MASK_ACCEPT_ALL_UNICAST ; 
 int VFPF_RX_MASK_ACCEPT_BROADCAST ; 
 int VFPF_RX_MASK_ACCEPT_MATCHED_MULTICAST ; 
 int VFPF_RX_MASK_ACCEPT_MATCHED_UNICAST ; 
 int VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED ; 
 int VFPF_SET_Q_FILTERS_MULTICAST_CHANGED ; 
 int VFPF_SET_Q_FILTERS_RX_MASK_CHANGED ; 
 int /*<<< orphan*/  VFPF_VLAN_FILTER ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 void* bnx2x_vf_mbx_macvlan_list (struct bnx2x*,struct bnx2x_virtf*,struct vfpf_set_q_filters_tlv*,struct bnx2x_vfop_filters**,int /*<<< orphan*/ ) ; 
 struct bnx2x_vfop* bnx2x_vfop_cur (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_default (int) ; 
 int /*<<< orphan*/  bnx2x_vfop_end (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop*) ; 
 int bnx2x_vfop_mac_list_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*,struct bnx2x_vfop_filters*,int /*<<< orphan*/ ,int) ; 
 int bnx2x_vfop_mcast_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bnx2x_vfop_rxmode_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*,int /*<<< orphan*/ ,unsigned long) ; 
 int bnx2x_vfop_vlan_list_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*,struct bnx2x_vfop_filters*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_vfop_mbx_qfilters(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	int rc;

	struct vfpf_set_q_filters_tlv *msg =
		&BP_VF_MBX(bp, vf->index)->msg->req.set_q_filters;

	struct bnx2x_vfop *vfop = bnx2x_vfop_cur(bp, vf);
	enum bnx2x_vfop_filters_state state = vfop->state;

	struct bnx2x_vfop_cmd cmd = {
		.done = bnx2x_vfop_mbx_qfilters,
		.block = false,
	};

	DP(BNX2X_MSG_IOV, "STATE: %d\n", state);

	if (vfop->rc < 0)
		goto op_err;

	switch (state) {
	case BNX2X_VFOP_MBX_Q_FILTERS_MACS:
		/* next state */
		vfop->state = BNX2X_VFOP_MBX_Q_FILTERS_VLANS;

		/* check for any vlan/mac changes */
		if (msg->flags & VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED) {
			/* build mac list */
			struct bnx2x_vfop_filters *fl = NULL;

			vfop->rc = bnx2x_vf_mbx_macvlan_list(bp, vf, msg, &fl,
							     VFPF_MAC_FILTER);
			if (vfop->rc)
				goto op_err;

			if (fl) {
				/* set mac list */
				rc = bnx2x_vfop_mac_list_cmd(bp, vf, &cmd, fl,
							     msg->vf_qid,
							     false);
				if (rc) {
					vfop->rc = rc;
					goto op_err;
				}
				return;
			}
		}
		/* fall through */

	case BNX2X_VFOP_MBX_Q_FILTERS_VLANS:
		/* next state */
		vfop->state = BNX2X_VFOP_MBX_Q_FILTERS_RXMODE;

		/* check for any vlan/mac changes */
		if (msg->flags & VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED) {
			/* build vlan list */
			struct bnx2x_vfop_filters *fl = NULL;

			vfop->rc = bnx2x_vf_mbx_macvlan_list(bp, vf, msg, &fl,
							     VFPF_VLAN_FILTER);
			if (vfop->rc)
				goto op_err;

			if (fl) {
				/* set vlan list */
				rc = bnx2x_vfop_vlan_list_cmd(bp, vf, &cmd, fl,
							      msg->vf_qid,
							      false);
				if (rc) {
					vfop->rc = rc;
					goto op_err;
				}
				return;
			}
		}
		/* fall through */

	case BNX2X_VFOP_MBX_Q_FILTERS_RXMODE:
		/* next state */
		vfop->state = BNX2X_VFOP_MBX_Q_FILTERS_MCAST;

		if (msg->flags & VFPF_SET_Q_FILTERS_RX_MASK_CHANGED) {
			unsigned long accept = 0;

			/* covert VF-PF if mask to bnx2x accept flags */
			if (msg->rx_mask & VFPF_RX_MASK_ACCEPT_MATCHED_UNICAST)
				__set_bit(BNX2X_ACCEPT_UNICAST, &accept);

			if (msg->rx_mask &
					VFPF_RX_MASK_ACCEPT_MATCHED_MULTICAST)
				__set_bit(BNX2X_ACCEPT_MULTICAST, &accept);

			if (msg->rx_mask & VFPF_RX_MASK_ACCEPT_ALL_UNICAST)
				__set_bit(BNX2X_ACCEPT_ALL_UNICAST, &accept);

			if (msg->rx_mask & VFPF_RX_MASK_ACCEPT_ALL_MULTICAST)
				__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, &accept);

			if (msg->rx_mask & VFPF_RX_MASK_ACCEPT_BROADCAST)
				__set_bit(BNX2X_ACCEPT_BROADCAST, &accept);

			/* A packet arriving the vf's mac should be accepted
			 * with any vlan
			 */
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, &accept);

			/* set rx-mode */
			rc = bnx2x_vfop_rxmode_cmd(bp, vf, &cmd,
						   msg->vf_qid, accept);
			if (rc) {
				vfop->rc = rc;
				goto op_err;
			}
			return;
		}
		/* fall through */

	case BNX2X_VFOP_MBX_Q_FILTERS_MCAST:
		/* next state */
		vfop->state = BNX2X_VFOP_MBX_Q_FILTERS_DONE;

		if (msg->flags & VFPF_SET_Q_FILTERS_MULTICAST_CHANGED) {
			/* set mcasts */
			rc = bnx2x_vfop_mcast_cmd(bp, vf, &cmd, msg->multicast,
						  msg->n_multicast, false);
			if (rc) {
				vfop->rc = rc;
				goto op_err;
			}
			return;
		}
		/* fall through */
op_done:
	case BNX2X_VFOP_MBX_Q_FILTERS_DONE:
		bnx2x_vfop_end(bp, vf, vfop);
		return;
op_err:
	BNX2X_ERR("QFILTERS[%d:%d] error: rc %d\n",
		  vf->abs_vfid, msg->vf_qid, vfop->rc);
	goto op_done;

	default:
		bnx2x_vfop_default(state);
	}
}