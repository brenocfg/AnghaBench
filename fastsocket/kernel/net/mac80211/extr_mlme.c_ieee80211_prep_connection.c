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
typedef  void* u32 ;
struct TYPE_10__ {void** supp_rates; } ;
struct sta_info {TYPE_3__ sta; } ;
struct ieee80211_supported_band {int dummy; } ;
struct TYPE_13__ {int sync_dtim_count; int /*<<< orphan*/  sync_device_ts; int /*<<< orphan*/  sync_tsf; int /*<<< orphan*/  beacon_int; void* basic_rates; } ;
struct TYPE_14__ {TYPE_6__ bss_conf; } ;
struct ieee80211_if_managed {int /*<<< orphan*/  bssid; int /*<<< orphan*/  assoc_data; int /*<<< orphan*/  auth_data; } ;
struct TYPE_8__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_7__ vif; int /*<<< orphan*/  flags; TYPE_1__ u; struct ieee80211_local* local; } ;
struct TYPE_12__ {int flags; TYPE_2__* wiphy; } ;
struct ieee80211_local {TYPE_5__ hw; } ;
struct ieee80211_bss {int /*<<< orphan*/  device_ts_presp; int /*<<< orphan*/  device_ts_beacon; int /*<<< orphan*/  supp_rates_len; int /*<<< orphan*/  supp_rates; } ;
struct cfg80211_bss_ies {int /*<<< orphan*/  tsf; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct cfg80211_bss {int /*<<< orphan*/  bssid; int /*<<< orphan*/  proberesp_ies; int /*<<< orphan*/  beacon_ies; int /*<<< orphan*/  beacon_interval; TYPE_4__* channel; scalar_t__ priv; } ;
struct TYPE_11__ {size_t band; } ;
struct TYPE_9__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 void* BIT (int) ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IEEE80211_BAND_2GHZ ; 
 int IEEE80211_HW_TIMING_BEACON_ONLY ; 
 int /*<<< orphan*/  IEEE80211_SDATA_OPERATING_GMODE ; 
 int /*<<< orphan*/  IEEE80211_STA_AUTH ; 
 int INT_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WLAN_EID_TIM ; 
 int* cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_get_rates (struct ieee80211_supported_band*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,void**,int*,int*,int*) ; 
 int ieee80211_prep_channel (struct ieee80211_sub_if_data*,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfg80211_bss_ies* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,...) ; 
 struct sta_info* sta_info_alloc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_info_free (struct ieee80211_local*,struct sta_info*) ; 
 int sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int sta_info_insert (struct sta_info*) ; 
 int /*<<< orphan*/  sta_info_pre_move_state (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_prep_connection(struct ieee80211_sub_if_data *sdata,
				     struct cfg80211_bss *cbss, bool assoc)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_bss *bss = (void *)cbss->priv;
	struct sta_info *new_sta = NULL;
	bool have_sta = false;
	int err;

	if (WARN_ON(!ifmgd->auth_data && !ifmgd->assoc_data))
		return -EINVAL;

	if (assoc) {
		rcu_read_lock();
		have_sta = sta_info_get(sdata, cbss->bssid);
		rcu_read_unlock();
	}

	if (!have_sta) {
		new_sta = sta_info_alloc(sdata, cbss->bssid, GFP_KERNEL);
		if (!new_sta)
			return -ENOMEM;
	}

	if (new_sta) {
		u32 rates = 0, basic_rates = 0;
		bool have_higher_than_11mbit;
		int min_rate = INT_MAX, min_rate_index = -1;
		struct ieee80211_supported_band *sband;
		const struct cfg80211_bss_ies *ies;

		sband = local->hw.wiphy->bands[cbss->channel->band];

		err = ieee80211_prep_channel(sdata, cbss);
		if (err) {
			sta_info_free(local, new_sta);
			return err;
		}

		ieee80211_get_rates(sband, bss->supp_rates,
				    bss->supp_rates_len,
				    &rates, &basic_rates,
				    &have_higher_than_11mbit,
				    &min_rate, &min_rate_index);

		/*
		 * This used to be a workaround for basic rates missing
		 * in the association response frame. Now that we no
		 * longer use the basic rates from there, it probably
		 * doesn't happen any more, but keep the workaround so
		 * in case some *other* APs are buggy in different ways
		 * we can connect -- with a warning.
		 */
		if (!basic_rates && min_rate_index >= 0) {
			sdata_info(sdata,
				   "No basic rates, using min rate instead\n");
			basic_rates = BIT(min_rate_index);
		}

		new_sta->sta.supp_rates[cbss->channel->band] = rates;
		sdata->vif.bss_conf.basic_rates = basic_rates;

		/* cf. IEEE 802.11 9.2.12 */
		if (cbss->channel->band == IEEE80211_BAND_2GHZ &&
		    have_higher_than_11mbit)
			sdata->flags |= IEEE80211_SDATA_OPERATING_GMODE;
		else
			sdata->flags &= ~IEEE80211_SDATA_OPERATING_GMODE;

		memcpy(ifmgd->bssid, cbss->bssid, ETH_ALEN);

		/* set timing information */
		sdata->vif.bss_conf.beacon_int = cbss->beacon_interval;
		rcu_read_lock();
		ies = rcu_dereference(cbss->beacon_ies);
		if (ies) {
			const u8 *tim_ie;

			sdata->vif.bss_conf.sync_tsf = ies->tsf;
			sdata->vif.bss_conf.sync_device_ts =
				bss->device_ts_beacon;
			tim_ie = cfg80211_find_ie(WLAN_EID_TIM,
						  ies->data, ies->len);
			if (tim_ie && tim_ie[1] >= 2)
				sdata->vif.bss_conf.sync_dtim_count = tim_ie[2];
			else
				sdata->vif.bss_conf.sync_dtim_count = 0;
		} else if (!(local->hw.flags &
					IEEE80211_HW_TIMING_BEACON_ONLY)) {
			ies = rcu_dereference(cbss->proberesp_ies);
			/* must be non-NULL since beacon IEs were NULL */
			sdata->vif.bss_conf.sync_tsf = ies->tsf;
			sdata->vif.bss_conf.sync_device_ts =
				bss->device_ts_presp;
			sdata->vif.bss_conf.sync_dtim_count = 0;
		} else {
			sdata->vif.bss_conf.sync_tsf = 0;
			sdata->vif.bss_conf.sync_device_ts = 0;
			sdata->vif.bss_conf.sync_dtim_count = 0;
		}
		rcu_read_unlock();

		/* tell driver about BSSID, basic rates and timing */
		ieee80211_bss_info_change_notify(sdata,
			BSS_CHANGED_BSSID | BSS_CHANGED_BASIC_RATES |
			BSS_CHANGED_BEACON_INT);

		if (assoc)
			sta_info_pre_move_state(new_sta, IEEE80211_STA_AUTH);

		err = sta_info_insert(new_sta);
		new_sta = NULL;
		if (err) {
			sdata_info(sdata,
				   "failed to insert STA entry for the AP (error %d)\n",
				   err);
			return err;
		}
	} else
		WARN_ON_ONCE(!ether_addr_equal(ifmgd->bssid, cbss->bssid));

	return 0;
}