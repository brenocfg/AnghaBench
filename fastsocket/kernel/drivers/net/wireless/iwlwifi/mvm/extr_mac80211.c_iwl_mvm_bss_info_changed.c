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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int type; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_bss_conf {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_bss_info_changed_ap (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_bss_info_changed_station (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_bss_info_changed(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif,
				     struct ieee80211_bss_conf *bss_conf,
				     u32 changes)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		iwl_mvm_bss_info_changed_station(mvm, vif, bss_conf, changes);
		break;
	case NL80211_IFTYPE_AP:
		iwl_mvm_bss_info_changed_ap(mvm, vif, bss_conf, changes);
		break;
	default:
		/* shouldn't happen */
		WARN_ON_ONCE(1);
	}

	mutex_unlock(&mvm->mutex);
}