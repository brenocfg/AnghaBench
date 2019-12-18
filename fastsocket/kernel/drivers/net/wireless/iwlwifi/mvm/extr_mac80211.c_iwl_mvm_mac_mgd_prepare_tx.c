#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  assoc; scalar_t__ beacon_int; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_TE_SESSION_PROTECTION_MAX_TIME_MS ; 
 int /*<<< orphan*/  IWL_MVM_TE_SESSION_PROTECTION_MIN_TIME_MS ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_protect_session (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_mgd_prepare_tx(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	u32 duration = min(IWL_MVM_TE_SESSION_PROTECTION_MAX_TIME_MS,
			   200 + vif->bss_conf.beacon_int);
	u32 min_duration = min(IWL_MVM_TE_SESSION_PROTECTION_MIN_TIME_MS,
			       100 + vif->bss_conf.beacon_int);

	if (WARN_ON_ONCE(vif->bss_conf.assoc))
		return;

	mutex_lock(&mvm->mutex);
	/* Try really hard to protect the session and hear a beacon */
	iwl_mvm_protect_session(mvm, vif, duration, min_duration);
	mutex_unlock(&mvm->mutex);
}