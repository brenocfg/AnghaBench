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
struct sk_buff {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  status; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ hw_queue; } ;

/* Variables and functions */
 TYPE_1__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IWL_DEBUG_DROP (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_MVM_OFFCHANNEL_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RFKILL ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_ROC_RUNNING ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 scalar_t__ iwl_mvm_tx_skb (struct iwl_mvm*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_tx_skb_non_sta (struct iwl_mvm*,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_tx(struct ieee80211_hw *hw,
			   struct ieee80211_tx_control *control,
			   struct sk_buff *skb)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	if (test_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status)) {
		IWL_DEBUG_DROP(mvm, "Dropping - RF KILL\n");
		goto drop;
	}

	if (IEEE80211_SKB_CB(skb)->hw_queue == IWL_MVM_OFFCHANNEL_QUEUE &&
	    !test_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status))
		goto drop;

	if (control->sta) {
		if (iwl_mvm_tx_skb(mvm, skb, control->sta))
			goto drop;
		return;
	}

	if (iwl_mvm_tx_skb_non_sta(mvm, skb))
		goto drop;
	return;
 drop:
	ieee80211_free_txskb(hw, skb);
}