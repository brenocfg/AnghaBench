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
typedef  int u32 ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_bss_conf {int dummy; } ;

/* Variables and functions */
 int BSS_CHANGED_BEACON ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 scalar_t__ iwl_mvm_mac_ctxt_beacon_changed (struct iwl_mvm*,struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_bss_info_changed_ap(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif,
					struct ieee80211_bss_conf *bss_conf,
					u32 changes)
{
	/* Need to send a new beacon template to the FW */
	if (changes & BSS_CHANGED_BEACON) {
		if (iwl_mvm_mac_ctxt_beacon_changed(mvm, vif))
			IWL_WARN(mvm, "Failed updating beacon data\n");
	}
}