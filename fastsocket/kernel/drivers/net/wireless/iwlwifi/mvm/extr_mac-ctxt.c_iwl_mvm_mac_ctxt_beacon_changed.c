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
struct sk_buff {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct ieee80211_vif {scalar_t__ type; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_send_beacon (struct iwl_mvm*,struct ieee80211_vif*,struct sk_buff*) ; 

int iwl_mvm_mac_ctxt_beacon_changed(struct iwl_mvm *mvm,
				    struct ieee80211_vif *vif)
{
	struct sk_buff *beacon;
	int ret;

	WARN_ON(vif->type != NL80211_IFTYPE_AP);

	beacon = ieee80211_beacon_get(mvm->hw, vif);
	if (!beacon)
		return -ENOMEM;

	ret = iwl_mvm_mac_ctxt_send_beacon(mvm, vif, beacon);
	dev_kfree_skb(beacon);
	return ret;
}