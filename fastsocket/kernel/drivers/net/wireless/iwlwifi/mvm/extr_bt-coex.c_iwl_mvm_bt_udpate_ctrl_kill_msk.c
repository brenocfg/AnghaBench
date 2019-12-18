#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iwl_bt_coex_profile_notif {int dummy; } ;
struct iwl_mvm {int bt_kill_msk; int /*<<< orphan*/  mutex; struct iwl_bt_coex_profile_notif last_bt_notif; } ;
struct iwl_bt_coex_cmd {int /*<<< orphan*/  valid_bit_msk; void* kill_cts_msk; void* kill_ack_msk; } ;
typedef  enum iwl_bt_kill_msk { ____Placeholder_iwl_bt_kill_msk } iwl_bt_kill_msk ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  A2DP_STATE ; 
 int /*<<< orphan*/  BT_CONFIG ; 
 int BT_KILL_MSK_DEFAULT ; 
 int BT_KILL_MSK_REDUCED_TXPOW ; 
 int BT_KILL_MSK_SCO_HID_A2DP ; 
 scalar_t__ BT_MBOX_MSG (struct iwl_bt_coex_profile_notif*,int,int /*<<< orphan*/ ) ; 
 int BT_VALID_KILL_ACK ; 
 int BT_VALID_KILL_CTS ; 
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_DEBUG_COEX (struct iwl_mvm*,char*,int,...) ; 
 int /*<<< orphan*/  SCO_STATE ; 
 int /*<<< orphan*/  SNIFF_STATE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iwl_bt_ack_kill_msk ; 
 int /*<<< orphan*/ * iwl_bt_cts_kill_msk ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_bt_coex_cmd*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_bt_udpate_ctrl_kill_msk(struct iwl_mvm *mvm,
					   bool reduced_tx_power)
{
	enum iwl_bt_kill_msk bt_kill_msk;
	struct iwl_bt_coex_cmd cmd = {};
	struct iwl_bt_coex_profile_notif *notif = &mvm->last_bt_notif;

	lockdep_assert_held(&mvm->mutex);

	if (reduced_tx_power) {
		/* Reduced Tx power has precedence on the type of the profile */
		bt_kill_msk = BT_KILL_MSK_REDUCED_TXPOW;
	} else {
		/* Low latency BT profile is active: give higher prio to BT */
		if (BT_MBOX_MSG(notif, 3, SCO_STATE)  ||
		    BT_MBOX_MSG(notif, 3, A2DP_STATE) ||
		    BT_MBOX_MSG(notif, 3, SNIFF_STATE))
			bt_kill_msk = BT_KILL_MSK_SCO_HID_A2DP;
		else
			bt_kill_msk = BT_KILL_MSK_DEFAULT;
	}

	IWL_DEBUG_COEX(mvm,
		       "Update kill_msk: %d - SCO %sactive A2DP %sactive SNIFF %sactive\n",
		       bt_kill_msk,
		       BT_MBOX_MSG(notif, 3, SCO_STATE) ? "" : "in",
		       BT_MBOX_MSG(notif, 3, A2DP_STATE) ? "" : "in",
		       BT_MBOX_MSG(notif, 3, SNIFF_STATE) ? "" : "in");

	/* Don't send HCMD if there is no update */
	if (bt_kill_msk == mvm->bt_kill_msk)
		return 0;

	mvm->bt_kill_msk = bt_kill_msk;
	cmd.kill_ack_msk = cpu_to_le32(iwl_bt_ack_kill_msk[bt_kill_msk]);
	cmd.kill_cts_msk = cpu_to_le32(iwl_bt_cts_kill_msk[bt_kill_msk]);
	cmd.valid_bit_msk = cpu_to_le16(BT_VALID_KILL_ACK | BT_VALID_KILL_CTS);

	IWL_DEBUG_COEX(mvm, "bt_kill_msk = %d\n", bt_kill_msk);
	return iwl_mvm_send_cmd_pdu(mvm, BT_CONFIG, CMD_SYNC,
				    sizeof(cmd), &cmd);
}