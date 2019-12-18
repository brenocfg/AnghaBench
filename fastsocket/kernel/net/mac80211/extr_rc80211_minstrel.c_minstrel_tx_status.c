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
struct minstrel_sta_info {scalar_t__ sample_deferred; scalar_t__ stats_update; int /*<<< orphan*/  sample_count; TYPE_2__* r; } ;
struct minstrel_priv {int update_interval; } ;
struct ieee80211_tx_rate {scalar_t__ idx; scalar_t__ count; } ;
struct TYPE_3__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ status; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_4__ {int success; int /*<<< orphan*/  attempts; } ;

/* Variables and functions */
 int HZ ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_MAX_RATES ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  minstrel_update_stats (struct minstrel_priv*,struct minstrel_sta_info*) ; 
 int rix_to_ndx (struct minstrel_sta_info*,scalar_t__) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
minstrel_tx_status(void *priv, struct ieee80211_supported_band *sband,
                   struct ieee80211_sta *sta, void *priv_sta,
		   struct sk_buff *skb)
{
	struct minstrel_priv *mp = priv;
	struct minstrel_sta_info *mi = priv_sta;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *ar = info->status.rates;
	int i, ndx;
	int success;

	success = !!(info->flags & IEEE80211_TX_STAT_ACK);

	for (i = 0; i < IEEE80211_TX_MAX_RATES; i++) {
		if (ar[i].idx < 0)
			break;

		ndx = rix_to_ndx(mi, ar[i].idx);
		if (ndx < 0)
			continue;

		mi->r[ndx].attempts += ar[i].count;

		if ((i != IEEE80211_TX_MAX_RATES - 1) && (ar[i + 1].idx < 0))
			mi->r[ndx].success += success;
	}

	if ((info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE) && (i >= 0))
		mi->sample_count++;

	if (mi->sample_deferred > 0)
		mi->sample_deferred--;

	if (time_after(jiffies, mi->stats_update +
				(mp->update_interval * HZ) / 1000))
		minstrel_update_stats(mp, mi);
}