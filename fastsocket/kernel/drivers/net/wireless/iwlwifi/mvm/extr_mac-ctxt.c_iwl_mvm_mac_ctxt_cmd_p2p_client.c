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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctwin; int /*<<< orphan*/  sta; } ;
struct iwl_mac_ctx_cmd {TYPE_1__ p2p_sta; } ;
struct ieee80211_p2p_noa_attr {int oppps_ctwindow; } ;
struct TYPE_4__ {struct ieee80211_p2p_noa_attr p2p_noa_attr; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  p2p; TYPE_2__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CTXT_ACTION_ADD ; 
 int IEEE80211_P2P_OPPPS_CTWINDOW_MASK ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_cmd_common (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_mac_ctx_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_cmd_fill_sta (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ *,int) ; 
 int iwl_mvm_mac_ctxt_send_cmd (struct iwl_mvm*,struct iwl_mac_ctx_cmd*) ; 

__attribute__((used)) static int iwl_mvm_mac_ctxt_cmd_p2p_client(struct iwl_mvm *mvm,
					   struct ieee80211_vif *vif,
					   u32 action)
{
	struct iwl_mac_ctx_cmd cmd = {};
	struct ieee80211_p2p_noa_attr *noa = &vif->bss_conf.p2p_noa_attr;

	WARN_ON(vif->type != NL80211_IFTYPE_STATION || !vif->p2p);

	/* Fill the common data for all mac context types */
	iwl_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, action);

	/* Fill the data specific for station mode */
	iwl_mvm_mac_ctxt_cmd_fill_sta(mvm, vif, &cmd.p2p_sta.sta,
				      action == FW_CTXT_ACTION_ADD);

	cmd.p2p_sta.ctwin = cpu_to_le32(noa->oppps_ctwindow &
					IEEE80211_P2P_OPPPS_CTWINDOW_MASK);

	return iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}