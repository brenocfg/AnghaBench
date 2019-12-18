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
typedef  int u8 ;
struct iwl_mvm_vif {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm_int_sta {scalar_t__ sta_id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IWL_MVM_STATION_COUNT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int iwl_mvm_add_int_sta_common (struct iwl_mvm*,struct iwl_mvm_int_sta*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_send_bcast_sta(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			   struct iwl_mvm_int_sta *bsta)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	static const u8 baddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON_ONCE(bsta->sta_id == IWL_MVM_STATION_COUNT))
		return -ENOSPC;

	return iwl_mvm_add_int_sta_common(mvm, bsta, baddr,
					  mvmvif->id, mvmvif->color);
}