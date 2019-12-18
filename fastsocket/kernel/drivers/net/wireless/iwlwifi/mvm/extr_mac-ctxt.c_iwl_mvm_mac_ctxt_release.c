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
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int type; int /*<<< orphan*/ * hw_queue; int /*<<< orphan*/  cab_queue; } ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  IWL_MVM_OFFCHANNEL_QUEUE ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_P2P_DEVICE 128 
 int /*<<< orphan*/  iwl_trans_txq_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwl_mvm_mac_ctxt_release(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	int ac;

	lockdep_assert_held(&mvm->mutex);

	switch (vif->type) {
	case NL80211_IFTYPE_P2P_DEVICE:
		iwl_trans_txq_disable(mvm->trans, IWL_MVM_OFFCHANNEL_QUEUE);
		break;
	case NL80211_IFTYPE_AP:
		iwl_trans_txq_disable(mvm->trans, vif->cab_queue);
		/* fall through */
	default:
		for (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			iwl_trans_txq_disable(mvm->trans, vif->hw_queue[ac]);
	}
}