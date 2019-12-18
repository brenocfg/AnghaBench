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
typedef  int u8 ;
typedef  int u16 ;
struct minstrel_rate_stats {scalar_t__ probability; int retry_count; int retry_count_rtscts; int /*<<< orphan*/  retry_updated; } ;
struct minstrel_priv {int* cck_rates; } ;
struct minstrel_ht_sta {int dummy; } ;
struct mcs_group {int streams; int flags; } ;
struct ieee80211_sta_rates {TYPE_1__* rate; } ;
struct TYPE_2__ {int count; int count_rts; int count_cts; int idx; int flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int MCS_GROUP_RATES ; 
 int MINSTREL_CCK_GROUP ; 
 scalar_t__ MINSTREL_FRAC (int,int) ; 
 int /*<<< orphan*/  minstrel_calc_retransmit (struct minstrel_priv*,struct minstrel_ht_sta*,int) ; 
 struct minstrel_rate_stats* minstrel_get_ratestats (struct minstrel_ht_sta*,int) ; 
 struct mcs_group* minstrel_mcs_groups ; 

__attribute__((used)) static void
minstrel_ht_set_rate(struct minstrel_priv *mp, struct minstrel_ht_sta *mi,
                     struct ieee80211_sta_rates *ratetbl, int offset, int index)
{
	const struct mcs_group *group = &minstrel_mcs_groups[index / MCS_GROUP_RATES];
	struct minstrel_rate_stats *mr;
	u8 idx;
	u16 flags;

	mr = minstrel_get_ratestats(mi, index);
	if (!mr->retry_updated)
		minstrel_calc_retransmit(mp, mi, index);

	if (mr->probability < MINSTREL_FRAC(20, 100) || !mr->retry_count) {
		ratetbl->rate[offset].count = 2;
		ratetbl->rate[offset].count_rts = 2;
		ratetbl->rate[offset].count_cts = 2;
	} else {
		ratetbl->rate[offset].count = mr->retry_count;
		ratetbl->rate[offset].count_cts = mr->retry_count;
		ratetbl->rate[offset].count_rts = mr->retry_count_rtscts;
	}

	if (index / MCS_GROUP_RATES == MINSTREL_CCK_GROUP) {
		idx = mp->cck_rates[index % ARRAY_SIZE(mp->cck_rates)];
		flags = 0;
	} else {
		idx = index % MCS_GROUP_RATES +
		      (group->streams - 1) * MCS_GROUP_RATES;
		flags = IEEE80211_TX_RC_MCS | group->flags;
	}

	if (offset > 0) {
		ratetbl->rate[offset].count = ratetbl->rate[offset].count_rts;
		flags |= IEEE80211_TX_RC_USE_RTS_CTS;
	}

	ratetbl->rate[offset].idx = idx;
	ratetbl->rate[offset].flags = flags;
}