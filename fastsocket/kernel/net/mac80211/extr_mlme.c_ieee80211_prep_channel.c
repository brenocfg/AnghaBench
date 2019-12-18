#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_vht_cap {int dummy; } ;
struct TYPE_11__ {scalar_t__ vht_supported; } ;
struct TYPE_10__ {scalar_t__ ht_supported; } ;
struct ieee80211_supported_band {TYPE_5__ vht_cap; TYPE_4__ ht_cap; } ;
struct ieee80211_if_managed {int flags; } ;
struct TYPE_7__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  smps_mode; int /*<<< orphan*/  needed_rx_chains; TYPE_1__ u; struct ieee80211_local* local; } ;
struct TYPE_9__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {int /*<<< orphan*/  rx_chains; TYPE_3__ hw; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct ieee80211_ht_cap {int dummy; } ;
struct cfg80211_chan_def {scalar_t__ width; } ;
struct cfg80211_bss {TYPE_6__* channel; } ;
struct TYPE_12__ {size_t band; } ;
struct TYPE_8__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANCTX_SHARED ; 
 int /*<<< orphan*/  IEEE80211_SMPS_OFF ; 
 int IEEE80211_STA_DISABLE_160MHZ ; 
 int IEEE80211_STA_DISABLE_40MHZ ; 
 int IEEE80211_STA_DISABLE_80P80MHZ ; 
 int IEEE80211_STA_DISABLE_HT ; 
 int IEEE80211_STA_DISABLE_VHT ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int /*<<< orphan*/  WLAN_EID_VHT_CAPABILITY ; 
 int /*<<< orphan*/  WLAN_EID_VHT_OPERATION ; 
 int chandef_downgrade (struct cfg80211_chan_def*) ; 
 int* ieee80211_bss_get_ie (struct cfg80211_bss*,int /*<<< orphan*/ ) ; 
 int ieee80211_determine_chantype (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,TYPE_6__*,struct ieee80211_ht_operation const*,struct ieee80211_vht_operation const*,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  ieee80211_ht_vht_rx_chains (struct ieee80211_sub_if_data*,struct cfg80211_bss*) ; 
 int ieee80211_vif_use_channel (struct ieee80211_sub_if_data*,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*) ; 

__attribute__((used)) static int ieee80211_prep_channel(struct ieee80211_sub_if_data *sdata,
				  struct cfg80211_bss *cbss)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	const struct ieee80211_ht_operation *ht_oper = NULL;
	const struct ieee80211_vht_operation *vht_oper = NULL;
	struct ieee80211_supported_band *sband;
	struct cfg80211_chan_def chandef;
	int ret;

	sband = local->hw.wiphy->bands[cbss->channel->band];

	ifmgd->flags &= ~(IEEE80211_STA_DISABLE_40MHZ |
			  IEEE80211_STA_DISABLE_80P80MHZ |
			  IEEE80211_STA_DISABLE_160MHZ);

	rcu_read_lock();

	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_HT) &&
	    sband->ht_cap.ht_supported) {
		const u8 *ht_oper_ie, *ht_cap;

		ht_oper_ie = ieee80211_bss_get_ie(cbss, WLAN_EID_HT_OPERATION);
		if (ht_oper_ie && ht_oper_ie[1] >= sizeof(*ht_oper))
			ht_oper = (void *)(ht_oper_ie + 2);

		ht_cap = ieee80211_bss_get_ie(cbss, WLAN_EID_HT_CAPABILITY);
		if (!ht_cap || ht_cap[1] < sizeof(struct ieee80211_ht_cap)) {
			ifmgd->flags |= IEEE80211_STA_DISABLE_HT;
			ht_oper = NULL;
		}
	}

	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_VHT) &&
	    sband->vht_cap.vht_supported) {
		const u8 *vht_oper_ie, *vht_cap;

		vht_oper_ie = ieee80211_bss_get_ie(cbss,
						   WLAN_EID_VHT_OPERATION);
		if (vht_oper_ie && vht_oper_ie[1] >= sizeof(*vht_oper))
			vht_oper = (void *)(vht_oper_ie + 2);
		if (vht_oper && !ht_oper) {
			vht_oper = NULL;
			sdata_info(sdata,
				   "AP advertised VHT without HT, disabling both\n");
			ifmgd->flags |= IEEE80211_STA_DISABLE_HT;
			ifmgd->flags |= IEEE80211_STA_DISABLE_VHT;
		}

		vht_cap = ieee80211_bss_get_ie(cbss, WLAN_EID_VHT_CAPABILITY);
		if (!vht_cap || vht_cap[1] < sizeof(struct ieee80211_vht_cap)) {
			ifmgd->flags |= IEEE80211_STA_DISABLE_VHT;
			vht_oper = NULL;
		}
	}

	ifmgd->flags |= ieee80211_determine_chantype(sdata, sband,
						     cbss->channel,
						     ht_oper, vht_oper,
						     &chandef, false);

	sdata->needed_rx_chains = min(ieee80211_ht_vht_rx_chains(sdata, cbss),
				      local->rx_chains);

	rcu_read_unlock();

	/* will change later if needed */
	sdata->smps_mode = IEEE80211_SMPS_OFF;

	/*
	 * If this fails (possibly due to channel context sharing
	 * on incompatible channels, e.g. 80+80 and 160 sharing the
	 * same control channel) try to use a smaller bandwidth.
	 */
	ret = ieee80211_vif_use_channel(sdata, &chandef,
					IEEE80211_CHANCTX_SHARED);
	while (ret && chandef.width != NL80211_CHAN_WIDTH_20_NOHT) {
		ifmgd->flags |= chandef_downgrade(&chandef);
		ret = ieee80211_vif_use_channel(sdata, &chandef,
						IEEE80211_CHANCTX_SHARED);
	}
	return ret;
}