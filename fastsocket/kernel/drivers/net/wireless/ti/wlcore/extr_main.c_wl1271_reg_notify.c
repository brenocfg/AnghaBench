#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wl1271 {int dummy; } ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct regulatory_request {int dummy; } ;
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct ieee80211_channel {int flags; } ;

/* Variables and functions */
 size_t IEEE80211_BAND_5GHZ ; 
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_IBSS ; 
 int IEEE80211_CHAN_PASSIVE_SCAN ; 
 int IEEE80211_CHAN_RADAR ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 
 int /*<<< orphan*/  wlcore_regdomain_config (struct wl1271*) ; 

__attribute__((used)) static void wl1271_reg_notify(struct wiphy *wiphy,
			      struct regulatory_request *request)
{
	struct ieee80211_supported_band *band;
	struct ieee80211_channel *ch;
	int i;
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct wl1271 *wl = hw->priv;

	band = wiphy->bands[IEEE80211_BAND_5GHZ];
	for (i = 0; i < band->n_channels; i++) {
		ch = &band->channels[i];
		if (ch->flags & IEEE80211_CHAN_DISABLED)
			continue;

		if (ch->flags & IEEE80211_CHAN_RADAR)
			ch->flags |= IEEE80211_CHAN_NO_IBSS |
				     IEEE80211_CHAN_PASSIVE_SCAN;

	}

	wlcore_regdomain_config(wl);
}