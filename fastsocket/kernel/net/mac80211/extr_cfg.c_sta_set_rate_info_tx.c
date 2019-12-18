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
struct sta_info {int /*<<< orphan*/  sdata; TYPE_3__* local; } ;
struct rate_info {size_t mcs; int /*<<< orphan*/  flags; int /*<<< orphan*/  legacy; int /*<<< orphan*/  nss; } ;
struct ieee80211_tx_rate {int flags; size_t idx; } ;
struct ieee80211_supported_band {TYPE_4__* bitrates; } ;
struct TYPE_8__ {int /*<<< orphan*/  bitrate; } ;
struct TYPE_6__ {TYPE_1__* wiphy; } ;
struct TYPE_7__ {TYPE_2__ hw; } ;
struct TYPE_5__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int IEEE80211_TX_RC_160_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_160_MHZ_WIDTH ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_80_MHZ_WIDTH ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_VHT_MCS ; 
 size_t ieee80211_get_sdata_band (int /*<<< orphan*/ ) ; 
 size_t ieee80211_rate_get_vht_mcs (struct ieee80211_tx_rate const*) ; 
 int /*<<< orphan*/  ieee80211_rate_get_vht_nss (struct ieee80211_tx_rate const*) ; 

void sta_set_rate_info_tx(struct sta_info *sta,
			  const struct ieee80211_tx_rate *rate,
			  struct rate_info *rinfo)
{
	rinfo->flags = 0;
	if (rate->flags & IEEE80211_TX_RC_MCS) {
		rinfo->flags |= RATE_INFO_FLAGS_MCS;
		rinfo->mcs = rate->idx;
	} else if (rate->flags & IEEE80211_TX_RC_VHT_MCS) {
		rinfo->flags |= RATE_INFO_FLAGS_VHT_MCS;
		rinfo->mcs = ieee80211_rate_get_vht_mcs(rate);
		rinfo->nss = ieee80211_rate_get_vht_nss(rate);
	} else {
		struct ieee80211_supported_band *sband;
		sband = sta->local->hw.wiphy->bands[
				ieee80211_get_sdata_band(sta->sdata)];
		rinfo->legacy = sband->bitrates[rate->idx].bitrate;
	}
	if (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		rinfo->flags |= RATE_INFO_FLAGS_40_MHZ_WIDTH;
	if (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		rinfo->flags |= RATE_INFO_FLAGS_80_MHZ_WIDTH;
	if (rate->flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		rinfo->flags |= RATE_INFO_FLAGS_160_MHZ_WIDTH;
	if (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
}