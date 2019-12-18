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
typedef  size_t u8 ;
struct TYPE_4__ {int /*<<< orphan*/  ofdm_trig_low; int /*<<< orphan*/  ofdm_trig_high; } ;
struct ath_hw {scalar_t__ opmode; TYPE_2__ config; TYPE_1__* curchan; } ;
struct ath_common {int dummy; } ;
struct ar5416AniState {size_t ofdmNoiseImmunityLevel; size_t cckNoiseImmunityLevel; scalar_t__ spurImmunityLevel; scalar_t__ firstepLevel; int ofdmWeakSigDetect; } ;
struct ani_ofdm_level_entry {scalar_t__ spur_immunity_level; scalar_t__ fir_step_level; int ofdm_weak_signal_on; } ;
struct ani_cck_level_entry {scalar_t__ fir_step_level; } ;
struct TYPE_3__ {struct ar5416AniState ani; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 int /*<<< orphan*/  ATH9K_ANI_FIRSTEP_LEVEL ; 
 size_t ATH9K_ANI_OFDM_DEF_LEVEL ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_HIGH ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_HIGH_BELOW_INI ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_LOW ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_LOW_ABOVE_INI ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_WEAK_SIGNAL_DETECTION ; 
 scalar_t__ ATH9K_ANI_RSSI_THR_HIGH ; 
 int /*<<< orphan*/  ATH9K_ANI_RSSI_THR_LOW ; 
 int /*<<< orphan*/  ATH9K_ANI_SPUR_IMMUNITY_LEVEL ; 
 scalar_t__ BEACON_RSSI (struct ath_hw*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ath9k_hw_ani_control (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t,size_t,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ani_cck_level_entry* cck_level_table ; 
 struct ani_ofdm_level_entry* ofdm_level_table ; 

__attribute__((used)) static void ath9k_hw_set_ofdm_nil(struct ath_hw *ah, u8 immunityLevel,
				  bool scan)
{
	struct ar5416AniState *aniState = &ah->curchan->ani;
	struct ath_common *common = ath9k_hw_common(ah);
	const struct ani_ofdm_level_entry *entry_ofdm;
	const struct ani_cck_level_entry *entry_cck;
	bool weak_sig;

	ath_dbg(common, ANI, "**** ofdmlevel %d=>%d, rssi=%d[lo=%d hi=%d]\n",
		aniState->ofdmNoiseImmunityLevel,
		immunityLevel, BEACON_RSSI(ah),
		ATH9K_ANI_RSSI_THR_LOW,
		ATH9K_ANI_RSSI_THR_HIGH);

	if (!scan)
		aniState->ofdmNoiseImmunityLevel = immunityLevel;

	entry_ofdm = &ofdm_level_table[aniState->ofdmNoiseImmunityLevel];
	entry_cck = &cck_level_table[aniState->cckNoiseImmunityLevel];

	if (aniState->spurImmunityLevel != entry_ofdm->spur_immunity_level)
		ath9k_hw_ani_control(ah,
				     ATH9K_ANI_SPUR_IMMUNITY_LEVEL,
				     entry_ofdm->spur_immunity_level);

	if (aniState->firstepLevel != entry_ofdm->fir_step_level &&
	    entry_ofdm->fir_step_level >= entry_cck->fir_step_level)
		ath9k_hw_ani_control(ah,
				     ATH9K_ANI_FIRSTEP_LEVEL,
				     entry_ofdm->fir_step_level);

	weak_sig = entry_ofdm->ofdm_weak_signal_on;
	if (ah->opmode == NL80211_IFTYPE_STATION &&
	    BEACON_RSSI(ah) <= ATH9K_ANI_RSSI_THR_HIGH)
		weak_sig = true;

	if (aniState->ofdmWeakSigDetect != weak_sig)
			ath9k_hw_ani_control(ah,
				ATH9K_ANI_OFDM_WEAK_SIGNAL_DETECTION,
				entry_ofdm->ofdm_weak_signal_on);

	if (aniState->ofdmNoiseImmunityLevel >= ATH9K_ANI_OFDM_DEF_LEVEL) {
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW_ABOVE_INI;
	} else {
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH_BELOW_INI;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW;
	}
}