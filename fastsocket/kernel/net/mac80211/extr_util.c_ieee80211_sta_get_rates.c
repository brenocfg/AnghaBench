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
typedef  int u32 ;
struct ieee802_11_elems {int supp_rates_len; int ext_supp_rates_len; int* supp_rates; int* ext_supp_rates; } ;
struct ieee80211_supported_band {size_t n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_rate {int bitrate; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_3__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BSS_MEMBERSHIP_SELECTOR_HT_PHY ; 
 scalar_t__ WARN_ON (int) ; 

u32 ieee80211_sta_get_rates(struct ieee80211_local *local,
			    struct ieee802_11_elems *elems,
			    enum ieee80211_band band, u32 *basic_rates)
{
	struct ieee80211_supported_band *sband;
	struct ieee80211_rate *bitrates;
	size_t num_rates;
	u32 supp_rates;
	int i, j;
	sband = local->hw.wiphy->bands[band];

	if (WARN_ON(!sband))
		return 1;

	bitrates = sband->bitrates;
	num_rates = sband->n_bitrates;
	supp_rates = 0;
	for (i = 0; i < elems->supp_rates_len +
		     elems->ext_supp_rates_len; i++) {
		u8 rate = 0;
		int own_rate;
		bool is_basic;
		if (i < elems->supp_rates_len)
			rate = elems->supp_rates[i];
		else if (elems->ext_supp_rates)
			rate = elems->ext_supp_rates
				[i - elems->supp_rates_len];
		own_rate = 5 * (rate & 0x7f);
		is_basic = !!(rate & 0x80);

		if (is_basic && (rate & 0x7f) == BSS_MEMBERSHIP_SELECTOR_HT_PHY)
			continue;

		for (j = 0; j < num_rates; j++) {
			if (bitrates[j].bitrate == own_rate) {
				supp_rates |= BIT(j);
				if (basic_rates && is_basic)
					*basic_rates |= BIT(j);
			}
		}
	}
	return supp_rates;
}