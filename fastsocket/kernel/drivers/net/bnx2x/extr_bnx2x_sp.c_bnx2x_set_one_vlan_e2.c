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
struct TYPE_10__ {void* vlan; int /*<<< orphan*/  header; } ;
union eth_classify_rule_cmd {TYPE_5__ vlan; } ;
typedef  int /*<<< orphan*/  u16 ;
struct eth_classify_rules_ramrod_data {int /*<<< orphan*/  header; union eth_classify_rule_cmd* rules; } ;
struct bnx2x_raw_obj {int /*<<< orphan*/  state; int /*<<< orphan*/  cid; scalar_t__ rdata; } ;
struct bnx2x_vlan_mac_obj {struct bnx2x_raw_obj raw; } ;
struct TYPE_6__ {int /*<<< orphan*/  vlan; } ;
struct TYPE_7__ {TYPE_1__ vlan; } ;
struct TYPE_8__ {int cmd; struct bnx2x_vlan_mac_obj* target_obj; TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_4__ cmd_data; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vlan_mac_cmd { ____Placeholder_bnx2x_vlan_mac_cmd } bnx2x_vlan_mac_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BNX2X_VLAN_MAC_ADD ; 
 int BNX2X_VLAN_MAC_MOVE ; 
 int /*<<< orphan*/  CLASSIFY_RULE_OPCODE_VLAN ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vlan_mac_set_cmd_hdr_e2 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_vlan_mac_set_rdata_hdr_e2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct eth_classify_rules_ramrod_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_set_one_vlan_e2(struct bnx2x *bp,
				  struct bnx2x_vlan_mac_obj *o,
				  struct bnx2x_exeq_elem *elem, int rule_idx,
				  int cam_offset)
{
	struct bnx2x_raw_obj *raw = &o->raw;
	struct eth_classify_rules_ramrod_data *data =
		(struct eth_classify_rules_ramrod_data *)(raw->rdata);
	int rule_cnt = rule_idx + 1;
	union eth_classify_rule_cmd *rule_entry = &data->rules[rule_idx];
	enum bnx2x_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	bool add = (cmd == BNX2X_VLAN_MAC_ADD) ? true : false;
	u16 vlan = elem->cmd_data.vlan_mac.u.vlan.vlan;

	/* Reset the ramrod data buffer for the first rule */
	if (rule_idx == 0)
		memset(data, 0, sizeof(*data));

	/* Set a rule header */
	bnx2x_vlan_mac_set_cmd_hdr_e2(bp, o, add, CLASSIFY_RULE_OPCODE_VLAN,
				      &rule_entry->vlan.header);

	DP(BNX2X_MSG_SP, "About to %s VLAN %d\n", (add ? "add" : "delete"),
			 vlan);

	/* Set a VLAN itself */
	rule_entry->vlan.vlan = cpu_to_le16(vlan);

	/* MOVE: Add a rule that will add this MAC to the target Queue */
	if (cmd == BNX2X_VLAN_MAC_MOVE) {
		rule_entry++;
		rule_cnt++;

		/* Setup ramrod data */
		bnx2x_vlan_mac_set_cmd_hdr_e2(bp,
					elem->cmd_data.vlan_mac.target_obj,
					      true, CLASSIFY_RULE_OPCODE_VLAN,
					      &rule_entry->vlan.header);

		/* Set a VLAN itself */
		rule_entry->vlan.vlan = cpu_to_le16(vlan);
	}

	/* Set the ramrod data header */
	/* TODO: take this to the higher level in order to prevent multiple
		 writing */
	bnx2x_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state, &data->header,
					rule_cnt);
}