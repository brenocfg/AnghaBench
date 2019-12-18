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
typedef  scalar_t__ u32 ;
struct ieee80211_vht_operation {int chan_width; int /*<<< orphan*/  center_freq_seg2_idx; int /*<<< orphan*/  center_freq_seg1_idx; } ;
struct TYPE_8__ {int /*<<< orphan*/  vht_supported; } ;
struct TYPE_7__ {int cap; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_supported_band {TYPE_3__ vht_cap; TYPE_2__ ht_cap; } ;
struct ieee80211_if_managed {scalar_t__ flags; } ;
struct TYPE_6__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_5__* local; TYPE_1__ u; } ;
struct ieee80211_ht_operation {int ht_param; int /*<<< orphan*/  primary_chan; } ;
struct ieee80211_channel {scalar_t__ center_freq; int /*<<< orphan*/  band; } ;
struct cfg80211_chan_def {scalar_t__ width; scalar_t__ center_freq1; void* center_freq2; struct ieee80211_channel* chan; } ;
struct TYPE_9__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_10__ {TYPE_4__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
#define  IEEE80211_HT_PARAM_CHA_SEC_ABOVE 133 
#define  IEEE80211_HT_PARAM_CHA_SEC_BELOW 132 
 int IEEE80211_HT_PARAM_CHA_SEC_OFFSET ; 
 scalar_t__ IEEE80211_STA_DISABLE_40MHZ ; 
 scalar_t__ IEEE80211_STA_DISABLE_HT ; 
 scalar_t__ IEEE80211_STA_DISABLE_VHT ; 
#define  IEEE80211_VHT_CHANWIDTH_160MHZ 131 
#define  IEEE80211_VHT_CHANWIDTH_80MHZ 130 
#define  IEEE80211_VHT_CHANWIDTH_80P80MHZ 129 
#define  IEEE80211_VHT_CHANWIDTH_USE_HT 128 
 scalar_t__ NL80211_CHAN_WIDTH_160 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 void* NL80211_CHAN_WIDTH_40 ; 
 scalar_t__ NL80211_CHAN_WIDTH_80 ; 
 scalar_t__ NL80211_CHAN_WIDTH_80P80 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cfg80211_chandef_compatible (struct cfg80211_chan_def*,struct cfg80211_chan_def*) ; 
 scalar_t__ cfg80211_chandef_identical (struct cfg80211_chan_def*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  cfg80211_chandef_usable (int /*<<< orphan*/ ,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def*) ; 
 scalar_t__ chandef_downgrade (struct cfg80211_chan_def*) ; 
 void* ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,...) ; 

__attribute__((used)) static u32
ieee80211_determine_chantype(struct ieee80211_sub_if_data *sdata,
			     struct ieee80211_supported_band *sband,
			     struct ieee80211_channel *channel,
			     const struct ieee80211_ht_operation *ht_oper,
			     const struct ieee80211_vht_operation *vht_oper,
			     struct cfg80211_chan_def *chandef, bool tracking)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct cfg80211_chan_def vht_chandef;
	u32 ht_cfreq, ret;

	chandef->chan = channel;
	chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
	chandef->center_freq1 = channel->center_freq;
	chandef->center_freq2 = 0;

	if (!ht_oper || !sband->ht_cap.ht_supported) {
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		goto out;
	}

	chandef->width = NL80211_CHAN_WIDTH_20;

	ht_cfreq = ieee80211_channel_to_frequency(ht_oper->primary_chan,
						  channel->band);
	/* check that channel matches the right operating channel */
	if (!tracking && channel->center_freq != ht_cfreq) {
		/*
		 * It's possible that some APs are confused here;
		 * Netgear WNDR3700 sometimes reports 4 higher than
		 * the actual channel in association responses, but
		 * since we look at probe response/beacon data here
		 * it should be OK.
		 */
		sdata_info(sdata,
			   "Wrong control channel: center-freq: %d ht-cfreq: %d ht->primary_chan: %d band: %d - Disabling HT\n",
			   channel->center_freq, ht_cfreq,
			   ht_oper->primary_chan, channel->band);
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		goto out;
	}

