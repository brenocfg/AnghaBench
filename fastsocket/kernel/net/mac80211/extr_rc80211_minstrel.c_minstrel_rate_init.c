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
struct minstrel_sta_info {size_t lowest_rix; unsigned int sp_ack_dur; unsigned int n_rates; int /*<<< orphan*/  stats_update; struct minstrel_rate* r; scalar_t__ max_prob_rate; struct minstrel_rate* max_tp_rate; struct ieee80211_sta* sta; } ;
struct minstrel_rate {unsigned int rix; int bitrate; int sample_limit; int retry_count; int retry_count_cts; int retry_count_rtscts; unsigned int perfect_tx_time; unsigned int ack_time; int adjusted_retry_count; } ;
struct minstrel_priv {unsigned int cw_min; unsigned int segment_size; int max_retry; int /*<<< orphan*/  cw_max; } ;
struct ieee80211_supported_band {unsigned int n_bitrates; struct ieee80211_rate* bitrates; int /*<<< orphan*/  band; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rate {int bitrate; int flags; } ;

/* Variables and functions */
 int IEEE80211_RATE_ERP_G ; 
 int /*<<< orphan*/  calc_rate_durations (int /*<<< orphan*/ ,struct minstrel_rate*,struct ieee80211_rate*) ; 
 unsigned int ieee80211_frame_duration (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  init_sample_table (struct minstrel_sta_info*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct minstrel_rate*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minstrel_update_rates (struct minstrel_priv*,struct minstrel_sta_info*) ; 
 size_t rate_lowest_index (struct ieee80211_supported_band*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  rate_supported (struct ieee80211_sta*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
minstrel_rate_init(void *priv, struct ieee80211_supported_band *sband,
               struct ieee80211_sta *sta, void *priv_sta)
{
	struct minstrel_sta_info *mi = priv_sta;
	struct minstrel_priv *mp = priv;
	struct ieee80211_rate *ctl_rate;
	unsigned int i, n = 0;
	unsigned int t_slot = 9; /* FIXME: get real slot time */

	mi->sta = sta;
	mi->lowest_rix = rate_lowest_index(sband, sta);
	ctl_rate = &sband->bitrates[mi->lowest_rix];
	mi->sp_ack_dur = ieee80211_frame_duration(sband->band, 10,
				ctl_rate->bitrate,
				!!(ctl_rate->flags & IEEE80211_RATE_ERP_G), 1);

	memset(mi->max_tp_rate, 0, sizeof(mi->max_tp_rate));
	mi->max_prob_rate = 0;

	for (i = 0; i < sband->n_bitrates; i++) {
		struct minstrel_rate *mr = &mi->r[n];
		unsigned int tx_time = 0, tx_time_cts = 0, tx_time_rtscts = 0;
		unsigned int tx_time_single;
		unsigned int cw = mp->cw_min;

		if (!rate_supported(sta, sband->band, i))
			continue;
		n++;
		memset(mr, 0, sizeof(*mr));

		mr->rix = i;
		mr->bitrate = sband->bitrates[i].bitrate / 5;
		calc_rate_durations(sband->band, mr, &sband->bitrates[i]);

		/* calculate maximum number of retransmissions before
		 * fallback (based on maximum segment size) */
		mr->sample_limit = -1;
		mr->retry_count = 1;
		mr->retry_count_cts = 1;
		mr->retry_count_rtscts = 1;
		tx_time = mr->perfect_tx_time + mi->sp_ack_dur;
		do {
			/* add one retransmission */
			tx_time_single = mr->ack_time + mr->perfect_tx_time;

			/* contention window */
			tx_time_single += (t_slot * cw) >> 1;
			cw = min((cw << 1) | 1, mp->cw_max);

			tx_time += tx_time_single;
			tx_time_cts += tx_time_single + mi->sp_ack_dur;
			tx_time_rtscts += tx_time_single + 2 * mi->sp_ack_dur;
			if ((tx_time_cts < mp->segment_size) &&
				(mr->retry_count_cts < mp->max_retry))
				mr->retry_count_cts++;
			if ((tx_time_rtscts < mp->segment_size) &&
				(mr->retry_count_rtscts < mp->max_retry))
				mr->retry_count_rtscts++;
		} while ((tx_time < mp->segment_size) &&
				(++mr->retry_count < mp->max_retry));
		mr->adjusted_retry_count = mr->retry_count;
		if (!(sband->bitrates[i].flags & IEEE80211_RATE_ERP_G))
			mr->retry_count_cts = mr->retry_count;
	}

	for (i = n; i < sband->n_bitrates; i++) {
		struct minstrel_rate *mr = &mi->r[i];
		mr->rix = -1;
	}

	mi->n_rates = n;
	mi->stats_update = jiffies;

	init_sample_table(mi);
	minstrel_update_rates(mp, mi);
}