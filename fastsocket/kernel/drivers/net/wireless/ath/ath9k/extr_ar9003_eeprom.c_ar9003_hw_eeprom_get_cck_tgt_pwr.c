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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct cal_tgt_pow_legacy {int /*<<< orphan*/ * tPow2x; } ;
struct ar9300_eeprom {int /*<<< orphan*/ * calTarget_freqbin_Cck; struct cal_tgt_pow_legacy* calTargetPowerCck; } ;
struct TYPE_2__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int AR9300_NUM_2G_CCK_TARGET_POWERS ; 
 int /*<<< orphan*/  ar9003_hw_power_interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ath9k_hw_fbin2freq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 ar9003_hw_eeprom_get_cck_tgt_pwr(struct ath_hw *ah,
					   u16 rateIndex, u16 freq)
{
	u16 numPiers = AR9300_NUM_2G_CCK_TARGET_POWERS, i;
	s32 targetPowerArray[AR9300_NUM_2G_CCK_TARGET_POWERS];
	s32 freqArray[AR9300_NUM_2G_CCK_TARGET_POWERS];
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	struct cal_tgt_pow_legacy *pEepromTargetPwr = eep->calTargetPowerCck;
	u8 *pFreqBin = eep->calTarget_freqbin_Cck;

	/*
	 * create array of channels and targetpower from
	 * targetpower piers stored on eeprom
	 */
	for (i = 0; i < numPiers; i++) {
		freqArray[i] = ath9k_hw_fbin2freq(pFreqBin[i], 1);
		targetPowerArray[i] = pEepromTargetPwr[i].tPow2x[rateIndex];
	}

	/* interpolate to get target power for given frequency */
	return (u8) ar9003_hw_power_interpolate((s32) freq,
						 freqArray,
						 targetPowerArray, numPiers);
}