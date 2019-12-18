#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_5__ {int rx_chains_num; int tx_chains_num; int ht40_channel; } ;
struct il_priv {TYPE_3__* cfg; TYPE_1__ hw_params; } ;
struct TYPE_8__ {int* rx_mask; int tx_params; int /*<<< orphan*/  rx_highest; } ;
struct ieee80211_sta_ht_cap {int ht_supported; TYPE_4__ mcs; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  cap; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_7__ {TYPE_2__* mod_params; } ;
struct TYPE_6__ {scalar_t__ amsdu_size_8K; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CFG_HT_MPDU_DENSITY_DEF ; 
 int /*<<< orphan*/  CFG_HT_RX_AMPDU_FACTOR_DEF ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_MAX_AMSDU ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_MCS_RX_HIGHEST_MASK ; 
 int IEEE80211_HT_MCS_TX_DEFINED ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int MAX_BIT_RATE_20_MHZ ; 
 int MAX_BIT_RATE_40_MHZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
il_init_ht_hw_capab(const struct il_priv *il,
		    struct ieee80211_sta_ht_cap *ht_info,
		    enum ieee80211_band band)
{
	u16 max_bit_rate = 0;
	u8 rx_chains_num = il->hw_params.rx_chains_num;
	u8 tx_chains_num = il->hw_params.tx_chains_num;

	ht_info->cap = 0;
	memset(&ht_info->mcs, 0, sizeof(ht_info->mcs));

	ht_info->ht_supported = true;

	ht_info->cap |= IEEE80211_HT_CAP_SGI_20;
	max_bit_rate = MAX_BIT_RATE_20_MHZ;
	if (il->hw_params.ht40_channel & BIT(band)) {
		ht_info->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		ht_info->cap |= IEEE80211_HT_CAP_SGI_40;
		ht_info->mcs.rx_mask[4] = 0x01;
		max_bit_rate = MAX_BIT_RATE_40_MHZ;
	}

	if (il->cfg->mod_params->amsdu_size_8K)
		ht_info->cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	ht_info->ampdu_factor = CFG_HT_RX_AMPDU_FACTOR_DEF;
	ht_info->ampdu_density = CFG_HT_MPDU_DENSITY_DEF;

	ht_info->mcs.rx_mask[0] = 0xFF;
	if (rx_chains_num >= 2)
		ht_info->mcs.rx_mask[1] = 0xFF;
	if (rx_chains_num >= 3)
		ht_info->mcs.rx_mask[2] = 0xFF;

	/* Highest supported Rx data rate */
	max_bit_rate *= rx_chains_num;
	WARN_ON(max_bit_rate & ~IEEE80211_HT_MCS_RX_HIGHEST_MASK);
	ht_info->mcs.rx_highest = cpu_to_le16(max_bit_rate);

	/* Tx MCS capabilities */
	ht_info->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	if (tx_chains_num != rx_chains_num) {
		ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		ht_info->mcs.tx_params |=
		    ((tx_chains_num -
		      1) << IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT);
	}
}