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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct iwl_mac_ctx_cmd {int /*<<< orphan*/  ap; int /*<<< orphan*/  filter_flags; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CTXT_ACTION_ADD ; 
 int /*<<< orphan*/  MAC_FILTER_IN_PROBE_REQUEST ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_cmd_common (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_mac_ctx_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_cmd_fill_ap (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ *,int) ; 
 int iwl_mvm_mac_ctxt_send_cmd (struct iwl_mvm*,struct iwl_mac_ctx_cmd*) ; 

__attribute__((used)) static int iwl_mvm_mac_ctxt_cmd_ap(struct iwl_mvm *mvm,
				   struct ieee80211_vif *vif,
				   u32 action)
{
	struct iwl_mac_ctx_cmd cmd = {};

	WARN_ON(vif->type != NL80211_IFTYPE_AP || vif->p2p);

	/* Fill the common data for all mac context types */
	iwl_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, action);

	/* Also enable probe requests to pass */
	cmd.filter_flags |= cpu_to_le32(MAC_FILTER_IN_PROBE_REQUEST);

	/* Fill the data specific for ap mode */
	iwl_mvm_mac_ctxt_cmd_fill_ap(mvm, vif, &cmd.ap,
				     action == FW_CTXT_ACTION_ADD);

	return iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}