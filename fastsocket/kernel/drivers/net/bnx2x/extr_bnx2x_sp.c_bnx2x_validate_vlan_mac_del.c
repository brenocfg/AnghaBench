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
struct bnx2x_vlan_mac_obj {scalar_t__ (* put_credit ) (struct bnx2x_vlan_mac_obj*) ;struct bnx2x_vlan_mac_registry_elem* (* check_del ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ;struct bnx2x_exe_queue_obj exe_queue; } ;
union bnx2x_qable_obj {struct bnx2x_vlan_mac_obj vlan_mac; } ;
struct bnx2x_vlan_mac_registry_elem {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_mac_flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/  u; } ;
struct TYPE_4__ {TYPE_1__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_2__ cmd_data; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  query_elem ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DONT_CONSUME_CAM_CREDIT ; 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BNX2X_VLAN_MAC_MOVE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct bnx2x_exeq_elem*,struct bnx2x_exeq_elem*,int) ; 
 struct bnx2x_vlan_mac_registry_elem* stub1 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct bnx2x_exe_queue_obj*,struct bnx2x_exeq_elem*) ; 
 scalar_t__ stub3 (struct bnx2x_exe_queue_obj*,struct bnx2x_exeq_elem*) ; 
 scalar_t__ stub4 (struct bnx2x_vlan_mac_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bnx2x_validate_vlan_mac_del(struct bnx2x *bp,
					      union bnx2x_qable_obj *qo,
					      struct bnx2x_exeq_elem *elem)
{
	struct bnx2x_vlan_mac_obj *o = &qo->vlan_mac;
	struct bnx2x_vlan_mac_registry_elem *pos;
	struct bnx2x_exe_queue_obj *exeq = &o->exe_queue;
	struct bnx2x_exeq_elem query_elem;

	/* If this classification can not be deleted (doesn't exist)
	 * - return a BNX2X_EXIST.
	 */
	pos = o->check_del(bp, o, &elem->cmd_data.vlan_mac.u);
	if (!pos) {
		DP(BNX2X_MSG_SP, "DEL command is not allowed considering current registry state\n");
		return -EEXIST;
	}

	/* Check if there are pending DEL or MOVE commands for this
	 * MAC/VLAN/VLAN-MAC. Return an error if so.
	 */
	memcpy(&query_elem, elem, sizeof(query_elem));

	/* Check for MOVE commands */
	query_elem.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_MOVE;
	if (exeq->get(exeq, &query_elem)) {
		BNX2X_ERR("There is a pending MOVE command already\n");
		return -EINVAL;
	}

	/* Check for DEL commands */
	if (exeq->get(exeq, elem)) {
		DP(BNX2X_MSG_SP, "There is a pending DEL command already\n");
		return -EEXIST;
	}

	/* Return the credit to the credit pool if not requested not to */
	if (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    o->put_credit(o))) {
		BNX2X_ERR("Failed to return a credit\n");
		return -EINVAL;
	}

	return 0;
}