	/* check 40 MHz support, if we have it */
	if (sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) {
		switch (ht_oper->ht_param & IEEE80211_HT_PARAM_CHA_SEC_OFFSET) {
		case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
			chandef->width = NL80211_CHAN_WIDTH_40;
			chandef->center_freq1 += 10;
			break;
		case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
			chandef->width = NL80211_CHAN_WIDTH_40;
			chandef->center_freq1 -= 10;
			break;
		}
	} else {
		/* 40 MHz (and 80 MHz) must be supported for VHT */
		ret = IEEE80211_STA_DISABLE_VHT;
		/* also mark 40 MHz disabled */
		ret |= IEEE80211_STA_DISABLE_40MHZ;
		goto out;
	}

	if (!vht_oper || !sband->vht_cap.vht_supported) {
		ret = IEEE80211_STA_DISABLE_VHT;
		goto out;
	}

	vht_chandef.chan = channel;
	vht_chandef.center_freq1 =
		ieee80211_channel_to_frequency(vht_oper->center_freq_seg1_idx,
					       channel->band);
	vht_chandef.center_freq2 = 0;

	switch (vht_oper->chan_width) {
	case IEEE80211_VHT_CHANWIDTH_USE_HT:
		vht_chandef.width = chandef->width;
		break;
	case IEEE80211_VHT_CHANWIDTH_80MHZ:
		vht_chandef.width = NL80211_CHAN_WIDTH_80;
		break;
	case IEEE80211_VHT_CHANWIDTH_160MHZ:
		vht_chandef.width = NL80211_CHAN_WIDTH_160;
		break;
	case IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		vht_chandef.width = NL80211_CHAN_WIDTH_80P80;
		vht_chandef.center_freq2 =
			ieee80211_channel_to_frequency(
				vht_oper->center_freq_seg2_idx,
				channel->band);
		break;
	default:
		if (!(ifmgd->flags & IEEE80211_STA_DISABLE_VHT))
			sdata_info(sdata,
				   "AP VHT operation IE has invalid channel width (%d), disable VHT\n",
				   vht_oper->chan_width);
		ret = IEEE80211_STA_DISABLE_VHT;
		goto out;
	}

	if (!cfg80211_chandef_valid(&vht_chandef)) {
		if (!(ifmgd->flags & IEEE80211_STA_DISABLE_VHT))
			sdata_info(sdata,
				   "AP VHT information is invalid, disable VHT\n");
		ret = IEEE80211_STA_DISABLE_VHT;
		goto out;
	}

	if (cfg80211_chandef_identical(chandef, &vht_chandef)) {
		ret = 0;
		goto out;
	}

	if (!cfg80211_chandef_compatible(chandef, &vht_chandef)) {
		if (!(ifmgd->flags & IEEE80211_STA_DISABLE_VHT))
			sdata_info(sdata,
				   "AP VHT information doesn't match HT, disable VHT\n");
		ret = IEEE80211_STA_DISABLE_VHT;
		goto out;
	}

	*chandef = vht_chandef;

	ret = 0;

out:
	/* don't print the message below for VHT mismatch if VHT is disabled */
	if (ret & IEEE80211_STA_DISABLE_VHT)
		vht_chandef = *chandef;

	/*
	 * Ignore the DISABLED flag when we're already connected and only
	 * tracking the APs beacon for bandwidth changes - otherwise we
	 * might get disconnected here if we connect to an AP, update our
	 * regulatory information based on the AP's country IE and the
	 * information we have is wrong/outdated and disables the channel
	 * that we're actually using for the connection to the AP.
	 */
	while (!cfg80211_chandef_usable(sdata->local->hw.wiphy, chandef,
					tracking ? 0 :
						   IEEE80211_CHAN_DISABLED)) {
		if (WARN_ON(chandef->width == NL80211_CHAN_WIDTH_20_NOHT)) {
			ret = IEEE80211_STA_DISABLE_HT |
			      IEEE80211_STA_DISABLE_VHT;
			break;
		}

		ret |= chandef_downgrade(chandef);
	}

	if (chandef->width != vht_chandef.width && !tracking)
		sdata_info(sdata,
			   "capabilities/regulatory prevented using AP HT/VHT configuration, downgraded\n");

	WARN_ON_ONCE(!cfg80211_chandef_valid(chandef));
	return ret;
}