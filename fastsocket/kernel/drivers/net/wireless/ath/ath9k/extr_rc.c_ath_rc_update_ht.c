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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct ieee80211_tx_info {int dummy; } ;
struct ath_softc {int dummy; } ;
struct ath_rate_table {int rate_cnt; scalar_t__ probe_interval; TYPE_1__* info; } ;
struct ath_rate_priv {int rate_table_size; int* per; size_t rate_max_phy; scalar_t__ per_down_time; scalar_t__ probe_time; struct ath_rate_table* rate_table; } ;
struct TYPE_2__ {scalar_t__ ratekbps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_debug_stat_retries (struct ath_rate_priv*,int,int,int,int) ; 
 int /*<<< orphan*/  ath_rc_get_lower_rix (struct ath_rate_priv*,int,size_t*) ; 
 int /*<<< orphan*/  ath_rc_update_per (struct ath_softc*,struct ath_rate_table const*,struct ath_rate_priv*,struct ieee80211_tx_info*,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ jiffies_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath_rc_update_ht(struct ath_softc *sc,
			     struct ath_rate_priv *ath_rc_priv,
			     struct ieee80211_tx_info *tx_info,
			     int tx_rate, int xretries, int retries)
{
	u32 now_msec = jiffies_to_msecs(jiffies);
	int rate;
	u8 last_per;
	const struct ath_rate_table *rate_table = ath_rc_priv->rate_table;
	int size = ath_rc_priv->rate_table_size;

	if ((tx_rate < 0) || (tx_rate > rate_table->rate_cnt))
		return;

	last_per = ath_rc_priv->per[tx_rate];

	/* Update PER first */
	ath_rc_update_per(sc, rate_table, ath_rc_priv,
			  tx_info, tx_rate, xretries,
			  retries, now_msec);

	/*
	 * If this rate looks bad (high PER) then stop using it for
	 * a while (except if we are probing).
	 */
	if (ath_rc_priv->per[tx_rate] >= 55 && tx_rate > 0 &&
	    rate_table->info[tx_rate].ratekbps <=
	    rate_table->info[ath_rc_priv->rate_max_phy].ratekbps) {
		ath_rc_get_lower_rix(ath_rc_priv, (u8)tx_rate,
				     &ath_rc_priv->rate_max_phy);

		/* Don't probe for a little while. */
		ath_rc_priv->probe_time = now_msec;
	}

	/* Make sure the rates below this have lower PER */
	/* Monotonicity is kept only for rates below the current rate. */
	if (ath_rc_priv->per[tx_rate] < last_per) {
		for (rate = tx_rate - 1; rate >= 0; rate--) {

			if (ath_rc_priv->per[rate] >
			    ath_rc_priv->per[rate+1]) {
				ath_rc_priv->per[rate] =
					ath_rc_priv->per[rate+1];
			}
		}
	}

	/* Maintain monotonicity for rates above the current rate */
	for (rate = tx_rate; rate < size - 1; rate++) {
		if (ath_rc_priv->per[rate+1] <
		    ath_rc_priv->per[rate])
			ath_rc_priv->per[rate+1] =
				ath_rc_priv->per[rate];
	}

	/* Every so often, we reduce the thresholds
	 * and PER (different for CCK and OFDM). */
	if (now_msec - ath_rc_priv->per_down_time >=
	    rate_table->probe_interval) {
		for (rate = 0; rate < size; rate++) {
			ath_rc_priv->per[rate] =
				7 * ath_rc_priv->per[rate] / 8;
		}

		ath_rc_priv->per_down_time = now_msec;
	}

	ath_debug_stat_retries(ath_rc_priv, tx_rate, xretries, retries,
			       ath_rc_priv->per[tx_rate]);

}