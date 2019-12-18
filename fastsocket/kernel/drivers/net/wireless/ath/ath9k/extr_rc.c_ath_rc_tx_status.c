#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_rate {scalar_t__ idx; int count; int flags; } ;
struct TYPE_4__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ status; } ;
struct ath_softc {TYPE_1__* hw; } ;
struct ath_rate_priv {int ht_cap; } ;
struct TYPE_3__ {size_t max_rates; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_STAT_ACK ; 
 int WLAN_RC_40_FLAG ; 
 int /*<<< orphan*/  ath_debug_stat_rc (struct ath_rate_priv*,size_t) ; 
 size_t ath_rc_get_rateindex (struct ath_rate_priv*,struct ieee80211_tx_rate*) ; 
 int /*<<< orphan*/  ath_rc_update_ht (struct ath_softc*,struct ath_rate_priv*,struct ieee80211_tx_info*,size_t,int,int) ; 

__attribute__((used)) static void ath_rc_tx_status(struct ath_softc *sc,
			     struct ath_rate_priv *ath_rc_priv,
			     struct sk_buff *skb)
{
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *rates = tx_info->status.rates;
	struct ieee80211_tx_rate *rate;
	int final_ts_idx = 0, xretries = 0, long_retry = 0;
	u8 flags;
	u32 i = 0, rix;

	for (i = 0; i < sc->hw->max_rates; i++) {
		rate = &tx_info->status.rates[i];
		if (rate->idx < 0 || !rate->count)
			break;

		final_ts_idx = i;
		long_retry = rate->count - 1;
	}

	if (!(tx_info->flags & IEEE80211_TX_STAT_ACK))
		xretries = 1;

	/*
	 * If the first rate is not the final index, there
	 * are intermediate rate failures to be processed.
	 */
	if (final_ts_idx != 0) {
		for (i = 0; i < final_ts_idx ; i++) {
			if (rates[i].count != 0 && (rates[i].idx >= 0)) {
				flags = rates[i].flags;

				/* If HT40 and we have switched mode from
				 * 40 to 20 => don't update */

				if ((flags & IEEE80211_TX_RC_40_MHZ_WIDTH) &&
				    !(ath_rc_priv->ht_cap & WLAN_RC_40_FLAG))
					return;

				rix = ath_rc_get_rateindex(ath_rc_priv, &rates[i]);
				ath_rc_update_ht(sc, ath_rc_priv, tx_info,
						 rix, xretries ? 1 : 2,
						 rates[i].count);
			}
		}
	}

	flags = rates[final_ts_idx].flags;

	/* If HT40 and we have switched mode from 40 to 20 => don't update */
	if ((flags & IEEE80211_TX_RC_40_MHZ_WIDTH) &&
	    !(ath_rc_priv->ht_cap & WLAN_RC_40_FLAG))
		return;

	rix = ath_rc_get_rateindex(ath_rc_priv, &rates[final_ts_idx]);
	ath_rc_update_ht(sc, ath_rc_priv, tx_info, rix, xretries, long_retry);
	ath_debug_stat_rc(ath_rc_priv, rix);
}