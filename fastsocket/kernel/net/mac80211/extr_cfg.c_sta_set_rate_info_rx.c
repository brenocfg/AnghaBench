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
struct sta_info {int last_rx_rate_flag; size_t last_rx_rate_idx; int /*<<< orphan*/  sdata; TYPE_3__* local; int /*<<< orphan*/  last_rx_rate_vht_nss; } ;
struct rate_info {size_t mcs; int /*<<< orphan*/  flags; int /*<<< orphan*/  legacy; int /*<<< orphan*/  nss; } ;
struct ieee80211_supported_band {TYPE_4__* bitrates; } ;
struct TYPE_8__ {int /*<<< orphan*/  bitrate; } ;
struct TYPE_6__ {TYPE_1__* wiphy; } ;
struct TYPE_7__ {TYPE_2__ hw; } ;
struct TYPE_5__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  RATE_INFO_FLAGS_160_MHZ_WIDTH ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_80P80_MHZ_WIDTH ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_80_MHZ_WIDTH ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_VHT_MCS ; 
 int RX_FLAG_160MHZ ; 
 int RX_FLAG_40MHZ ; 
 int RX_FLAG_80MHZ ; 
 int RX_FLAG_80P80MHZ ; 
 int RX_FLAG_HT ; 
 int RX_FLAG_SHORT_GI ; 
 int RX_FLAG_VHT ; 
 size_t ieee80211_get_sdata_band (int /*<<< orphan*/ ) ; 

void sta_set_rate_info_rx(struct sta_info *sta, struct rate_info *rinfo)
{
	rinfo->flags = 0;

	if (sta->last_rx_rate_flag & RX_FLAG_HT) {
		rinfo->flags |= RATE_INFO_FLAGS_MCS;
		rinfo->mcs = sta->last_rx_rate_idx;
	} else if (sta->last_rx_rate_flag & RX_FLAG_VHT) {
		rinfo->flags |= RATE_INFO_FLAGS_VHT_MCS;
		rinfo->nss = sta->last_rx_rate_vht_nss;
		rinfo->mcs = sta->last_rx_rate_idx;
	} else {
		struct ieee80211_supported_band *sband;

		sband = sta->local->hw.wiphy->bands[
				ieee80211_get_sdata_band(sta->sdata)];
		rinfo->legacy =
			sband->bitrates[sta->last_rx_rate_idx].bitrate;
	}

	if (sta->last_rx_rate_flag & RX_FLAG_40MHZ)
		rinfo->flags |= RATE_INFO_FLAGS_40_MHZ_WIDTH;
	if (sta->last_rx_rate_flag & RX_FLAG_SHORT_GI)
		rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
	if (sta->last_rx_rate_flag & RX_FLAG_80MHZ)
		rinfo->flags |= RATE_INFO_FLAGS_80_MHZ_WIDTH;
	if (sta->last_rx_rate_flag & RX_FLAG_80P80MHZ)
		rinfo->flags |= RATE_INFO_FLAGS_80P80_MHZ_WIDTH;
	if (sta->last_rx_rate_flag & RX_FLAG_160MHZ)
		rinfo->flags |= RATE_INFO_FLAGS_160_MHZ_WIDTH;
}