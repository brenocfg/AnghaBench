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
typedef  size_t u8 ;
struct iwl_mvm_tid_data {scalar_t__ ssn; scalar_t__ next_reclaimed; int state; size_t txq_id; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  lock; struct ieee80211_vif* vif; struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/ * queue_to_mac80211; int /*<<< orphan*/  trans; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;

/* Variables and functions */
 int IWL_AGG_OFF ; 
 int IWL_AGG_STARTING ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,scalar_t__) ; 
#define  IWL_EMPTYING_HW_QUEUE_ADDBA 129 
#define  IWL_EMPTYING_HW_QUEUE_DELBA 128 
 int /*<<< orphan*/  IWL_INVALID_MAC80211_QUEUE ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iwl_trans_txq_disable (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_check_ratid_empty(struct iwl_mvm *mvm,
				      struct ieee80211_sta *sta, u8 tid)
{
	struct iwl_mvm_sta *mvmsta = (void *)sta->drv_priv;
	struct iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];
	struct ieee80211_vif *vif = mvmsta->vif;

	lockdep_assert_held(&mvmsta->lock);

	if (tid_data->ssn != tid_data->next_reclaimed)
		return;

	switch (tid_data->state) {
	case IWL_EMPTYING_HW_QUEUE_ADDBA:
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Can continue addBA flow ssn = next_recl = %d\n",
				    tid_data->next_reclaimed);
		tid_data->state = IWL_AGG_STARTING;
		ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;

	case IWL_EMPTYING_HW_QUEUE_DELBA:
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Can continue DELBA flow ssn = next_recl = %d\n",
				    tid_data->next_reclaimed);
		iwl_trans_txq_disable(mvm->trans, tid_data->txq_id);
		tid_data->state = IWL_AGG_OFF;
		/*
		 * we can't hold the mutex - but since we are after a sequence
		 * point (call to iwl_trans_txq_disable), so we don't even need
		 * a memory barrier.
		 */
		mvm->queue_to_mac80211[tid_data->txq_id] =
					IWL_INVALID_MAC80211_QUEUE;
		ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;

	default:
		break;
	}
}