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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct iwl_mvm_vif {scalar_t__ id; scalar_t__ tsf_id; } ;
struct iwl_mvm_mac_iface_iterator_data {int found_vif; scalar_t__ preferred_tsf; int /*<<< orphan*/  available_tsf_ids; struct ieee80211_vif* vif; int /*<<< orphan*/  available_mac_ids; int /*<<< orphan*/  used_hw_queues; } ;
struct ieee80211_vif {scalar_t__* hw_queue; scalar_t__ cab_queue; int type; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_INVAL_HW_QUEUE ; 
 size_t IEEE80211_NUM_ACS ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ NUM_TSF_IDS ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_mac_iface_iterator(void *_data, u8 *mac,
				       struct ieee80211_vif *vif)
{
	struct iwl_mvm_mac_iface_iterator_data *data = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u32 ac;

	/* Iterator may already find the interface being added -- skip it */
	if (vif == data->vif) {
		data->found_vif = true;
		return;
	}

	/* Mark the queues used by the vif */
	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		if (vif->hw_queue[ac] != IEEE80211_INVAL_HW_QUEUE)
			__set_bit(vif->hw_queue[ac], data->used_hw_queues);

	if (vif->cab_queue != IEEE80211_INVAL_HW_QUEUE)
		__set_bit(vif->cab_queue, data->used_hw_queues);

	/*
	 * Mark MAC IDs as used by clearing the available bit, and
	 * (below) mark TSFs as used if their existing use is not
	 * compatible with the new interface type.
	 * No locking or atomic bit operations are needed since the
	 * data is on the stack of the caller function.
	 */
	__clear_bit(mvmvif->id, data->available_mac_ids);

	/*
	 * The TSF is a hardware/firmware resource, there are 4 and
	 * the driver should assign and free them as needed. However,
	 * there are cases where 2 MACs should share the same TSF ID
	 * for the purpose of clock sync, an optimization to avoid
	 * clock drift causing overlapping TBTTs/DTIMs for a GO and
	 * client in the system.
	 *
	 * The firmware will decide according to the MAC type which
	 * will be the master and slave. Clients that need to sync
	 * with a remote station will be the master, and an AP or GO
	 * will be the slave.
	 *
	 * Depending on the new interface type it can be slaved to
	 * or become the master of an existing interface.
	 */
	switch (data->vif->type) {
	case NL80211_IFTYPE_STATION:
		/*
		 * The new interface is client, so if the existing one
		 * we're iterating is an AP, the TSF should be used to
		 * avoid drift between the new client and existing AP,
		 * the existing AP will get drift updates from the new
		 * client context in this case
		 */
		if (vif->type == NL80211_IFTYPE_AP) {
			if (data->preferred_tsf == NUM_TSF_IDS &&
			    test_bit(mvmvif->tsf_id, data->available_tsf_ids))
				data->preferred_tsf = mvmvif->tsf_id;
			return;
		}
		break;
	case NL80211_IFTYPE_AP:
		/*
		 * The new interface is AP/GO, so should get drift
		 * updates from an existing client or use the same
		 * TSF as an existing GO. There's no drift between
		 * TSFs internally but if they used different TSFs
		 * then a new client MAC could update one of them
		 * and cause drift that way.
		 */
		if (vif->type == NL80211_IFTYPE_STATION ||
		    vif->type == NL80211_IFTYPE_AP) {
			if (data->preferred_tsf == NUM_TSF_IDS &&
			    test_bit(mvmvif->tsf_id, data->available_tsf_ids))
				data->preferred_tsf = mvmvif->tsf_id;
			return;
		}
		break;
	default:
		/*
		 * For all other interface types there's no need to
		 * take drift into account. Either they're exclusive
		 * like IBSS and monitor, or we don't care much about
		 * their TSF (like P2P Device), but we won't be able
		 * to share the TSF resource.
		 */
		break;
	}

	/*
	 * Unless we exited above, we can't share the TSF resource
	 * that the virtual interface we're iterating over is using
	 * with the new one, so clear the available bit and if this
	 * was the preferred one, reset that as well.
	 */
	__clear_bit(mvmvif->tsf_id, data->available_tsf_ids);

	if (data->preferred_tsf == mvmvif->tsf_id)
		data->preferred_tsf = NUM_TSF_IDS;
}