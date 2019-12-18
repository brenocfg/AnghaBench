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
struct ieee80211_supported_band {int n_bitrates; int /*<<< orphan*/  band; struct ieee80211_rate* bitrates; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rate {int bitrate; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ rate_supported (struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline s8
rate_lowest_non_cck_index(struct ieee80211_supported_band *sband,
			  struct ieee80211_sta *sta)
{
	int i;

	for (i = 0; i < sband->n_bitrates; i++) {
		struct ieee80211_rate *srate = &sband->bitrates[i];
		if ((srate->bitrate == 10) || (srate->bitrate == 20) ||
		    (srate->bitrate == 55) || (srate->bitrate == 110))
			continue;

		if (rate_supported(sta, sband->band, i))
			return i;
	}

	/* No matching rate found */
	return 0;
}