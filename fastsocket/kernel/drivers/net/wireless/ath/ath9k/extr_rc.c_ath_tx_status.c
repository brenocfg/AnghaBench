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
typedef  int u8 ;
struct sk_buff {scalar_t__ protocol; scalar_t__ data; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath_softc {TYPE_1__* hw; } ;
struct ath_rate_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PAE ; 
 scalar_t__ IEEE80211_AC_VO ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_STAT_AMPDU ; 
 int IEEE80211_TX_STAT_TX_FILTERED ; 
 int /*<<< orphan*/  ath_rc_tx_status (struct ath_softc*,struct ath_rate_priv*,struct sk_buff*) ; 
 scalar_t__ ath_tx_aggr_check (struct ath_softc*,struct ieee80211_sta*,int) ; 
 scalar_t__ conf_is_ht (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_session (struct ieee80211_sta*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_get_queue_mapping (struct sk_buff*) ; 

__attribute__((used)) static void ath_tx_status(void *priv, struct ieee80211_supported_band *sband,
			  struct ieee80211_sta *sta, void *priv_sta,
			  struct sk_buff *skb)
{
	struct ath_softc *sc = priv;
	struct ath_rate_priv *ath_rc_priv = priv_sta;
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;

	if (!priv_sta || !ieee80211_is_data(fc))
		return;

	/* This packet was aggregated but doesn't carry status info */
	if ((tx_info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(tx_info->flags & IEEE80211_TX_STAT_AMPDU))
		return;

	if (tx_info->flags & IEEE80211_TX_STAT_TX_FILTERED)
		return;

	ath_rc_tx_status(sc, ath_rc_priv, skb);

	/* Check if aggregation has to be enabled for this tid */
	if (conf_is_ht(&sc->hw->conf) &&
	    !(skb->protocol == cpu_to_be16(ETH_P_PAE))) {
		if (ieee80211_is_data_qos(fc) &&
		    skb_get_queue_mapping(skb) != IEEE80211_AC_VO) {
			u8 *qc, tid;

			qc = ieee80211_get_qos_ctl(hdr);
			tid = qc[0] & 0xf;

			if(ath_tx_aggr_check(sc, sta, tid))
				ieee80211_start_tx_ba_session(sta, tid, 0);
		}
	}
}