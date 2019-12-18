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
typedef  int u32 ;
struct ieee80211_supported_band {int n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_rate {int flags; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
typedef  enum ieee80211_rate_flags { ____Placeholder_ieee80211_rate_flags } ieee80211_rate_flags ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_3__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_BAND_2GHZ ; 
 int IEEE80211_RATE_MANDATORY_A ; 
 int IEEE80211_RATE_MANDATORY_B ; 
 scalar_t__ WARN_ON (int) ; 

u32 ieee80211_mandatory_rates(struct ieee80211_local *local,
			      enum ieee80211_band band)
{
	struct ieee80211_supported_band *sband;
	struct ieee80211_rate *bitrates;
	u32 mandatory_rates;
	enum ieee80211_rate_flags mandatory_flag;
	int i;

	sband = local->hw.wiphy->bands[band];
	if (WARN_ON(!sband))
		return 1;

	if (band == IEEE80211_BAND_2GHZ)
		mandatory_flag = IEEE80211_RATE_MANDATORY_B;
	else
		mandatory_flag = IEEE80211_RATE_MANDATORY_A;

	bitrates = sband->bitrates;
	mandatory_rates = 0;
	for (i = 0; i < sband->n_bitrates; i++)
		if (bitrates[i].flags & mandatory_flag)
			mandatory_rates |= BIT(i);
	return mandatory_rates;
}