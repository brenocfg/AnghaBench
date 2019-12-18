#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_exe_queue_obj {scalar_t__ (* get ) (struct bnx2x_exe_queue_obj*,struct bnx2x_exeq_elem*) ;} ;
struct bnx2x_vlan_mac_obj {int (* check_add ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ;scalar_t__ (* get_credit ) (struct bnx2x_vlan_mac_obj*) ;struct bnx2x_exe_queue_obj exe_queue; } ;
union bnx2x_qable_obj {struct bnx2x_vlan_mac_obj vlan_mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_mac_flags; int /*<<< orphan*/  u; } ;
struct TYPE_4__ {TYPE_1__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_2__ cmd_data; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DONT_CONSUME_CAM_CREDIT ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EEXIST ; 
 int EINVAL ; 
 int stub1 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct bnx2x_exe_queue_obj*,struct bnx2x_exeq_elem*) ; 
 scalar_t__ stub3 (struct bnx2x_vlan_mac_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bnx2x_validate_vlan_mac_add(struct bnx2x *bp,
					      union bnx2x_qable_obj *qo,
					      struct bnx2x_exeq_elem *elem)
{
	struct bnx2x_vlan_mac_obj *o = &qo->vlan_mac;
	struct bnx2x_exe_queue_obj *exeq = &o->exe_queue;
	int rc;

	/* Check the registry */
	rc = o->check_add(bp, o, &elem->cmd_data.vlan_mac.u);
	if (rc) {
		DP(BNX2X_MSG_SP, "ADD command is not allowed considering current registry state.\n");
		return rc;
	}

	/* Check if there is a pending ADD command for this
	 * MAC/VLAN/VLAN-MAC. Return an error if there is.
	 */
	if (exeq->get(exeq, elem)) {
		DP(BNX2X_MSG_SP, "There is a pending ADD command already\n");
		return -EEXIST;
	}

	/* TODO: Check the pending MOVE from other objects where this
	 * object is a destination object.
	 */

	/* Consume the credit if not requested not to */
	if (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    o->get_credit(o)))
		return -EINVAL;

	return 0;
}