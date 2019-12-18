#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_supported_band {int n_bitrates; size_t band; TYPE_1__* bitrates; } ;
struct TYPE_8__ {int* rx_mask; } ;
struct TYPE_10__ {int /*<<< orphan*/  ht_supported; TYPE_3__ mcs; } ;
struct ieee80211_sta {int* supp_rates; TYPE_5__ ht_cap; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct TYPE_9__ {int* rs_rates; int rs_nrates; } ;
struct TYPE_7__ {int* rs_rates; int rs_nrates; } ;
struct ath_rate_priv {int /*<<< orphan*/  ht_cap; int /*<<< orphan*/  rate_table; TYPE_4__ neg_ht_rates; TYPE_2__ neg_rates; } ;
struct ath_common {int dummy; } ;
struct TYPE_6__ {int bitrate; } ;

/* Variables and functions */
 int ATH_RATE_MAX ; 
 int BIT (int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_choose_rate_table (struct ath_softc*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  ath_rc_build_ht_caps (struct ath_softc*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ath_rc_init (struct ath_softc*,void*) ; 

__attribute__((used)) static void ath_rate_init(void *priv, struct ieee80211_supported_band *sband,
                          struct ieee80211_sta *sta, void *priv_sta)
{
	struct ath_softc *sc = priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_rate_priv *ath_rc_priv = priv_sta;
	int i, j = 0;

	for (i = 0; i < sband->n_bitrates; i++) {
		if (sta->supp_rates[sband->band] & BIT(i)) {
			ath_rc_priv->neg_rates.rs_rates[j]
				= (sband->bitrates[i].bitrate * 2) / 10;
			j++;
		}
	}
	ath_rc_priv->neg_rates.rs_nrates = j;

	if (sta->ht_cap.ht_supported) {
		for (i = 0, j = 0; i < 77; i++) {
			if (sta->ht_cap.mcs.rx_mask[i/8] & (1<<(i%8)))
				ath_rc_priv->neg_ht_rates.rs_rates[j++] = i;
			if (j == ATH_RATE_MAX)
				break;
		}
		ath_rc_priv->neg_ht_rates.rs_nrates = j;
	}

	ath_rc_priv->rate_table = ath_choose_rate_table(sc, sband->band,
							sta->ht_cap.ht_supported);
	if (!ath_rc_priv->rate_table) {
		ath_err(common, "No rate table chosen\n");
		return;
	}

	ath_rc_priv->ht_cap = ath_rc_build_ht_caps(sc, sta);
	ath_rc_init(sc, priv_sta);
}