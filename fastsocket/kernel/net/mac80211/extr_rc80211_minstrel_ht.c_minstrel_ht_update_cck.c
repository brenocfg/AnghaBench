#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct minstrel_priv {int /*<<< orphan*/ * cck_rates; TYPE_1__* hw; } ;
struct minstrel_ht_sta {int /*<<< orphan*/  cck_supported; TYPE_3__* groups; int /*<<< orphan*/  cck_supported_short; } ;
struct ieee80211_supported_band {scalar_t__ band; TYPE_2__* bitrates; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  supported; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int IEEE80211_HW_SUPPORTS_HT_CCK_RATES ; 
 int IEEE80211_RATE_SHORT_PREAMBLE ; 
 size_t MINSTREL_CCK_GROUP ; 
 int /*<<< orphan*/  rate_supported (struct ieee80211_sta*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
minstrel_ht_update_cck(struct minstrel_priv *mp, struct minstrel_ht_sta *mi,
		       struct ieee80211_supported_band *sband,
		       struct ieee80211_sta *sta)
{
	int i;

	if (sband->band != IEEE80211_BAND_2GHZ)
		return;

	if (!(mp->hw->flags & IEEE80211_HW_SUPPORTS_HT_CCK_RATES))
		return;

	mi->cck_supported = 0;
	mi->cck_supported_short = 0;
	for (i = 0; i < 4; i++) {
		if (!rate_supported(sta, sband->band, mp->cck_rates[i]))
			continue;

		mi->cck_supported |= BIT(i);
		if (sband->bitrates[i].flags & IEEE80211_RATE_SHORT_PREAMBLE)
			mi->cck_supported_short |= BIT(i);
	}

	mi->groups[MINSTREL_CCK_GROUP].supported = mi->cck_supported;
}