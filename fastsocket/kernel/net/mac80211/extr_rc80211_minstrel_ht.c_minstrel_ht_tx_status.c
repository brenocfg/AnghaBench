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
struct sk_buff {int dummy; } ;
struct minstrel_rate_stats {int success; int attempts; } ;
struct minstrel_priv {int update_interval; } ;
struct minstrel_ht_sta {int ampdu_len; int sample_wait; int sample_tries; scalar_t__ sample_count; int sample_packets; int max_prob_rate; scalar_t__ stats_update; int /*<<< orphan*/  max_tp_rate2; int /*<<< orphan*/  max_tp_rate; int /*<<< orphan*/  avg_ampdu_len; int /*<<< orphan*/  ampdu_packets; } ;
struct minstrel_ht_sta_priv {int /*<<< orphan*/  legacy; int /*<<< orphan*/  is_ht; struct minstrel_ht_sta ht; } ;
struct ieee80211_tx_rate {int count; } ;
struct TYPE_3__ {int ampdu_ack_len; int ampdu_len; struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ status; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_4__ {void (* tx_status ) (void*,struct ieee80211_supported_band*,struct ieee80211_sta*,int /*<<< orphan*/ *,struct sk_buff*) ;} ;

/* Variables and functions */
 int HZ ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_MAX_RATES ; 
 int IEEE80211_TX_STAT_ACK ; 
 int IEEE80211_TX_STAT_AMPDU ; 
 int MCS_GROUP_RATES ; 
 int MINSTREL_CCK_GROUP ; 
 scalar_t__ MINSTREL_FRAC (int,int) ; 
 int MINSTREL_TRUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_2__ mac80211_minstrel ; 
 int /*<<< orphan*/  minstrel_aggr_check (struct ieee80211_sta*,struct sk_buff*) ; 
 int /*<<< orphan*/  minstrel_downgrade_rate (struct minstrel_ht_sta*,int /*<<< orphan*/ *,int) ; 
 struct minstrel_rate_stats* minstrel_get_ratestats (struct minstrel_ht_sta*,int /*<<< orphan*/ ) ; 
 struct minstrel_rate_stats* minstrel_ht_get_stats (struct minstrel_priv*,struct minstrel_ht_sta*,struct ieee80211_tx_rate*) ; 
 int /*<<< orphan*/  minstrel_ht_txstat_valid (struct minstrel_priv*,struct ieee80211_tx_rate*) ; 
 int /*<<< orphan*/  minstrel_ht_update_rates (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_update_stats (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 void stub1 (void*,struct ieee80211_supported_band*,struct ieee80211_sta*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
minstrel_ht_tx_status(void *priv, struct ieee80211_supported_band *sband,
                      struct ieee80211_sta *sta, void *priv_sta,
                      struct sk_buff *skb)
{
	struct minstrel_ht_sta_priv *msp = priv_sta;
	struct minstrel_ht_sta *mi = &msp->ht;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *ar = info->status.rates;
	struct minstrel_rate_stats *rate, *rate2;
	struct minstrel_priv *mp = priv;
	bool last, update = false;
	int i;

	if (!msp->is_ht)
		return mac80211_minstrel.tx_status(priv, sband, sta, &msp->legacy, skb);

	/* This packet was aggregated but doesn't carry status info */
	if ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(info->flags & IEEE80211_TX_STAT_AMPDU))
		return;

	if (!(info->flags & IEEE80211_TX_STAT_AMPDU)) {
		info->status.ampdu_ack_len =
			(info->flags & IEEE80211_TX_STAT_ACK ? 1 : 0);
		info->status.ampdu_len = 1;
	}

	mi->ampdu_packets++;
	mi->ampdu_len += info->status.ampdu_len;

	if (!mi->sample_wait && !mi->sample_tries && mi->sample_count > 0) {
		mi->sample_wait = 16 + 2 * MINSTREL_TRUNC(mi->avg_ampdu_len);
		mi->sample_tries = 1;
		mi->sample_count--;
	}

	if (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)
		mi->sample_packets += info->status.ampdu_len;

	last = !minstrel_ht_txstat_valid(mp, &ar[0]);
	for (i = 0; !last; i++) {
		last = (i == IEEE80211_TX_MAX_RATES - 1) ||
		       !minstrel_ht_txstat_valid(mp, &ar[i + 1]);

		rate = minstrel_ht_get_stats(mp, mi, &ar[i]);

		if (last)
			rate->success += info->status.ampdu_ack_len;

		rate->attempts += ar[i].count * info->status.ampdu_len;
	}

	/*
	 * check for sudden death of spatial multiplexing,
	 * downgrade to a lower number of streams if necessary.
	 */
	rate = minstrel_get_ratestats(mi, mi->max_tp_rate);
	if (rate->attempts > 30 &&
	    MINSTREL_FRAC(rate->success, rate->attempts) <
	    MINSTREL_FRAC(20, 100)) {
		minstrel_downgrade_rate(mi, &mi->max_tp_rate, true);
		update = true;
	}

	rate2 = minstrel_get_ratestats(mi, mi->max_tp_rate2);
	if (rate2->attempts > 30 &&
	    MINSTREL_FRAC(rate2->success, rate2->attempts) <
	    MINSTREL_FRAC(20, 100)) {
		minstrel_downgrade_rate(mi, &mi->max_tp_rate2, false);
		update = true;
	}

	if (time_after(jiffies, mi->stats_update + (mp->update_interval / 2 * HZ) / 1000)) {
		update = true;
		minstrel_ht_update_stats(mp, mi);
		if (!(info->flags & IEEE80211_TX_CTL_AMPDU) &&
		    mi->max_prob_rate / MCS_GROUP_RATES != MINSTREL_CCK_GROUP)
			minstrel_aggr_check(sta, skb);
	}

	if (update)
		minstrel_ht_update_rates(mp, mi);
}