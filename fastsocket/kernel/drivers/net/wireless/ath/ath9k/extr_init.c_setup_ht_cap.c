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
struct TYPE_4__ {int tx_params; int* rx_mask; } ;
struct ieee80211_sta_ht_cap {int ht_supported; int cap; TYPE_2__ mcs; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; } ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct TYPE_3__ {int hw_caps; } ;
struct ath_hw {int /*<<< orphan*/  rxchainmask; int /*<<< orphan*/  txchainmask; TYPE_1__ caps; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int ATH9K_HW_CAP_LDPC ; 
 int ATH9K_HW_CAP_SGI_20 ; 
 int /*<<< orphan*/  CONFIG ; 
 int IEEE80211_HT_CAP_DSSSCCK40 ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SM_PS ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_64K ; 
 int IEEE80211_HT_MCS_TX_DEFINED ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int /*<<< orphan*/  IEEE80211_HT_MPDU_DENSITY_8 ; 
 int ath9k_cmn_count_streams (int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_ht_cap(struct ath_softc *sc,
			 struct ieee80211_sta_ht_cap *ht_info)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	u8 tx_streams, rx_streams;
	int i, max_streams;

	ht_info->ht_supported = true;
	ht_info->cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_SM_PS |
		       IEEE80211_HT_CAP_SGI_40 |
		       IEEE80211_HT_CAP_DSSSCCK40;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_LDPC)
		ht_info->cap |= IEEE80211_HT_CAP_LDPC_CODING;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_SGI_20)
		ht_info->cap |= IEEE80211_HT_CAP_SGI_20;

	ht_info->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_info->ampdu_density = IEEE80211_HT_MPDU_DENSITY_8;

	if (AR_SREV_9330(ah) || AR_SREV_9485(ah) || AR_SREV_9565(ah))
		max_streams = 1;
	else if (AR_SREV_9462(ah))
		max_streams = 2;
	else if (AR_SREV_9300_20_OR_LATER(ah))
		max_streams = 3;
	else
		max_streams = 2;

	if (AR_SREV_9280_20_OR_LATER(ah)) {
		if (max_streams >= 2)
			ht_info->cap |= IEEE80211_HT_CAP_TX_STBC;
		ht_info->cap |= (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);
	}

	/* set up supported mcs set */
	memset(&ht_info->mcs, 0, sizeof(ht_info->mcs));
	tx_streams = ath9k_cmn_count_streams(ah->txchainmask, max_streams);
	rx_streams = ath9k_cmn_count_streams(ah->rxchainmask, max_streams);

	ath_dbg(common, CONFIG, "TX streams %d, RX streams: %d\n",
		tx_streams, rx_streams);

	if (tx_streams != rx_streams) {
		ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		ht_info->mcs.tx_params |= ((tx_streams - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT);
	}

	for (i = 0; i < rx_streams; i++)
		ht_info->mcs.rx_mask[i] = 0xff;

	ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_DEFINED;
}