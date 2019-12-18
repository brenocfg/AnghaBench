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
struct iwl_mvm_vif {size_t ap_sta_id; } ;
struct iwl_mvm_sta {size_t sta_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  tfd_queue_msk; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/ * pending_frames; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {scalar_t__ assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t IWL_MVM_STATION_COUNT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int iwl_mvm_drain_sta (struct iwl_mvm*,struct iwl_mvm_sta*,int) ; 
 int iwl_mvm_flush_tx_path (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 
 int iwl_mvm_rm_sta_common (struct iwl_mvm*,size_t) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iwl_mvm_rm_sta(struct iwl_mvm *mvm,
		   struct ieee80211_vif *vif,
		   struct ieee80211_sta *sta)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_sta *mvm_sta = (void *)sta->drv_priv;
	int ret;

	lockdep_assert_held(&mvm->mutex);

	if (vif->type == NL80211_IFTYPE_STATION &&
	    mvmvif->ap_sta_id == mvm_sta->sta_id) {
		/* flush its queues here since we are freeing mvm_sta */
		ret = iwl_mvm_flush_tx_path(mvm, mvm_sta->tfd_queue_msk, true);

		/*
		 * Put a non-NULL since the fw station isn't removed.
		 * It will be removed after the MAC will be set as
		 * unassoc.
		 */
		rcu_assign_pointer(mvm->fw_id_to_mac_id[mvm_sta->sta_id],
				   ERR_PTR(-EINVAL));

		/* if we are associated - we can't remove the AP STA now */
		if (vif->bss_conf.assoc)
			return ret;

		/* unassoc - go ahead - remove the AP STA now */
		mvmvif->ap_sta_id = IWL_MVM_STATION_COUNT;
	}

	/*
	 * Make sure that the tx response code sees the station as -EBUSY and
	 * calls the drain worker.
	 */
	spin_lock_bh(&mvm_sta->lock);
	/*
	 * There are frames pending on the AC queues for this station.
	 * We need to wait until all the frames are drained...
	 */
	if (atomic_read(&mvm->pending_frames[mvm_sta->sta_id])) {
		rcu_assign_pointer(mvm->fw_id_to_mac_id[mvm_sta->sta_id],
				   ERR_PTR(-EBUSY));
		spin_unlock_bh(&mvm_sta->lock);
		ret = iwl_mvm_drain_sta(mvm, mvm_sta, true);
	} else {
		spin_unlock_bh(&mvm_sta->lock);
		ret = iwl_mvm_rm_sta_common(mvm, mvm_sta->sta_id);
		rcu_assign_pointer(mvm->fw_id_to_mac_id[mvm_sta->sta_id], NULL);
	}

	return ret;
}