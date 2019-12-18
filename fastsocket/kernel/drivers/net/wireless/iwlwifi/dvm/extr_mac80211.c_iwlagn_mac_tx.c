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
struct iwl_priv {int dummy; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 scalar_t__ iwlagn_tx_skb (struct iwl_priv*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void iwlagn_mac_tx(struct ieee80211_hw *hw,
			  struct ieee80211_tx_control *control,
			  struct sk_buff *skb)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	if (iwlagn_tx_skb(priv, control->sta, skb))
		ieee80211_free_txskb(hw, skb);
}