#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_tx_rate_control {struct sk_buff* skb; } ;
struct ieee80211_tx_rate {scalar_t__ count; scalar_t__ idx; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct TYPE_9__ {int cap; } ;
struct ieee80211_sta {TYPE_2__ ht_cap; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; } ;
struct ath_softc {TYPE_5__* hw; } ;
struct ath_rate_table {TYPE_6__* info; } ;
struct ath_rate_priv {struct ath_rate_table* rate_table; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_11__ {TYPE_3__* chan; } ;
struct TYPE_14__ {TYPE_4__ chandef; } ;
struct TYPE_13__ {int dot11rate; int phy; } ;
struct TYPE_12__ {TYPE_7__ conf; } ;
struct TYPE_10__ {scalar_t__ band; } ;

/* Variables and functions */
 scalar_t__ ATH_TXMAXTRY ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int IEEE80211_SCTL_FRAG ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_LDPC ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_CTL_STBC_SHIFT ; 
 int WLAN_RC_PHY_HT_20_SS ; 
 int WLAN_RC_PHY_HT_40_SS ; 
 int ath_rc_get_highest_rix (struct ath_rate_priv*,int*) ; 
 int /*<<< orphan*/  ath_rc_get_lower_rix (struct ath_rate_priv*,int,int*) ; 
 int /*<<< orphan*/  ath_rc_rate_set_rtscts (struct ath_softc*,struct ath_rate_table const*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ath_rc_rate_set_series (struct ath_rate_table const*,struct ieee80211_tx_rate*,struct ieee80211_tx_rate_control*,int,int,int) ; 
 scalar_t__ conf_is_ht (TYPE_7__*) ; 
 scalar_t__ ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ rate_control_send_low (struct ieee80211_sta*,void*,struct ieee80211_tx_rate_control*) ; 

__attribute__((used)) static void ath_get_rate(void *priv, struct ieee80211_sta *sta, void *priv_sta,
			 struct ieee80211_tx_rate_control *txrc)
{
	struct ath_softc *sc = priv;
	struct ath_rate_priv *ath_rc_priv = priv_sta;
	const struct ath_rate_table *rate_table;
	struct sk_buff *skb = txrc->skb;
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *rates = tx_info->control.rates;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;
	u8 try_per_rate, i = 0, rix;
	int is_probe = 0;

	if (rate_control_send_low(sta, priv_sta, txrc))
		return;

	/*
	 * For Multi Rate Retry we use a different number of
	 * retry attempt counts. This ends up looking like this:
	 *
	 * MRR[0] = 4
	 * MRR[1] = 4
	 * MRR[2] = 4
	 * MRR[3] = 8
	 *
	 */
	try_per_rate = 4;

	rate_table = ath_rc_priv->rate_table;
	rix = ath_rc_get_highest_rix(ath_rc_priv, &is_probe);

	if (conf_is_ht(&sc->hw->conf) &&
	    (sta->ht_cap.cap & IEEE80211_HT_CAP_LDPC_CODING))
		tx_info->flags |= IEEE80211_TX_CTL_LDPC;

	if (conf_is_ht(&sc->hw->conf) &&
	    (sta->ht_cap.cap & IEEE80211_HT_CAP_TX_STBC))
		tx_info->flags |= (1 << IEEE80211_TX_CTL_STBC_SHIFT);

	if (is_probe) {
		/*
		 * Set one try for probe rates. For the
		 * probes don't enable RTS.
		 */
		ath_rc_rate_set_series(rate_table, &rates[i++], txrc,
				       1, rix, 0);
		/*
		 * Get the next tried/allowed rate.
		 * No RTS for the next series after the probe rate.
		 */
		ath_rc_get_lower_rix(ath_rc_priv, rix, &rix);
		ath_rc_rate_set_series(rate_table, &rates[i++], txrc,
				       try_per_rate, rix, 0);

		tx_info->flags |= IEEE80211_TX_CTL_RATE_CTRL_PROBE;
	} else {
		/*
		 * Set the chosen rate. No RTS for first series entry.
		 */
		ath_rc_rate_set_series(rate_table, &rates[i++], txrc,
				       try_per_rate, rix, 0);
	}

	for ( ; i < 4; i++) {
		/*
		 * Use twice the number of tries for the last MRR segment.
		 */
		if (i + 1 == 4)
			try_per_rate = 8;

		ath_rc_get_lower_rix(ath_rc_priv, rix, &rix);

		/*
		 * All other rates in the series have RTS enabled.
		 */
		ath_rc_rate_set_series(rate_table, &rates[i], txrc,
				       try_per_rate, rix, 1);
	}

	/*
	 * NB:Change rate series to enable aggregation when operating
	 * at lower MCS rates. When first rate in series is MCS2
	 * in HT40 @ 2.4GHz, series should look like:
	 *
	 * {MCS2, MCS1, MCS0, MCS0}.
	 *
	 * When first rate in series is MCS3 in HT20 @ 2.4GHz, series should
	 * look like:
	 *
	 * {MCS3, MCS2, MCS1, MCS1}
	 *
	 * So, set fourth rate in series to be same as third one for
	 * above conditions.
	 */
	if ((sc->hw->conf.chandef.chan->band == IEEE80211_BAND_2GHZ) &&
	    (conf_is_ht(&sc->hw->conf))) {
		u8 dot11rate = rate_table->info[rix].dot11rate;
		u8 phy = rate_table->info[rix].phy;
		if (i == 4 &&
		    ((dot11rate == 2 && phy == WLAN_RC_PHY_HT_40_SS) ||
		     (dot11rate == 3 && phy == WLAN_RC_PHY_HT_20_SS))) {
			rates[3].idx = rates[2].idx;
			rates[3].flags = rates[2].flags;
		}
	}

	/*
	 * Force hardware to use computed duration for next
	 * fragment by disabling multi-rate retry, which
	 * updates duration based on the multi-rate duration table.
	 *
	 * FIXME: Fix duration
	 */
	if (ieee80211_has_morefrags(fc) ||
	    (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_FRAG)) {
		rates[1].count = rates[2].count = rates[3].count = 0;
		rates[1].idx = rates[2].idx = rates[3].idx = 0;
		rates[0].count = ATH_TXMAXTRY;
	}

	ath_rc_rate_set_rtscts(sc, rate_table, tx_info);
}