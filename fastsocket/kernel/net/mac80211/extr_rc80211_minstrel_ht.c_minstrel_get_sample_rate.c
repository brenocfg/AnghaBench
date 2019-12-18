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
struct minstrel_rate_stats {scalar_t__ probability; int sample_skipped; } ;
struct minstrel_priv {int dummy; } ;
struct minstrel_mcs_group_data {size_t column; size_t index; struct minstrel_rate_stats* rates; } ;
struct minstrel_ht_sta {scalar_t__ sample_wait; size_t sample_group; int max_tp_rate; int max_tp_rate2; int max_prob_rate; scalar_t__ max_prob_streams; int /*<<< orphan*/  sample_tries; int /*<<< orphan*/  sample_slow; struct minstrel_mcs_group_data* groups; } ;
struct TYPE_2__ {scalar_t__ streams; } ;

/* Variables and functions */
 unsigned int MCS_GROUP_RATES ; 
 scalar_t__ MINSTREL_FRAC (int,int) ; 
 unsigned int minstrel_get_duration (int) ; 
 TYPE_1__* minstrel_mcs_groups ; 
 int /*<<< orphan*/  minstrel_next_sample_idx (struct minstrel_ht_sta*) ; 
 int** sample_table ; 

__attribute__((used)) static int
minstrel_get_sample_rate(struct minstrel_priv *mp, struct minstrel_ht_sta *mi)
{
	struct minstrel_rate_stats *mr;
	struct minstrel_mcs_group_data *mg;
	unsigned int sample_dur, sample_group;
	int sample_idx = 0;

	if (mi->sample_wait > 0) {
		mi->sample_wait--;
		return -1;
	}

	if (!mi->sample_tries)
		return -1;

	mg = &mi->groups[mi->sample_group];
	sample_idx = sample_table[mg->column][mg->index];
	mr = &mg->rates[sample_idx];
	sample_group = mi->sample_group;
	sample_idx += sample_group * MCS_GROUP_RATES;
	minstrel_next_sample_idx(mi);

	/*
	 * Sampling might add some overhead (RTS, no aggregation)
	 * to the frame. Hence, don't use sampling for the currently
	 * used rates.
	 */
	if (sample_idx == mi->max_tp_rate ||
	    sample_idx == mi->max_tp_rate2 ||
	    sample_idx == mi->max_prob_rate)
		return -1;

	/*
	 * Do not sample if the probability is already higher than 95%
	 * to avoid wasting airtime.
	 */
	if (mr->probability > MINSTREL_FRAC(95, 100))
		return -1;

	/*
	 * Make sure that lower rates get sampled only occasionally,
	 * if the link is working perfectly.
	 */
	sample_dur = minstrel_get_duration(sample_idx);
	if (sample_dur >= minstrel_get_duration(mi->max_tp_rate2) &&
	    (mi->max_prob_streams <
	     minstrel_mcs_groups[sample_group].streams ||
	     sample_dur >= minstrel_get_duration(mi->max_prob_rate))) {
		if (mr->sample_skipped < 20)
			return -1;

		if (mi->sample_slow++ > 2)
			return -1;
	}
	mi->sample_tries--;

	return sample_idx;
}