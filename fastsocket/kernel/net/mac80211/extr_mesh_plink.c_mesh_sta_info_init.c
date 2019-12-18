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
typedef  scalar_t__ u32 ;
struct TYPE_8__ {scalar_t__* supp_rates; scalar_t__ bandwidth; } ;
struct sta_info {scalar_t__ plink_state; int /*<<< orphan*/  lock; TYPE_4__ sta; int /*<<< orphan*/  last_rx; } ;
struct ieee802_11_elems {TYPE_3__* ht_operation; int /*<<< orphan*/  ht_cap_elem; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_6__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_7__ {int ht_param; } ;
struct TYPE_5__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int IEEE80211_HT_PARAM_CHAN_WIDTH_ANY ; 
 scalar_t__ IEEE80211_RC_BW_CHANGED ; 
 scalar_t__ IEEE80211_RC_SUPP_RATES_CHANGED ; 
 scalar_t__ IEEE80211_STA_RX_BW_20 ; 
 scalar_t__ NL80211_PLINK_ESTAB ; 
 int ieee80211_get_sdata_band (struct ieee80211_sub_if_data*) ; 
 scalar_t__ ieee80211_ht_cap_ie_to_sta_ht_cap (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,int /*<<< orphan*/ ,struct sta_info*) ; 
 scalar_t__ ieee80211_sta_get_rates (struct ieee80211_local*,struct ieee802_11_elems*,int,scalar_t__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rate_control_rate_init (struct sta_info*) ; 
 int /*<<< orphan*/  rate_control_rate_update (struct ieee80211_local*,struct ieee80211_supported_band*,struct sta_info*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mesh_sta_info_init(struct ieee80211_sub_if_data *sdata,
			       struct sta_info *sta,
			       struct ieee802_11_elems *elems, bool insert)
{
	struct ieee80211_local *local = sdata->local;
	enum ieee80211_band band = ieee80211_get_sdata_band(sdata);
	struct ieee80211_supported_band *sband;
	u32 rates, basic_rates = 0, changed = 0;

	sband = local->hw.wiphy->bands[band];
	rates = ieee80211_sta_get_rates(local, elems, band, &basic_rates);

	spin_lock_bh(&sta->lock);
	sta->last_rx = jiffies;

	/* rates and capabilities don't change during peering */
	if (sta->plink_state == NL80211_PLINK_ESTAB)
		goto out;

	if (sta->sta.supp_rates[band] != rates)
		changed |= IEEE80211_RC_SUPP_RATES_CHANGED;
	sta->sta.supp_rates[band] = rates;

	if (ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
					      elems->ht_cap_elem, sta))
		changed |= IEEE80211_RC_BW_CHANGED;

	/* HT peer is operating 20MHz-only */
	if (elems->ht_operation &&
	    !(elems->ht_operation->ht_param &
	      IEEE80211_HT_PARAM_CHAN_WIDTH_ANY)) {
		if (sta->sta.bandwidth != IEEE80211_STA_RX_BW_20)
			changed |= IEEE80211_RC_BW_CHANGED;
		sta->sta.bandwidth = IEEE80211_STA_RX_BW_20;
	}

	if (insert)
		rate_control_rate_init(sta);
	else
		rate_control_rate_update(local, sband, sta, changed);
out:
	spin_unlock_bh(&sta->lock);
}