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
typedef  int u16 ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int IEEE80211_BAND_2GHZ ; 

__attribute__((used)) static u16 iwl_mvm_get_active_dwell(enum ieee80211_band band, int n_ssids)
{
	if (band == IEEE80211_BAND_2GHZ)
		return 30  + 3 * (n_ssids + 1);
	return 20  + 2 * (n_ssids + 1);
}