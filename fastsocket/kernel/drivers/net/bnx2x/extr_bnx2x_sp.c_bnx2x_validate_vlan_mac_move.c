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
struct bnx2x_vlan_mac_obj {scalar_t__ (* put_credit ) (struct bnx2x_vlan_mac_obj*) ;scalar_t__ (* get_credit ) (struct bnx2x_vlan_mac_obj*) ;int /*<<< orphan*/  (* check_move ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ;struct bnx2x_exe_queue_obj exe_queue; } ;
union bnx2x_qable_obj {struct bnx2x_vlan_mac_obj vlan_mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_mac_flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/  u; struct bnx2x_vlan_mac_obj* target_obj; } ;
struct TYPE_4__ {TYPE_1__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_2__ cmd_data; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  query_elem ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DONT_CONSUME_CAM_CREDIT ; 
 int /*<<< orphan*/  BNX2X_DONT_CONSUME_CAM_CREDIT_DEST ; 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BNX2X_VLAN_MAC_ADD ; 
 int /*<<< orphan*/  BNX2X_VLAN_MAC_DEL ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct bnx2x_exeq_elem*,struct bnx2x_exeq_elem*,int) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct bnx2x_exe_queue_obj*,struct bnx2x_exeq_elem*) ; 
 scalar_t__ stub3 (struct bnx2x_exe_queue_obj*,struct bnx2x_exeq_elem*) ; 
 scalar_t__ stub4 (struct bnx2x_exe_queue_obj*,struct bnx2x_exeq_elem*) ; 
 scalar_t__ stub5 (struct bnx2x_vlan_mac_obj*) ; 
 scalar_t__ stub6 (struct bnx2x_vlan_mac_obj*) ; 
 scalar_t__ stub7 (struct bnx2x_vlan_mac_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bnx2x_validate_vlan_mac_move(struct bnx2x *bp,
					       union bnx2x_qable_obj *qo,
					       struct bnx2x_exeq_elem *elem)
{
	struct bnx2x_vlan_mac_obj *src_o = &qo->vlan_mac;
	struct bnx2x_vlan_mac_obj *dest_o = elem->cmd_data.vlan_mac.target_obj;
	struct bnx2x_exeq_elem query_elem;
	struct bnx2x_exe_queue_obj *src_exeq = &src_o->exe_queue;
	struct bnx2x_exe_queue_obj *dest_exeq = &dest_o->exe_queue;

	/* Check if we can perform this operation based on the current registry
	 * state.
	 */
	if (!src_o->check_move(bp, src_o, dest_o,
			       &elem->cmd_data.vlan_mac.u)) {
		DP(BNX2X_MSG_SP, "MOVE command is not allowed considering current registry state\n");
		return -EINVAL;
	}

	/* Check if there is an already pending DEL or MOVE command for the
	 * source object or ADD command for a destination object. Return an
	 * error if so.
	 */
	memcpy(&query_elem, elem, sizeof(query_elem));

	/* Check DEL on source */
	query_elem.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_DEL;
	if (src_exeq->get(src_exeq, &query_elem)) {
		BNX2X_ERR("There is a pending DEL command on the source queue already\n");
		return -EINVAL;
	}

	/* Check MOVE on source */
	if (src_exeq->get(src_exeq, elem)) {
		DP(BNX2X_MSG_SP, "There is a pending MOVE command already\n");
		return -EEXIST;
	}

	/* Check ADD on destination */
	query_elem.cmd_data.vlan_mac.cmd = BNX2X_VLAN_MAC_ADD;
	if (dest_exeq->get(dest_exeq, &query_elem)) {
		BNX2X_ERR("There is a pending ADD command on the destination queue already\n");
		return -EINVAL;
	}

	/* Consume the credit if not requested not to */
	if (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT_DEST,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    dest_o->get_credit(dest_o)))
		return -EINVAL;

	if (!(test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		       &elem->cmd_data.vlan_mac.vlan_mac_flags) ||
	    src_o->put_credit(src_o))) {
		/* return the credit taken from dest... */
		dest_o->put_credit(dest_o);
		return -EINVAL;
	}

	return 0;
}