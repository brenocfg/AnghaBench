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
struct ath_softc {int dummy; } ;
struct ath_rate_table {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 struct ath_rate_table const ar5416_11a_ratetable ; 
 struct ath_rate_table const ar5416_11g_ratetable ; 
 struct ath_rate_table const ar5416_11na_ratetable ; 
 struct ath_rate_table const ar5416_11ng_ratetable ; 

__attribute__((used)) static const
struct ath_rate_table *ath_choose_rate_table(struct ath_softc *sc,
					     enum ieee80211_band band,
					     bool is_ht)
{
	switch(band) {
	case IEEE80211_BAND_2GHZ:
		if (is_ht)
			return &ar5416_11ng_ratetable;
		return &ar5416_11g_ratetable;
	case IEEE80211_BAND_5GHZ:
		if (is_ht)
			return &ar5416_11na_ratetable;
		return &ar5416_11a_ratetable;
	default:
		return NULL;
	}
}