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
struct TYPE_9__ {int /*<<< orphan*/  vlan_mac_flags; } ;
struct bnx2x_vlan_mac_ramrod_params {int /*<<< orphan*/  ramrod_flags; TYPE_4__ user_req; struct bnx2x_vlan_mac_obj* vlan_mac_obj; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* check_pending ) (TYPE_5__*) ;} ;
struct bnx2x_vlan_mac_obj {scalar_t__ (* delete_all ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_5__ raw; } ;
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vfop_filters {int dummy; } ;
struct TYPE_7__ {struct bnx2x_vfop_filters* multi_filter; } ;
struct TYPE_8__ {TYPE_2__ filters; } ;
struct bnx2x_vfop {int state; scalar_t__ rc; TYPE_3__ args; TYPE_1__* op_p; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vfop_vlan_mac_state { ____Placeholder_bnx2x_vfop_vlan_mac_state } bnx2x_vfop_vlan_mac_state ;
struct TYPE_6__ {struct bnx2x_vlan_mac_ramrod_params vlan_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
#define  BNX2X_VFOP_MAC_CONFIG_LIST 132 
#define  BNX2X_VFOP_VLAN_CONFIG_LIST 131 
#define  BNX2X_VFOP_VLAN_MAC_CHK_DONE 130 
#define  BNX2X_VFOP_VLAN_MAC_CLEAR 129 
#define  BNX2X_VFOP_VLAN_MAC_CONFIG_SINGLE 128 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  VFOP_DONE ; 
 void* bnx2x_config_vlan_mac (struct bnx2x*,struct bnx2x_vlan_mac_ramrod_params*) ; 
 void* bnx2x_vfop_config_list (struct bnx2x*,struct bnx2x_vfop_filters*,struct bnx2x_vlan_mac_ramrod_params*) ; 
 int /*<<< orphan*/  bnx2x_vfop_credit (struct bnx2x*,struct bnx2x_vfop*,struct bnx2x_vlan_mac_obj*) ; 
 struct bnx2x_vfop* bnx2x_vfop_cur (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_default (int) ; 
 int /*<<< orphan*/  bnx2x_vfop_end (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop*) ; 
 int /*<<< orphan*/  bnx2x_vfop_finalize (struct bnx2x_virtf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfop_reset_wq (struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  kfree (struct bnx2x_vfop_filters*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*) ; 

__attribute__((used)) static void bnx2x_vfop_vlan_mac(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	struct bnx2x_vfop *vfop = bnx2x_vfop_cur(bp, vf);
	struct bnx2x_vlan_mac_ramrod_params *vlan_mac = &vfop->op_p->vlan_mac;
	struct bnx2x_vlan_mac_obj *obj = vlan_mac->vlan_mac_obj;
	struct bnx2x_vfop_filters *filters = vfop->args.filters.multi_filter;

	enum bnx2x_vfop_vlan_mac_state state = vfop->state;

	if (vfop->rc < 0)
		goto op_err;

	DP(BNX2X_MSG_IOV, "vf[%d] STATE: %d\n", vf->abs_vfid, state);

	bnx2x_vfop_reset_wq(vf);

	switch (state) {
	case BNX2X_VFOP_VLAN_MAC_CLEAR:
		/* next state */
		vfop->state = BNX2X_VFOP_VLAN_MAC_CHK_DONE;

		/* do delete */
		vfop->rc = obj->delete_all(bp, obj,
					   &vlan_mac->user_req.vlan_mac_flags,
					   &vlan_mac->ramrod_flags);

		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);

	case BNX2X_VFOP_VLAN_MAC_CONFIG_SINGLE:
		/* next state */
		vfop->state = BNX2X_VFOP_VLAN_MAC_CHK_DONE;

		/* do config */
		vfop->rc = bnx2x_config_vlan_mac(bp, vlan_mac);
		if (vfop->rc == -EEXIST)
			vfop->rc = 0;

		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);

	case BNX2X_VFOP_VLAN_MAC_CHK_DONE:
		vfop->rc = !!obj->raw.check_pending(&obj->raw);
		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);

	case BNX2X_VFOP_MAC_CONFIG_LIST:
		/* next state */
		vfop->state = BNX2X_VFOP_VLAN_MAC_CHK_DONE;

		/* do list config */
		vfop->rc = bnx2x_vfop_config_list(bp, filters, vlan_mac);
		if (vfop->rc)
			goto op_err;

		set_bit(RAMROD_CONT, &vlan_mac->ramrod_flags);
		vfop->rc = bnx2x_config_vlan_mac(bp, vlan_mac);
		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);

	case BNX2X_VFOP_VLAN_CONFIG_LIST:
		/* next state */
		vfop->state = BNX2X_VFOP_VLAN_MAC_CHK_DONE;

		/* do list config */
		vfop->rc = bnx2x_vfop_config_list(bp, filters, vlan_mac);
		if (!vfop->rc) {
			set_bit(RAMROD_CONT, &vlan_mac->ramrod_flags);
			vfop->rc = bnx2x_config_vlan_mac(bp, vlan_mac);
		}
		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);

	default:
		bnx2x_vfop_default(state);
	}
op_err:
	BNX2X_ERR("VLAN-MAC error: rc %d\n", vfop->rc);
op_done:
	kfree(filters);
	bnx2x_vfop_credit(bp, vfop, obj);
	bnx2x_vfop_end(bp, vf, vfop);
op_pending:
	return;
}