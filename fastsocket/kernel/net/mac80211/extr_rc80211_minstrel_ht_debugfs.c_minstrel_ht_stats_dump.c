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
struct minstrel_rate_stats {int cur_tp; int cur_prob; int probability; int retry_count; int last_success; int last_attempts; scalar_t__ att_hist; scalar_t__ succ_hist; } ;
struct minstrel_ht_sta {int max_tp_rate; int max_tp_rate2; int max_prob_rate; TYPE_1__* groups; } ;
struct mcs_group {int flags; int streams; } ;
struct TYPE_2__ {int supported; struct minstrel_rate_stats* rates; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 unsigned int MCS_GROUP_RATES ; 
 unsigned int MINSTREL_MAX_STREAMS ; 
 unsigned int MINSTREL_STREAM_GROUPS ; 
 unsigned int MINSTREL_TRUNC (int) ; 
 struct mcs_group* minstrel_mcs_groups ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,...) ; 

__attribute__((used)) static char *
minstrel_ht_stats_dump(struct minstrel_ht_sta *mi, int i, char *p)
{
	unsigned int max_mcs = MINSTREL_MAX_STREAMS * MINSTREL_STREAM_GROUPS;
	const struct mcs_group *mg;
	unsigned int j, tp, prob, eprob;
	char htmode = '2';
	char gimode = 'L';

	if (!mi->groups[i].supported)
		return p;

	mg = &minstrel_mcs_groups[i];
	if (mg->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		htmode = '4';
	if (mg->flags & IEEE80211_TX_RC_SHORT_GI)
		gimode = 'S';

	for (j = 0; j < MCS_GROUP_RATES; j++) {
		struct minstrel_rate_stats *mr = &mi->groups[i].rates[j];
		static const int bitrates[4] = { 10, 20, 55, 110 };
		int idx = i * MCS_GROUP_RATES + j;

		if (!(mi->groups[i].supported & BIT(j)))
			continue;

		if (i == max_mcs)
			p += sprintf(p, "CCK/%cP   ", j < 4 ? 'L' : 'S');
		else
			p += sprintf(p, "HT%c0/%cGI ", htmode, gimode);

		*(p++) = (idx == mi->max_tp_rate) ? 'T' : ' ';
		*(p++) = (idx == mi->max_tp_rate2) ? 't' : ' ';
		*(p++) = (idx == mi->max_prob_rate) ? 'P' : ' ';

		if (i == max_mcs) {
			int r = bitrates[j % 4];
			p += sprintf(p, " %2u.%1uM", r / 10, r % 10);
		} else {
			p += sprintf(p, " MCS%-2u", (mg->streams - 1) *
					 MCS_GROUP_RATES + j);
		}

		tp = mr->cur_tp / 10;
		prob = MINSTREL_TRUNC(mr->cur_prob * 1000);
		eprob = MINSTREL_TRUNC(mr->probability * 1000);

		p += sprintf(p, "      %6u.%1u   %6u.%1u    %6u.%1u    "
				"%3u            %3u(%3u)  %8llu    %8llu\n",
				tp / 10, tp % 10,
				eprob / 10, eprob % 10,
				prob / 10, prob % 10,
				mr->retry_count,
				mr->last_success,
				mr->last_attempts,
				(unsigned long long)mr->succ_hist,
				(unsigned long long)mr->att_hist);
	}

	return p;
}