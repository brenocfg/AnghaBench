#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_supported_band {int n_bitrates; size_t band; TYPE_4__* bitrates; } ;
struct TYPE_22__ {int* rx_mask; } ;
struct TYPE_13__ {int cap; TYPE_8__ mcs; scalar_t__ ht_supported; } ;
struct ieee80211_sta {int* supp_rates; TYPE_10__ ht_cap; scalar_t__ drv_priv; } ;
struct TYPE_20__ {int* rs_rates; int rs_nrates; } ;
struct TYPE_19__ {int* rs_rates; int rs_nrates; } ;
struct TYPE_21__ {TYPE_6__ ht_rates; TYPE_5__ legacy_rates; } ;
struct ath9k_htc_target_rate {int isnew; int /*<<< orphan*/  capflags; int /*<<< orphan*/  sta_index; TYPE_7__ rates; } ;
struct ath9k_htc_sta {int /*<<< orphan*/  index; } ;
struct ath9k_htc_priv {TYPE_9__* hw; } ;
struct TYPE_17__ {TYPE_2__* chan; } ;
struct TYPE_14__ {TYPE_3__ chandef; } ;
struct TYPE_23__ {TYPE_11__ conf; TYPE_1__* wiphy; } ;
struct TYPE_18__ {int bitrate; } ;
struct TYPE_16__ {size_t band; } ;
struct TYPE_15__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int ATH_HTC_RATE_MAX ; 
 int BIT (int) ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  WLAN_RC_40_FLAG ; 
 int /*<<< orphan*/  WLAN_RC_DS_FLAG ; 
 int /*<<< orphan*/  WLAN_RC_HT_FLAG ; 
 int /*<<< orphan*/  WLAN_RC_SGI_FLAG ; 
 scalar_t__ conf_is_ht20 (TYPE_11__*) ; 
 scalar_t__ conf_is_ht40 (TYPE_11__*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_htc_setup_rate(struct ath9k_htc_priv *priv,
				 struct ieee80211_sta *sta,
				 struct ath9k_htc_target_rate *trate)
{
	struct ath9k_htc_sta *ista = (struct ath9k_htc_sta *) sta->drv_priv;
	struct ieee80211_supported_band *sband;
	u32 caps = 0;
	int i, j;

	sband = priv->hw->wiphy->bands[priv->hw->conf.chandef.chan->band];

	for (i = 0, j = 0; i < sband->n_bitrates; i++) {
		if (sta->supp_rates[sband->band] & BIT(i)) {
			trate->rates.legacy_rates.rs_rates[j]
				= (sband->bitrates[i].bitrate * 2) / 10;
			j++;
		}
	}
	trate->rates.legacy_rates.rs_nrates = j;

	if (sta->ht_cap.ht_supported) {
		for (i = 0, j = 0; i < 77; i++) {
			if (sta->ht_cap.mcs.rx_mask[i/8] & (1<<(i%8)))
				trate->rates.ht_rates.rs_rates[j++] = i;
			if (j == ATH_HTC_RATE_MAX)
				break;
		}
		trate->rates.ht_rates.rs_nrates = j;

		caps = WLAN_RC_HT_FLAG;
		if (sta->ht_cap.mcs.rx_mask[1])
			caps |= WLAN_RC_DS_FLAG;
		if ((sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) &&
		     (conf_is_ht40(&priv->hw->conf)))
			caps |= WLAN_RC_40_FLAG;
		if (conf_is_ht40(&priv->hw->conf) &&
		    (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40))
			caps |= WLAN_RC_SGI_FLAG;
		else if (conf_is_ht20(&priv->hw->conf) &&
			 (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20))
			caps |= WLAN_RC_SGI_FLAG;
	}

	trate->sta_index = ista->index;
	trate->isnew = 1;
	trate->capflags = cpu_to_be32(caps);
}