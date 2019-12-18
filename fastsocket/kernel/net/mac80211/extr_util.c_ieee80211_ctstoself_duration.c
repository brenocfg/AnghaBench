#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_8__ {size_t rts_cts_rate_idx; } ;
struct ieee80211_tx_info {size_t band; int flags; TYPE_3__ control; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  band; struct ieee80211_rate* bitrates; } ;
struct TYPE_9__ {int use_short_preamble; } ;
struct TYPE_10__ {TYPE_4__ bss_conf; } ;
struct ieee80211_sub_if_data {int flags; TYPE_5__ vif; } ;
struct ieee80211_rate {int flags; int /*<<< orphan*/  bitrate; } ;
struct TYPE_7__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int IEEE80211_RATE_ERP_G ; 
 int IEEE80211_SDATA_OPERATING_GMODE ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 scalar_t__ ieee80211_frame_duration (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

__le16 ieee80211_ctstoself_duration(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    size_t frame_len,
				    const struct ieee80211_tx_info *frame_txctl)
{
	struct ieee80211_local *local = hw_to_local(hw);
	struct ieee80211_rate *rate;
	struct ieee80211_sub_if_data *sdata;
	bool short_preamble;
	int erp;
	u16 dur;
	struct ieee80211_supported_band *sband;

	sband = local->hw.wiphy->bands[frame_txctl->band];

	short_preamble = false;

	rate = &sband->bitrates[frame_txctl->control.rts_cts_rate_idx];
	erp = 0;
	if (vif) {
		sdata = vif_to_sdata(vif);
		short_preamble = sdata->vif.bss_conf.use_short_preamble;
		if (sdata->flags & IEEE80211_SDATA_OPERATING_GMODE)
			erp = rate->flags & IEEE80211_RATE_ERP_G;
	}

	/* Data frame duration */
	dur = ieee80211_frame_duration(sband->band, frame_len, rate->bitrate,
				       erp, short_preamble);
	if (!(frame_txctl->flags & IEEE80211_TX_CTL_NO_ACK)) {
		/* ACK duration */
		dur += ieee80211_frame_duration(sband->band, 10, rate->bitrate,
						erp, short_preamble);
	}

	return cpu_to_le16(dur);
}