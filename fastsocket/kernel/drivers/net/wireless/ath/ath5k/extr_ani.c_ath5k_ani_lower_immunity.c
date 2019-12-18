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
struct ath5k_hw {scalar_t__ opmode; int /*<<< orphan*/  ah_beacon_rssi_avg; } ;
struct ath5k_ani_state {scalar_t__ firstep_level; scalar_t__ spur_level; scalar_t__ noise_imm_level; int /*<<< orphan*/  ofdm_weak_sig; } ;

/* Variables and functions */
 int ATH5K_ANI_RSSI_THR_HIGH ; 
 int ATH5K_ANI_RSSI_THR_LOW ; 
 int /*<<< orphan*/  ATH5K_DBG_UNLIMIT (struct ath5k_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_ANI ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  ath5k_ani_set_firstep_level (struct ath5k_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_ani_set_noise_immunity_level (struct ath5k_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_ani_set_ofdm_weak_signal_detection (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_ani_set_spur_immunity_level (struct ath5k_hw*,scalar_t__) ; 
 int ewma_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath5k_ani_lower_immunity(struct ath5k_hw *ah, struct ath5k_ani_state *as)
{
	int rssi = ewma_read(&ah->ah_beacon_rssi_avg);

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "lower immunity");

	if (ah->opmode == NL80211_IFTYPE_AP) {
		/* AP mode */
		if (as->firstep_level > 0) {
			ath5k_ani_set_firstep_level(ah, as->firstep_level - 1);
			return;
		}
	} else {
		/* STA and IBSS mode (see TODO above) */
		if (rssi > ATH5K_ANI_RSSI_THR_HIGH) {
			/* beacon signal is high, leave OFDM weak signal
			 * detection off or it may oscillate
			 * TODO: who said it's off??? */
		} else if (rssi > ATH5K_ANI_RSSI_THR_LOW) {
			/* beacon RSSI is mid-range: turn on ODFM weak signal
			 * detection and next, lower firstep level */
			if (!as->ofdm_weak_sig) {
				ath5k_ani_set_ofdm_weak_signal_detection(ah,
									 true);
				return;
			}
			if (as->firstep_level > 0) {
				ath5k_ani_set_firstep_level(ah,
							as->firstep_level - 1);
				return;
			}
		} else {
			/* beacon signal is low: only reduce firstep level */
			if (as->firstep_level > 0) {
				ath5k_ani_set_firstep_level(ah,
							as->firstep_level - 1);
				return;
			}
		}
	}

	/* all modes */
	if (as->spur_level > 0) {
		ath5k_ani_set_spur_immunity_level(ah, as->spur_level - 1);
		return;
	}

	/* finally, reduce noise immunity */
	if (as->noise_imm_level > 0) {
		ath5k_ani_set_noise_immunity_level(ah, as->noise_imm_level - 1);
		return;
	}
}