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
struct iwl_mvm_vif {int uploaded; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_ADD ; 
 scalar_t__ WARN_ONCE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_type_p2p (struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctx_send (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

int iwl_mvm_mac_ctxt_add(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	if (WARN_ONCE(mvmvif->uploaded, "Adding active MAC %pM/%d\n",
		      vif->addr, ieee80211_vif_type_p2p(vif)))
		return -EIO;

	ret = iwl_mvm_mac_ctx_send(mvm, vif, FW_CTXT_ACTION_ADD);
	if (ret)
		return ret;

	mvmvif->uploaded = true;
	return 0;
}