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
typedef  int u32 ;
struct TYPE_2__ {int ampdu_len; int ampdu_ack_len; } ;
struct ieee80211_tx_info {TYPE_1__ status; } ;
struct ath_softc {int dummy; } ;
struct ath_rate_table {int probe_interval; } ;
struct ath_rate_priv {int* per; int probe_rate; int rate_max_phy; int probe_time; int hw_maxretry_pktcnt; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 

__attribute__((used)) static void ath_rc_update_per(struct ath_softc *sc,
			      const struct ath_rate_table *rate_table,
			      struct ath_rate_priv *ath_rc_priv,
				  struct ieee80211_tx_info *tx_info,
			      int tx_rate, int xretries, int retries,
			      u32 now_msec)
{
	int count, n_bad_frames;
	u8 last_per;
	static const u32 nretry_to_per_lookup[10] = {
		100 * 0 / 1,
		100 * 1 / 4,
		100 * 1 / 2,
		100 * 3 / 4,
		100 * 4 / 5,
		100 * 5 / 6,
		100 * 6 / 7,
		100 * 7 / 8,
		100 * 8 / 9,
		100 * 9 / 10
	};

	last_per = ath_rc_priv->per[tx_rate];
	n_bad_frames = tx_info->status.ampdu_len - tx_info->status.ampdu_ack_len;

	if (xretries) {
		if (xretries == 1) {
			ath_rc_priv->per[tx_rate] += 30;
			if (ath_rc_priv->per[tx_rate] > 100)
				ath_rc_priv->per[tx_rate] = 100;
		} else {
			/* xretries == 2 */
			count = ARRAY_SIZE(nretry_to_per_lookup);
			if (retries >= count)
				retries = count - 1;

			/* new_PER = 7/8*old_PER + 1/8*(currentPER) */
			ath_rc_priv->per[tx_rate] =
				(u8)(last_per - (last_per >> 3) + (100 >> 3));
		}

		/* xretries == 1 or 2 */

		if (ath_rc_priv->probe_rate == tx_rate)
			ath_rc_priv->probe_rate = 0;

	} else { /* xretries == 0 */
		count = ARRAY_SIZE(nretry_to_per_lookup);
		if (retries >= count)
			retries = count - 1;

		if (n_bad_frames) {
			/* new_PER = 7/8*old_PER + 1/8*(currentPER)
			 * Assuming that n_frames is not 0.  The current PER
			 * from the retries is 100 * retries / (retries+1),
			 * since the first retries attempts failed, and the
			 * next one worked.  For the one that worked,
			 * n_bad_frames subframes out of n_frames wored,
			 * so the PER for that part is
			 * 100 * n_bad_frames / n_frames, and it contributes
			 * 100 * n_bad_frames / (n_frames * (retries+1)) to
			 * the above PER.  The expression below is a
			 * simplified version of the sum of these two terms.
			 */
			if (tx_info->status.ampdu_len > 0) {
				int n_frames, n_bad_tries;
				u8 cur_per, new_per;

				n_bad_tries = retries * tx_info->status.ampdu_len +
					n_bad_frames;
				n_frames = tx_info->status.ampdu_len * (retries + 1);
				cur_per = (100 * n_bad_tries / n_frames) >> 3;
				new_per = (u8)(last_per - (last_per >> 3) + cur_per);
				ath_rc_priv->per[tx_rate] = new_per;
			}
		} else {
			ath_rc_priv->per[tx_rate] =
				(u8)(last_per - (last_per >> 3) +
				     (nretry_to_per_lookup[retries] >> 3));
		}


		/*
		 * If we got at most one retry then increase the max rate if
		 * this was a probe.  Otherwise, ignore the probe.
		 */
		if (ath_rc_priv->probe_rate && ath_rc_priv->probe_rate == tx_rate) {
			if (retries > 0 || 2 * n_bad_frames > tx_info->status.ampdu_len) {
				/*
				 * Since we probed with just a single attempt,
				 * any retries means the probe failed.  Also,
				 * if the attempt worked, but more than half
				 * the subframes were bad then also consider
				 * the probe a failure.
				 */
				ath_rc_priv->probe_rate = 0;
			} else {
				u8 probe_rate = 0;

				ath_rc_priv->rate_max_phy =
					ath_rc_priv->probe_rate;
				probe_rate = ath_rc_priv->probe_rate;

				if (ath_rc_priv->per[probe_rate] > 30)
					ath_rc_priv->per[probe_rate] = 20;

				ath_rc_priv->probe_rate = 0;

				/*
				 * Since this probe succeeded, we allow the next
				 * probe twice as soon.  This allows the maxRate
				 * to move up faster if the probes are
				 * successful.
				 */
				ath_rc_priv->probe_time =
					now_msec - rate_table->probe_interval / 2;
			}
		}

		if (retries > 0) {
			/*
			 * Don't update anything.  We don't know if
			 * this was because of collisions or poor signal.
			 */
			ath_rc_priv->hw_maxretry_pktcnt = 0;
		} else {
			/*
			 * It worked with no retries. First ignore bogus (small)
			 * rssi_ack values.
			 */
			if (tx_rate == ath_rc_priv->rate_max_phy &&
			    ath_rc_priv->hw_maxretry_pktcnt < 255) {
				ath_rc_priv->hw_maxretry_pktcnt++;
			}

		}
	}
}