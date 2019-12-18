#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct minstrel_priv {int fixed_rate_idx; int* cck_rates; TYPE_2__* hw; } ;
struct minstrel_ht_sta {int max_tp_rate; int max_tp_rate2; int max_prob_rate; scalar_t__ sample_packets; int /*<<< orphan*/  total_packets; int /*<<< orphan*/  tx_flags; } ;
struct minstrel_ht_sta_priv {int /*<<< orphan*/  legacy; int /*<<< orphan*/  is_ht; struct minstrel_ht_sta ht; } ;
struct mcs_group {int streams; int flags; } ;
struct ieee80211_tx_rate_control {TYPE_4__* skb; int /*<<< orphan*/  short_preamble; } ;
struct ieee80211_tx_rate {int count; int idx; int flags; } ;
struct TYPE_5__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; TYPE_1__ status; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_8__ {scalar_t__ protocol; } ;
struct TYPE_7__ {void (* get_rate ) (void*,struct ieee80211_sta*,int /*<<< orphan*/ *,struct ieee80211_tx_rate_control*) ;} ;
struct TYPE_6__ {int max_rates; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (TYPE_4__*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_RC_MCS ; 
 int MCS_GROUP_RATES ; 
 int MINSTREL_CCK_GROUP ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 TYPE_3__ mac80211_minstrel ; 
 int minstrel_get_sample_rate (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_check_cck_shortpreamble (struct minstrel_priv*,struct minstrel_ht_sta*,int /*<<< orphan*/ ) ; 
 struct mcs_group* minstrel_mcs_groups ; 
 scalar_t__ rate_control_send_low (struct ieee80211_sta*,void*,struct ieee80211_tx_rate_control*) ; 
 void stub1 (void*,struct ieee80211_sta*,int /*<<< orphan*/ *,struct ieee80211_tx_rate_control*) ; 

__attribute__((used)) static void
minstrel_ht_get_rate(void *priv, struct ieee80211_sta *sta, void *priv_sta,
                     struct ieee80211_tx_rate_control *txrc)
{
	const struct mcs_group *sample_group;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	struct ieee80211_tx_rate *rate = &info->status.rates[0];
	struct minstrel_ht_sta_priv *msp = priv_sta;
	struct minstrel_ht_sta *mi = &msp->ht;
	struct minstrel_priv *mp = priv;
	int sample_idx;

	if (rate_control_send_low(sta, priv_sta, txrc))
		return;

	if (!msp->is_ht)
		return mac80211_minstrel.get_rate(priv, sta, &msp->legacy, txrc);

	info->flags |= mi->tx_flags;
	minstrel_ht_check_cck_shortpreamble(mp, mi, txrc->short_preamble);

	/* Don't use EAPOL frames for sampling on non-mrr hw */
	if (mp->hw->max_rates == 1 &&
	    txrc->skb->protocol == cpu_to_be16(ETH_P_PAE))
		sample_idx = -1;
	else
		sample_idx = minstrel_get_sample_rate(mp, mi);

#ifdef CONFIG_MAC80211_DEBUGFS
	/* use fixed index if set */
	if (mp->fixed_rate_idx != -1) {
		mi->max_tp_rate = mp->fixed_rate_idx;
		mi->max_tp_rate2 = mp->fixed_rate_idx;
		mi->max_prob_rate = mp->fixed_rate_idx;
		sample_idx = -1;
	}
#endif

	mi->total_packets++;

	/* wraparound */
	if (mi->total_packets == ~0) {
		mi->total_packets = 0;
		mi->sample_packets = 0;
	}

	if (sample_idx < 0)
		return;

	sample_group = &minstrel_mcs_groups[sample_idx / MCS_GROUP_RATES];
	info->flags |= IEEE80211_TX_CTL_RATE_CTRL_PROBE;
	rate->count = 1;

	if (sample_idx / MCS_GROUP_RATES == MINSTREL_CCK_GROUP) {
		int idx = sample_idx % ARRAY_SIZE(mp->cck_rates);
		rate->idx = mp->cck_rates[idx];
		rate->flags = 0;
		return;
	}

	rate->idx = sample_idx % MCS_GROUP_RATES +
		    (sample_group->streams - 1) * MCS_GROUP_RATES;
	rate->flags = IEEE80211_TX_RC_MCS | sample_group->flags;
}