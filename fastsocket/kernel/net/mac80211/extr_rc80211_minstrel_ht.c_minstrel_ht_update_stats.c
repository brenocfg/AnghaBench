#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct minstrel_rate_stats {int retry_updated; int cur_tp; int probability; int cur_prob; } ;
struct minstrel_priv {int dummy; } ;
struct minstrel_mcs_group_data {int supported; int max_tp_rate; int max_tp_rate2; int max_prob_rate; struct minstrel_rate_stats* rates; } ;
struct minstrel_ht_sta {scalar_t__ ampdu_packets; int ampdu_len; int sample_count; int max_tp_rate; int max_tp_rate2; int max_prob_rate; int max_prob_streams; int /*<<< orphan*/  stats_update; struct minstrel_mcs_group_data* groups; scalar_t__ sample_slow; int /*<<< orphan*/  avg_ampdu_len; } ;
struct TYPE_3__ {int streams; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  EWMA_LEVEL ; 
 int MCS_GROUP_RATES ; 
 int MINSTREL_FRAC (int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  minstrel_calc_rate_ewma (struct minstrel_rate_stats*) ; 
 int /*<<< orphan*/  minstrel_ewma (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct minstrel_rate_stats* minstrel_get_ratestats (struct minstrel_ht_sta*,int) ; 
 int /*<<< orphan*/  minstrel_ht_calc_tp (struct minstrel_ht_sta*,int,int) ; 
 TYPE_1__* minstrel_mcs_groups ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void
minstrel_ht_update_stats(struct minstrel_priv *mp, struct minstrel_ht_sta *mi)
{
	struct minstrel_mcs_group_data *mg;
	struct minstrel_rate_stats *mr;
	int cur_prob, cur_prob_tp, cur_tp, cur_tp2;
	int group, i, index;
	bool mi_rates_valid = false;

	if (mi->ampdu_packets > 0) {
		mi->avg_ampdu_len = minstrel_ewma(mi->avg_ampdu_len,
			MINSTREL_FRAC(mi->ampdu_len, mi->ampdu_packets), EWMA_LEVEL);
		mi->ampdu_len = 0;
		mi->ampdu_packets = 0;
	}

	mi->sample_slow = 0;
	mi->sample_count = 0;

	for (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) {
		bool mg_rates_valid = false;

		cur_prob = 0;
		cur_prob_tp = 0;
		cur_tp = 0;
		cur_tp2 = 0;

		mg = &mi->groups[group];
		if (!mg->supported)
			continue;

		mi->sample_count++;

		for (i = 0; i < MCS_GROUP_RATES; i++) {
			if (!(mg->supported & BIT(i)))
				continue;

			/* initialize rates selections starting indexes */
			if (!mg_rates_valid) {
				mg->max_tp_rate = mg->max_tp_rate2 =
					mg->max_prob_rate = i;
				if (!mi_rates_valid) {
					mi->max_tp_rate = mi->max_tp_rate2 =
						mi->max_prob_rate = i;
					mi_rates_valid = true;
				}
				mg_rates_valid = true;
			}

			mr = &mg->rates[i];
			mr->retry_updated = false;
			index = MCS_GROUP_RATES * group + i;
			minstrel_calc_rate_ewma(mr);
			minstrel_ht_calc_tp(mi, group, i);

			if (!mr->cur_tp)
				continue;

			if ((mr->cur_tp > cur_prob_tp && mr->probability >
			     MINSTREL_FRAC(3, 4)) || mr->probability > cur_prob) {
				mg->max_prob_rate = index;
				cur_prob = mr->probability;
				cur_prob_tp = mr->cur_tp;
			}

			if (mr->cur_tp > cur_tp) {
				swap(index, mg->max_tp_rate);
				cur_tp = mr->cur_tp;
				mr = minstrel_get_ratestats(mi, index);
			}

			if (index >= mg->max_tp_rate)
				continue;

			if (mr->cur_tp > cur_tp2) {
				mg->max_tp_rate2 = index;
				cur_tp2 = mr->cur_tp;
			}
		}
	}

	/* try to sample all available rates during each interval */
	mi->sample_count *= 8;

	cur_prob = 0;
	cur_prob_tp = 0;
	cur_tp = 0;
	cur_tp2 = 0;
	for (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) {
		mg = &mi->groups[group];
		if (!mg->supported)
			continue;

		mr = minstrel_get_ratestats(mi, mg->max_tp_rate);
		if (cur_tp < mr->cur_tp) {
			mi->max_tp_rate2 = mi->max_tp_rate;
			cur_tp2 = cur_tp;
			mi->max_tp_rate = mg->max_tp_rate;
			cur_tp = mr->cur_tp;
			mi->max_prob_streams = minstrel_mcs_groups[group].streams - 1;
		}

		mr = minstrel_get_ratestats(mi, mg->max_tp_rate2);
		if (cur_tp2 < mr->cur_tp) {
			mi->max_tp_rate2 = mg->max_tp_rate2;
			cur_tp2 = mr->cur_tp;
		}
	}

	if (mi->max_prob_streams < 1)
		mi->max_prob_streams = 1;

	for (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) {
		mg = &mi->groups[group];
		if (!mg->supported)
			continue;
		mr = minstrel_get_ratestats(mi, mg->max_prob_rate);
		if (cur_prob_tp < mr->cur_tp &&
		    minstrel_mcs_groups[group].streams <= mi->max_prob_streams) {
			mi->max_prob_rate = mg->max_prob_rate;
			cur_prob = mr->cur_prob;
			cur_prob_tp = mr->cur_tp;
		}
	}


	mi->stats_update = jiffies;
}