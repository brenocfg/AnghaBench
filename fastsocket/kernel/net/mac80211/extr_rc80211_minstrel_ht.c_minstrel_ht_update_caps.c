#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct minstrel_priv {scalar_t__ has_mrr; } ;
struct minstrel_ht_sta {int overhead; int overhead_rtscts; int sample_count; int sample_wait; int sample_tries; int tx_flags; int /*<<< orphan*/  sample_table; int /*<<< orphan*/  r; TYPE_2__* groups; int /*<<< orphan*/  avg_ampdu_len; int /*<<< orphan*/  stats_update; struct ieee80211_sta* sta; } ;
struct minstrel_ht_sta_priv {int is_ht; struct minstrel_ht_sta legacy; int /*<<< orphan*/  sample_table; int /*<<< orphan*/  ratelist; struct minstrel_ht_sta ht; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  band; } ;
struct ieee80211_mcs_info {scalar_t__* rx_mask; } ;
struct TYPE_5__ {int cap; int /*<<< orphan*/  ht_supported; struct ieee80211_mcs_info mcs; } ;
struct ieee80211_sta {scalar_t__ bandwidth; scalar_t__ smps_mode; TYPE_1__ ht_cap; } ;
struct TYPE_7__ {void (* rate_init ) (void*,struct ieee80211_supported_band*,struct ieee80211_sta*,struct minstrel_ht_sta*) ;} ;
struct TYPE_6__ {int flags; int streams; scalar_t__ supported; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 scalar_t__ IEEE80211_SMPS_STATIC ; 
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 
 int IEEE80211_TX_CTL_LDPC ; 
 int IEEE80211_TX_CTL_STBC_SHIFT ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int MINSTREL_CCK_GROUP ; 
 int /*<<< orphan*/  MINSTREL_FRAC (int,int) ; 
 int MINSTREL_MAX_STREAMS ; 
 int MINSTREL_STREAM_GROUPS ; 
 int ieee80211_frame_duration (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_3__ mac80211_minstrel ; 
 int /*<<< orphan*/  memset (struct minstrel_ht_sta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  minstrel_ht_update_cck (struct minstrel_priv*,struct minstrel_ht_sta*,struct ieee80211_supported_band*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_update_rates (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_update_stats (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 TYPE_2__* minstrel_mcs_groups ; 
 void stub1 (void*,struct ieee80211_supported_band*,struct ieee80211_sta*,struct minstrel_ht_sta*) ; 

__attribute__((used)) static void
minstrel_ht_update_caps(void *priv, struct ieee80211_supported_band *sband,
                        struct ieee80211_sta *sta, void *priv_sta)
{
	struct minstrel_priv *mp = priv;
	struct minstrel_ht_sta_priv *msp = priv_sta;
	struct minstrel_ht_sta *mi = &msp->ht;
	struct ieee80211_mcs_info *mcs = &sta->ht_cap.mcs;
	u16 sta_cap = sta->ht_cap.cap;
	int n_supported = 0;
	int ack_dur;
	int stbc;
	int i;

	/* fall back to the old minstrel for legacy stations */
	if (!sta->ht_cap.ht_supported)
		goto use_legacy;

	BUILD_BUG_ON(ARRAY_SIZE(minstrel_mcs_groups) !=
		MINSTREL_MAX_STREAMS * MINSTREL_STREAM_GROUPS + 1);

	msp->is_ht = true;
	memset(mi, 0, sizeof(*mi));

	mi->sta = sta;
	mi->stats_update = jiffies;

	ack_dur = ieee80211_frame_duration(sband->band, 10, 60, 1, 1);
	mi->overhead = ieee80211_frame_duration(sband->band, 0, 60, 1, 1) + ack_dur;
	mi->overhead_rtscts = mi->overhead + 2 * ack_dur;

	mi->avg_ampdu_len = MINSTREL_FRAC(1, 1);

	/* When using MRR, sample more on the first attempt, without delay */
	if (mp->has_mrr) {
		mi->sample_count = 16;
		mi->sample_wait = 0;
	} else {
		mi->sample_count = 8;
		mi->sample_wait = 8;
	}
	mi->sample_tries = 4;

	stbc = (sta_cap & IEEE80211_HT_CAP_RX_STBC) >>
		IEEE80211_HT_CAP_RX_STBC_SHIFT;
	mi->tx_flags |= stbc << IEEE80211_TX_CTL_STBC_SHIFT;

	if (sta_cap & IEEE80211_HT_CAP_LDPC_CODING)
		mi->tx_flags |= IEEE80211_TX_CTL_LDPC;

	for (i = 0; i < ARRAY_SIZE(mi->groups); i++) {
		mi->groups[i].supported = 0;
		if (i == MINSTREL_CCK_GROUP) {
			minstrel_ht_update_cck(mp, mi, sband, sta);
			continue;
		}

		if (minstrel_mcs_groups[i].flags & IEEE80211_TX_RC_SHORT_GI) {
			if (minstrel_mcs_groups[i].flags & IEEE80211_TX_RC_40_MHZ_WIDTH) {
				if (!(sta_cap & IEEE80211_HT_CAP_SGI_40))
					continue;
			} else {
				if (!(sta_cap & IEEE80211_HT_CAP_SGI_20))
					continue;
			}
		}

		if (minstrel_mcs_groups[i].flags & IEEE80211_TX_RC_40_MHZ_WIDTH &&
		    sta->bandwidth < IEEE80211_STA_RX_BW_40)
			continue;

		/* Mark MCS > 7 as unsupported if STA is in static SMPS mode */
		if (sta->smps_mode == IEEE80211_SMPS_STATIC &&
		    minstrel_mcs_groups[i].streams > 1)
			continue;

		mi->groups[i].supported =
			mcs->rx_mask[minstrel_mcs_groups[i].streams - 1];

		if (mi->groups[i].supported)
			n_supported++;
	}

	if (!n_supported)
		goto use_legacy;

	/* create an initial rate table with the lowest supported rates */
	minstrel_ht_update_stats(mp, mi);
	minstrel_ht_update_rates(mp, mi);

	return;

use_legacy:
	msp->is_ht = false;
	memset(&msp->legacy, 0, sizeof(msp->legacy));
	msp->legacy.r = msp->ratelist;
	msp->legacy.sample_table = msp->sample_table;
	return mac80211_minstrel.rate_init(priv, sband, sta, &msp->legacy);
}