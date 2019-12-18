#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
typedef  unsigned int u16 ;
struct rate_info {size_t mcs; int /*<<< orphan*/  legacy; int /*<<< orphan*/  flags; int /*<<< orphan*/  nss; } ;
struct ieee80211_supported_band {TYPE_3__* bitrates; } ;
struct ieee80211_rx_status {unsigned int mactime; int flag; size_t rate_idx; size_t band; int /*<<< orphan*/  vht_nss; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  ri ;
struct TYPE_6__ {int /*<<< orphan*/  bitrate; } ;
struct TYPE_4__ {struct ieee80211_supported_band** bands; } ;

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
 int RX_FLAG_MACTIME_END ; 
 int RX_FLAG_SHORT_GI ; 
 int RX_FLAG_VHT ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int cfg80211_calculate_bitrate (struct rate_info*) ; 
 int /*<<< orphan*/  ieee80211_have_rx_timestamp (struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  memset (struct rate_info*,int /*<<< orphan*/ ,int) ; 

u64 ieee80211_calculate_rx_timestamp(struct ieee80211_local *local,
				     struct ieee80211_rx_status *status,
				     unsigned int mpdu_len,
				     unsigned int mpdu_offset)
{
	u64 ts = status->mactime;
	struct rate_info ri;
	u16 rate;

	if (WARN_ON(!ieee80211_have_rx_timestamp(status)))
		return 0;

	memset(&ri, 0, sizeof(ri));

	/* Fill cfg80211 rate info */
	if (status->flag & RX_FLAG_HT) {
		ri.mcs = status->rate_idx;
		ri.flags |= RATE_INFO_FLAGS_MCS;
		if (status->flag & RX_FLAG_40MHZ)
			ri.flags |= RATE_INFO_FLAGS_40_MHZ_WIDTH;
		if (status->flag & RX_FLAG_SHORT_GI)
			ri.flags |= RATE_INFO_FLAGS_SHORT_GI;
	} else if (status->flag & RX_FLAG_VHT) {
		ri.flags |= RATE_INFO_FLAGS_VHT_MCS;
		ri.mcs = status->rate_idx;
		ri.nss = status->vht_nss;
		if (status->flag & RX_FLAG_40MHZ)
			ri.flags |= RATE_INFO_FLAGS_40_MHZ_WIDTH;
		if (status->flag & RX_FLAG_80MHZ)
			ri.flags |= RATE_INFO_FLAGS_80_MHZ_WIDTH;
		if (status->flag & RX_FLAG_80P80MHZ)
			ri.flags |= RATE_INFO_FLAGS_80P80_MHZ_WIDTH;
		if (status->flag & RX_FLAG_160MHZ)
			ri.flags |= RATE_INFO_FLAGS_160_MHZ_WIDTH;
		if (status->flag & RX_FLAG_SHORT_GI)
			ri.flags |= RATE_INFO_FLAGS_SHORT_GI;
	} else {
		struct ieee80211_supported_band *sband;

		sband = local->hw.wiphy->bands[status->band];
		ri.legacy = sband->bitrates[status->rate_idx].bitrate;
	}

	rate = cfg80211_calculate_bitrate(&ri);

	/* rewind from end of MPDU */
	if (status->flag & RX_FLAG_MACTIME_END)
		ts -= mpdu_len * 8 * 10 / rate;

	ts += mpdu_offset * 8 * 10 / rate;

	return ts;
}