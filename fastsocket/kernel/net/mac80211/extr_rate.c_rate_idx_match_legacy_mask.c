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
typedef  int u32 ;
struct ieee80211_tx_rate {int idx; } ;

/* Variables and functions */

__attribute__((used)) static bool rate_idx_match_legacy_mask(struct ieee80211_tx_rate *rate,
				       int n_bitrates, u32 mask)
{
	int j;

	/* See whether the selected rate or anything below it is allowed. */
	for (j = rate->idx; j >= 0; j--) {
		if (mask & (1 << j)) {
			/* Okay, found a suitable rate. Use it. */
			rate->idx = j;
			return true;
		}
	}

	/* Try to find a higher rate that would be allowed */
	for (j = rate->idx + 1; j < n_bitrates; j++) {
		if (mask & (1 << j)) {
			/* Okay, found a suitable rate. Use it. */
			rate->idx = j;
			return true;
		}
	}
	return false;
}