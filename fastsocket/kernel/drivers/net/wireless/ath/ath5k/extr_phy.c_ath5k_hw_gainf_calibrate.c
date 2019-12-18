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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ g_state; scalar_t__ g_f_corr; scalar_t__ g_current; } ;
struct ath5k_eeprom_info {scalar_t__ ee_cck_ofdm_gain_delta; } ;
struct TYPE_3__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {scalar_t__ ah_radio_5ghz_revision; TYPE_2__ ah_gain; int /*<<< orphan*/ * ah_rf_banks; TYPE_1__ ah_capabilities; } ;
typedef  enum ath5k_rfgain { ____Placeholder_ath5k_rfgain } ath5k_rfgain ;

/* Variables and functions */
 scalar_t__ AR5K_GAIN_CCK_PROBE_CORR ; 
 scalar_t__ AR5K_GAIN_CHECK_ADJUST (TYPE_2__*) ; 
 int /*<<< orphan*/  AR5K_PHY_PAPD_PROBE ; 
 scalar_t__ AR5K_PHY_PAPD_PROBE_GAINF_S ; 
 scalar_t__ AR5K_PHY_PAPD_PROBE_TX_NEXT ; 
 int /*<<< orphan*/  AR5K_PHY_PAPD_PROBE_TYPE ; 
 scalar_t__ AR5K_PHY_PAPD_PROBE_TYPE_CCK ; 
 scalar_t__ AR5K_REG_MS (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ AR5K_RFGAIN_ACTIVE ; 
 scalar_t__ AR5K_RFGAIN_INACTIVE ; 
 scalar_t__ AR5K_RFGAIN_NEED_CHANGE ; 
 scalar_t__ AR5K_RFGAIN_READ_REQUESTED ; 
 scalar_t__ AR5K_SREV_RAD_5112A ; 
 scalar_t__ ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath5k_hw_rf_check_gainf_readback (struct ath5k_hw*) ; 
 scalar_t__ ath5k_hw_rf_gainf_adjust (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_rf_gainf_corr (struct ath5k_hw*) ; 

enum ath5k_rfgain
ath5k_hw_gainf_calibrate(struct ath5k_hw *ah)
{
	u32 data, type;
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;

	if (ah->ah_rf_banks == NULL ||
	ah->ah_gain.g_state == AR5K_RFGAIN_INACTIVE)
		return AR5K_RFGAIN_INACTIVE;

	/* No check requested, either engine is inactive
	 * or an adjustment is already requested */
	if (ah->ah_gain.g_state != AR5K_RFGAIN_READ_REQUESTED)
		goto done;

	/* Read the PAPD (Peak to Average Power Detector)
	 * register */
	data = ath5k_hw_reg_read(ah, AR5K_PHY_PAPD_PROBE);

	/* No probe is scheduled, read gain_F measurement */
	if (!(data & AR5K_PHY_PAPD_PROBE_TX_NEXT)) {
		ah->ah_gain.g_current = data >> AR5K_PHY_PAPD_PROBE_GAINF_S;
		type = AR5K_REG_MS(data, AR5K_PHY_PAPD_PROBE_TYPE);

		/* If tx packet is CCK correct the gain_F measurement
		 * by cck ofdm gain delta */
		if (type == AR5K_PHY_PAPD_PROBE_TYPE_CCK) {
			if (ah->ah_radio_5ghz_revision >= AR5K_SREV_RAD_5112A)
				ah->ah_gain.g_current +=
					ee->ee_cck_ofdm_gain_delta;
			else
				ah->ah_gain.g_current +=
					AR5K_GAIN_CCK_PROBE_CORR;
		}

		/* Further correct gain_F measurement for
		 * RF5112A radios */
		if (ah->ah_radio_5ghz_revision >= AR5K_SREV_RAD_5112A) {
			ath5k_hw_rf_gainf_corr(ah);
			ah->ah_gain.g_current =
				ah->ah_gain.g_current >= ah->ah_gain.g_f_corr ?
				(ah->ah_gain.g_current - ah->ah_gain.g_f_corr) :
				0;
		}

		/* Check if measurement is ok and if we need
		 * to adjust gain, schedule a gain adjustment,
		 * else switch back to the active state */
		if (ath5k_hw_rf_check_gainf_readback(ah) &&
		AR5K_GAIN_CHECK_ADJUST(&ah->ah_gain) &&
		ath5k_hw_rf_gainf_adjust(ah)) {
			ah->ah_gain.g_state = AR5K_RFGAIN_NEED_CHANGE;
		} else {
			ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		}
	}

done:
	return ah->ah_gain.g_state;
}