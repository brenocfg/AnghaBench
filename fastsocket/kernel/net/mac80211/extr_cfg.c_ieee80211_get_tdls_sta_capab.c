#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_2__ {int flags; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int IEEE80211_HW_2GHZ_SHORT_PREAMBLE_INCAPABLE ; 
 int IEEE80211_HW_2GHZ_SHORT_SLOT_INCAPABLE ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_SHORT_SLOT_TIME ; 
 scalar_t__ ieee80211_get_sdata_band (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static u16 ieee80211_get_tdls_sta_capab(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	u16 capab;

	capab = 0;
	if (ieee80211_get_sdata_band(sdata) != IEEE80211_BAND_2GHZ)
		return capab;

	if (!(local->hw.flags & IEEE80211_HW_2GHZ_SHORT_SLOT_INCAPABLE))
		capab |= WLAN_CAPABILITY_SHORT_SLOT_TIME;
	if (!(local->hw.flags & IEEE80211_HW_2GHZ_SHORT_PREAMBLE_INCAPABLE))
		capab |= WLAN_CAPABILITY_SHORT_PREAMBLE;

	return capab;
}