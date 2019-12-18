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
typedef  size_t u8 ;
typedef  int u32 ;
struct minstrel_sta_info {int n_rates; size_t max_prob_rate; int /*<<< orphan*/  stats_update; int /*<<< orphan*/  max_tp_rate; struct minstrel_rate* r; } ;
struct minstrel_rate {int perfect_tx_time; scalar_t__ attempts; int cur_prob; int success; int probability; int last_success; int last_attempts; int cur_tp; int adjusted_retry_count; int retry_count; int sample_limit; scalar_t__ sample_skipped; int /*<<< orphan*/  att_hist; int /*<<< orphan*/  succ_hist; } ;
struct minstrel_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EWMA_LEVEL ; 
 int MAX_THR_RATES ; 
 int MINSTREL_FRAC (int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,int) ; 
 int minstrel_ewma (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minstrel_sort_best_tp_rates (struct minstrel_sta_info*,int,size_t*) ; 
 int /*<<< orphan*/  minstrel_update_rates (struct minstrel_priv*,struct minstrel_sta_info*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
minstrel_update_stats(struct minstrel_priv *mp, struct minstrel_sta_info *mi)
{
	u8 tmp_tp_rate[MAX_THR_RATES];
	u8 tmp_prob_rate = 0;
	u32 usecs;
	int i;

	for (i=0; i < MAX_THR_RATES; i++)
	    tmp_tp_rate[i] = 0;

	for (i = 0; i < mi->n_rates; i++) {
		struct minstrel_rate *mr = &mi->r[i];

		usecs = mr->perfect_tx_time;
		if (!usecs)
			usecs = 1000000;

		if (unlikely(mr->attempts > 0)) {
			mr->sample_skipped = 0;
			mr->cur_prob = MINSTREL_FRAC(mr->success, mr->attempts);
			mr->succ_hist += mr->success;
			mr->att_hist += mr->attempts;
			mr->probability = minstrel_ewma(mr->probability,
							mr->cur_prob,
							EWMA_LEVEL);
		} else
			mr->sample_skipped++;

		mr->last_success = mr->success;
		mr->last_attempts = mr->attempts;
		mr->success = 0;
		mr->attempts = 0;

		/* Update throughput per rate, reset thr. below 10% success */
		if (mr->probability < MINSTREL_FRAC(10, 100))
			mr->cur_tp = 0;
		else
			mr->cur_tp = mr->probability * (1000000 / usecs);

		/* Sample less often below the 10% chance of success.
		 * Sample less often above the 95% chance of success. */
		if (mr->probability > MINSTREL_FRAC(95, 100) ||
		    mr->probability < MINSTREL_FRAC(10, 100)) {
			mr->adjusted_retry_count = mr->retry_count >> 1;
			if (mr->adjusted_retry_count > 2)
				mr->adjusted_retry_count = 2;
			mr->sample_limit = 4;
		} else {
			mr->sample_limit = -1;
			mr->adjusted_retry_count = mr->retry_count;
		}
		if (!mr->adjusted_retry_count)
			mr->adjusted_retry_count = 2;

		minstrel_sort_best_tp_rates(mi, i, tmp_tp_rate);

		/* To determine the most robust rate (max_prob_rate) used at
		 * 3rd mmr stage we distinct between two cases:
		 * (1) if any success probabilitiy >= 95%, out of those rates
		 * choose the maximum throughput rate as max_prob_rate
		 * (2) if all success probabilities < 95%, the rate with
		 * highest success probability is choosen as max_prob_rate */
		if (mr->probability >= MINSTREL_FRAC(95,100)) {
			if (mr->cur_tp >= mi->r[tmp_prob_rate].cur_tp)
				tmp_prob_rate = i;
		} else {
			if (mr->probability >= mi->r[tmp_prob_rate].probability)
				tmp_prob_rate = i;
		}
	}

	/* Assign the new rate set */
	memcpy(mi->max_tp_rate, tmp_tp_rate, sizeof(mi->max_tp_rate));
	mi->max_prob_rate = tmp_prob_rate;

	/* Reset update timer */
	mi->stats_update = jiffies;

	minstrel_update_rates(mp, mi);
}