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
struct minstrel_rate_stats {unsigned int probability; int cur_tp; } ;
struct minstrel_ht_sta {int overhead; unsigned int avg_ampdu_len; TYPE_1__* groups; } ;
struct TYPE_4__ {scalar_t__* duration; } ;
struct TYPE_3__ {struct minstrel_rate_stats* rates; } ;

/* Variables and functions */
 int MINSTREL_CCK_GROUP ; 
 unsigned int MINSTREL_FRAC (int,int) ; 
 int MINSTREL_TRUNC (unsigned int) ; 
 TYPE_2__* minstrel_mcs_groups ; 

__attribute__((used)) static void
minstrel_ht_calc_tp(struct minstrel_ht_sta *mi, int group, int rate)
{
	struct minstrel_rate_stats *mr;
	unsigned int nsecs = 0;
	unsigned int tp;
	unsigned int prob;

	mr = &mi->groups[group].rates[rate];
	prob = mr->probability;

	if (prob < MINSTREL_FRAC(1, 10)) {
		mr->cur_tp = 0;
		return;
	}

	/*
	 * For the throughput calculation, limit the probability value to 90% to
	 * account for collision related packet error rate fluctuation
	 */
	if (prob > MINSTREL_FRAC(9, 10))
		prob = MINSTREL_FRAC(9, 10);

	if (group != MINSTREL_CCK_GROUP)
		nsecs = 1000 * mi->overhead / MINSTREL_TRUNC(mi->avg_ampdu_len);

	nsecs += minstrel_mcs_groups[group].duration[rate];
	tp = 1000000 * ((mr->probability * 1000) / nsecs);

	mr->cur_tp = MINSTREL_TRUNC(tp);
}