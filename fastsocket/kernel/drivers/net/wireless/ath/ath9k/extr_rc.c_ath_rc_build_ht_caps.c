#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {scalar_t__* rx_mask; } ;
struct TYPE_4__ {int cap; TYPE_1__ mcs; scalar_t__ ht_supported; } ;
struct ieee80211_sta {scalar_t__ bandwidth; TYPE_2__ ht_cap; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 
 int WLAN_RC_40_FLAG ; 
 int WLAN_RC_DS_FLAG ; 
 int WLAN_RC_HT_FLAG ; 
 int WLAN_RC_SGI_FLAG ; 
 int WLAN_RC_TS_FLAG ; 

__attribute__((used)) static u8 ath_rc_build_ht_caps(struct ath_softc *sc, struct ieee80211_sta *sta)
{
	u8 caps = 0;

	if (sta->ht_cap.ht_supported) {
		caps = WLAN_RC_HT_FLAG;
		if (sta->ht_cap.mcs.rx_mask[1] && sta->ht_cap.mcs.rx_mask[2])
			caps |= WLAN_RC_TS_FLAG | WLAN_RC_DS_FLAG;
		else if (sta->ht_cap.mcs.rx_mask[1])
			caps |= WLAN_RC_DS_FLAG;
		if (sta->bandwidth >= IEEE80211_STA_RX_BW_40) {
			caps |= WLAN_RC_40_FLAG;
			if (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
				caps |= WLAN_RC_SGI_FLAG;
		} else {
			if (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20)
				caps |= WLAN_RC_SGI_FLAG;
		}
	}

	return caps;
}