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
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 int /*<<< orphan*/  wl1271_error (char*,int) ; 

__attribute__((used)) static int wlcore_get_reg_conf_ch_idx(enum ieee80211_band band, u16 ch)
{
	int idx = -1;

	switch (band) {
	case IEEE80211_BAND_5GHZ:
		if (ch >= 8 && ch <= 16)
			idx = ((ch-8)/4 + 18);
		else if (ch >= 34 && ch <= 64)
			idx = ((ch-34)/2 + 3 + 18);
		else if (ch >= 100 && ch <= 140)
			idx = ((ch-100)/4 + 15 + 18);
		else if (ch >= 149 && ch <= 165)
			idx = ((ch-149)/4 + 26 + 18);
		else
			idx = -1;
		break;
	case IEEE80211_BAND_2GHZ:
		if (ch >= 1 && ch <= 14)
			idx = ch - 1;
		else
			idx = -1;
		break;
	default:
		wl1271_error("get reg conf ch idx - unknown band: %d",
			     (int)band);
	}

	return idx;
}