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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm_sta {int /*<<< orphan*/  mac_id_n_color; int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm_add_sta_cmd {int /*<<< orphan*/  sleep_state_flags; int /*<<< orphan*/  mac_id_n_color; int /*<<< orphan*/  sleep_tx_count; int /*<<< orphan*/  modify_mask; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  add_modify; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
typedef  enum ieee80211_frame_release_type { ____Placeholder_ieee80211_frame_release_type } ieee80211_frame_release_type ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STA ; 
 int /*<<< orphan*/  CMD_ASYNC ; 
 int IEEE80211_FRAME_RELEASE_UAPSD ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  STA_MODE_MODIFY ; 
 int /*<<< orphan*/  STA_MODIFY_SLEEPING_STA_TX_COUNT ; 
 int /*<<< orphan*/  STA_SLEEP_STATE_PS_POLL ; 
 int /*<<< orphan*/  STA_SLEEP_STATE_UAPSD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mvm_add_sta_cmd*) ; 

void iwl_mvm_sta_modify_sleep_tx_count(struct iwl_mvm *mvm,
				       struct ieee80211_sta *sta,
				       enum ieee80211_frame_release_type reason,
				       u16 cnt)
{
	u16 sleep_state_flags =
		(reason == IEEE80211_FRAME_RELEASE_UAPSD) ?
			STA_SLEEP_STATE_UAPSD : STA_SLEEP_STATE_PS_POLL;
	struct iwl_mvm_sta *mvmsta = (void *)sta->drv_priv;
	struct iwl_mvm_add_sta_cmd cmd = {
		.add_modify = STA_MODE_MODIFY,
		.sta_id = mvmsta->sta_id,
		.modify_mask = STA_MODIFY_SLEEPING_STA_TX_COUNT,
		.sleep_tx_count = cpu_to_le16(cnt),
		.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color),
		/*
		 * Same modify mask for sleep_tx_count and sleep_state_flags so
		 * we must set the sleep_state_flags too.
		 */
		.sleep_state_flags = cpu_to_le16(sleep_state_flags),
	};
	int ret;

	/* TODO: somehow the fw doesn't seem to take PS_POLL into account */
	ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA, CMD_ASYNC, sizeof(cmd), &cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to send ADD_STA command (%d)\n", ret);
}