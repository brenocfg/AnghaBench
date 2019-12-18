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
struct iwl_mvm_vif {int ap_sta_id; int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm_sta {int sta_id; int /*<<< orphan*/  tid_data; int /*<<< orphan*/  tfd_queue_msk; scalar_t__ tid_disable_agg; int /*<<< orphan*/  max_agg_bufsize; struct ieee80211_vif* vif; int /*<<< orphan*/  mac_id_n_color; int /*<<< orphan*/  lock; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/ * pending_frames; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {scalar_t__* hw_queue; scalar_t__ type; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_INVAL_HW_QUEUE ; 
 int IEEE80211_NUM_ACS ; 
 int IWL_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  LINK_QUAL_AGG_FRAME_LIMIT_DEF ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_find_free_sta_id (struct iwl_mvm*) ; 
 int iwl_mvm_sta_send_to_fw (struct iwl_mvm*,struct ieee80211_sta*,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_mvm_add_sta(struct iwl_mvm *mvm,
		    struct ieee80211_vif *vif,
		    struct ieee80211_sta *sta)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_sta *mvm_sta = (void *)sta->drv_priv;
	int i, ret, sta_id;

	lockdep_assert_held(&mvm->mutex);

	if (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
		sta_id = iwl_mvm_find_free_sta_id(mvm);
	else
		sta_id = mvm_sta->sta_id;

	if (WARN_ON_ONCE(sta_id == IWL_MVM_STATION_COUNT))
		return -ENOSPC;

	spin_lock_init(&mvm_sta->lock);

	mvm_sta->sta_id = sta_id;
	mvm_sta->mac_id_n_color = FW_CMD_ID_AND_COLOR(mvmvif->id,
						      mvmvif->color);
	mvm_sta->vif = vif;
	mvm_sta->max_agg_bufsize = LINK_QUAL_AGG_FRAME_LIMIT_DEF;

	/* HW restart, don't assume the memory has been zeroed */
	atomic_set(&mvm->pending_frames[sta_id], 0);
	mvm_sta->tid_disable_agg = 0;
	mvm_sta->tfd_queue_msk = 0;
	for (i = 0; i < IEEE80211_NUM_ACS; i++)
		if (vif->hw_queue[i] != IEEE80211_INVAL_HW_QUEUE)
			mvm_sta->tfd_queue_msk |= BIT(vif->hw_queue[i]);

	/* for HW restart - need to reset the seq_number etc... */
	memset(mvm_sta->tid_data, 0, sizeof(mvm_sta->tid_data));

	ret = iwl_mvm_sta_send_to_fw(mvm, sta, false);
	if (ret)
		return ret;

	/* The first station added is the AP, the others are TDLS STAs */
	if (vif->type == NL80211_IFTYPE_STATION &&
	    mvmvif->ap_sta_id == IWL_MVM_STATION_COUNT)
		mvmvif->ap_sta_id = sta_id;

	rcu_assign_pointer(mvm->fw_id_to_mac_id[sta_id], sta);

	return 0;
}