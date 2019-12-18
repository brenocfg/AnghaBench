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
typedef  int u32 ;
struct sk_buff {int len; } ;
struct ieee80211_tx_rate {int flags; } ;
struct TYPE_2__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int AR9170_MAC_BCN_HT1_BWC_40M_DUP ; 
 int AR9170_MAC_BCN_HT1_BWC_40M_SHARED ; 
 int /*<<< orphan*/  AR9170_MAC_BCN_HT1_CHAIN_MASK ; 
 int AR9170_MAC_BCN_HT1_HT_EN ; 
 int /*<<< orphan*/  AR9170_MAC_BCN_HT1_PWR_CTRL ; 
 int /*<<< orphan*/  AR9170_MAC_BCN_HT1_TPC ; 
 int AR9170_MAC_BCN_HT1_TX_ANT0 ; 
 int AR9170_MAC_BCN_HT1_TX_ANT1 ; 
 int AR9170_MAC_BCN_HT2_BW40 ; 
 int /*<<< orphan*/  AR9170_MAC_BCN_HT2_LEN ; 
 int AR9170_MAC_BCN_HT2_SGI ; 
 int AR9170_TX_PHY_RATE_CCK_11M ; 
 unsigned int AR9170_TX_PHY_TXCHAIN_2 ; 
 int FCS_LEN ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_DUP_DATA ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int /*<<< orphan*/  SET_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  carl9170_tx_rate_tpc_chains (struct ar9170*,struct ieee80211_tx_info*,struct ieee80211_tx_rate*,int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static bool carl9170_tx_beacon_physet(struct ar9170 *ar, struct sk_buff *skb,
				      u32 *ht1, u32 *plcp)
{
	struct ieee80211_tx_info *txinfo;
	struct ieee80211_tx_rate *rate;
	unsigned int power, chains;
	bool ht_rate;

	txinfo = IEEE80211_SKB_CB(skb);
	rate = &txinfo->control.rates[0];
	ht_rate = !!(txinfo->control.rates[0].flags & IEEE80211_TX_RC_MCS);
	carl9170_tx_rate_tpc_chains(ar, txinfo, rate, plcp, &power, &chains);

	*ht1 = AR9170_MAC_BCN_HT1_TX_ANT0;
	if (chains == AR9170_TX_PHY_TXCHAIN_2)
		*ht1 |= AR9170_MAC_BCN_HT1_TX_ANT1;
	SET_VAL(AR9170_MAC_BCN_HT1_PWR_CTRL, *ht1, 7);
	SET_VAL(AR9170_MAC_BCN_HT1_TPC, *ht1, power);
	SET_VAL(AR9170_MAC_BCN_HT1_CHAIN_MASK, *ht1, chains);

	if (ht_rate) {
		*ht1 |= AR9170_MAC_BCN_HT1_HT_EN;
		if (rate->flags & IEEE80211_TX_RC_SHORT_GI)
			*plcp |= AR9170_MAC_BCN_HT2_SGI;

		if (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH) {
			*ht1 |= AR9170_MAC_BCN_HT1_BWC_40M_SHARED;
			*plcp |= AR9170_MAC_BCN_HT2_BW40;
		} else if (rate->flags & IEEE80211_TX_RC_DUP_DATA) {
			*ht1 |= AR9170_MAC_BCN_HT1_BWC_40M_DUP;
			*plcp |= AR9170_MAC_BCN_HT2_BW40;
		}

		SET_VAL(AR9170_MAC_BCN_HT2_LEN, *plcp, skb->len + FCS_LEN);
	} else {
		if (*plcp <= AR9170_TX_PHY_RATE_CCK_11M)
			*plcp |= ((skb->len + FCS_LEN) << (3 + 16)) + 0x0400;
		else
			*plcp |= ((skb->len + FCS_LEN) << 16) + 0x0010;
	}

	return ht_rate;
}