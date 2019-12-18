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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_channel {scalar_t__ band; scalar_t__ hw_value; int center_freq; } ;
struct ath5k_rf_reg {int dummy; } ;
struct ath5k_ini_rfbuffer {int rfb_bank; int /*<<< orphan*/  rfb_ctrl_register; int /*<<< orphan*/ * rfb_mode_data; } ;
struct TYPE_4__ {size_t g_step_idx; void* g_state; } ;
struct ath5k_eeprom_info {int** ee_ob; int** ee_db; int* ee_xpd; int* ee_x_gain; int* ee_i_gain; size_t** ee_pdc_to_idx; int* ee_pd_gains; } ;
struct TYPE_3__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {int ah_radio; int ah_rf_banks_size; int ah_radio_5ghz_revision; scalar_t__ ah_mac_srev; int* ah_offset; scalar_t__ ah_bwmode; scalar_t__ ah_phy_revision; TYPE_2__ ah_gain; int /*<<< orphan*/ * ah_rf_banks; void* ah_rf_regs_count; TYPE_1__ ah_capabilities; } ;
struct ath5k_gain_opt_step {int* gos_param; } ;
struct ath5k_gain_opt {struct ath5k_gain_opt_step* go_step; } ;

/* Variables and functions */
 scalar_t__ AR5K_BWMODE_10MHZ ; 
 scalar_t__ AR5K_BWMODE_40MHZ ; 
 scalar_t__ AR5K_BWMODE_5MHZ ; 
 size_t AR5K_EEPROM_MODE_11A ; 
 size_t AR5K_EEPROM_MODE_11B ; 
 size_t AR5K_EEPROM_MODE_11G ; 
 int AR5K_MAX_RF_BANKS ; 
 scalar_t__ AR5K_MODE_11B ; 
 int /*<<< orphan*/  AR5K_PHY_FRAME_CTL ; 
 int /*<<< orphan*/  AR5K_PHY_FRAME_CTL_TX_CLIP ; 
 int /*<<< orphan*/  AR5K_REG_WAIT (int) ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  AR5K_RF2316 134 
#define  AR5K_RF2317 133 
#define  AR5K_RF2413 132 
#define  AR5K_RF2425 131 
#define  AR5K_RF5111 130 
#define  AR5K_RF5112 129 
#define  AR5K_RF5413 128 
 void* AR5K_RFGAIN_ACTIVE ; 
 int /*<<< orphan*/  AR5K_RF_DB_2GHZ ; 
 int /*<<< orphan*/  AR5K_RF_DB_5GHZ ; 
 int /*<<< orphan*/  AR5K_RF_DERBY_CHAN_SEL_MODE ; 
 int /*<<< orphan*/  AR5K_RF_GAIN_I ; 
 int /*<<< orphan*/  AR5K_RF_HIGH_VC_CP ; 
 int /*<<< orphan*/  AR5K_RF_LOW_VC_CP ; 
 int /*<<< orphan*/  AR5K_RF_MAX_TIME ; 
 int /*<<< orphan*/  AR5K_RF_MID_VC_CP ; 
 int /*<<< orphan*/  AR5K_RF_MIXGAIN_OVR ; 
 int /*<<< orphan*/  AR5K_RF_OB_2GHZ ; 
 int /*<<< orphan*/  AR5K_RF_OB_5GHZ ; 
 int /*<<< orphan*/  AR5K_RF_PAD2GND ; 
 int /*<<< orphan*/  AR5K_RF_PD_DELAY_A ; 
 int /*<<< orphan*/  AR5K_RF_PD_GAIN_HI ; 
 int /*<<< orphan*/  AR5K_RF_PD_GAIN_LO ; 
 int /*<<< orphan*/  AR5K_RF_PD_PERIOD_A ; 
 int /*<<< orphan*/  AR5K_RF_PLO_SEL ; 
 int /*<<< orphan*/  AR5K_RF_PUSH_UP ; 
 int /*<<< orphan*/  AR5K_RF_PWD_130 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_131 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_132 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_136 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_137 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_138 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_166 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_167 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_84 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_90 ; 
 int /*<<< orphan*/  AR5K_RF_PWD_ICLOBUF_2G ; 
 int /*<<< orphan*/  AR5K_RF_PWD_XPD ; 
 int /*<<< orphan*/  AR5K_RF_RFGAIN_SEL ; 
 int /*<<< orphan*/  AR5K_RF_TURBO ; 
 int /*<<< orphan*/  AR5K_RF_WAIT_I ; 
 int /*<<< orphan*/  AR5K_RF_WAIT_S ; 
 int /*<<< orphan*/  AR5K_RF_XB2_LVL ; 
 int /*<<< orphan*/  AR5K_RF_XB5_LVL ; 
 int /*<<< orphan*/  AR5K_RF_XPD_GAIN ; 
 int /*<<< orphan*/  AR5K_RF_XPD_SEL ; 
 scalar_t__ AR5K_SREV_AR2417 ; 
 scalar_t__ AR5K_SREV_AR5413 ; 
 scalar_t__ AR5K_SREV_AR5424 ; 
 scalar_t__ AR5K_SREV_PHY_5212A ; 
 int AR5K_SREV_RAD_5112A ; 
 int AR5K_SREV_REV ; 
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int ath5k_hw_bitswap (int,int) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_rfb_op (struct ath5k_hw*,struct ath5k_rf_reg const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 void* rf_regs_2316 ; 
 void* rf_regs_2413 ; 
 void* rf_regs_2425 ; 
 void* rf_regs_5111 ; 
 void* rf_regs_5112 ; 
 void* rf_regs_5112a ; 
 void* rf_regs_5413 ; 
 void* rfb_2316 ; 
 void* rfb_2317 ; 
 void* rfb_2413 ; 
 void* rfb_2417 ; 
 void* rfb_2425 ; 
 void* rfb_5111 ; 
 void* rfb_5112 ; 
 void* rfb_5112a ; 
 void* rfb_5413 ; 
 struct ath5k_gain_opt rfgain_opt_5111 ; 
 struct ath5k_gain_opt rfgain_opt_5112 ; 

__attribute__((used)) static int
ath5k_hw_rfregs_init(struct ath5k_hw *ah,
			struct ieee80211_channel *channel,
			unsigned int mode)
{
	const struct ath5k_rf_reg *rf_regs;
	const struct ath5k_ini_rfbuffer *ini_rfb;
	const struct ath5k_gain_opt *go = NULL;
	const struct ath5k_gain_opt_step *g_step;
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u8 ee_mode = 0;
	u32 *rfb;
	int i, obdb = -1, bank = -1;

	switch (ah->ah_radio) {
	case AR5K_RF5111:
		rf_regs = rf_regs_5111;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5111);
		ini_rfb = rfb_5111;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5111);
		go = &rfgain_opt_5111;
		break;
	case AR5K_RF5112:
		if (ah->ah_radio_5ghz_revision >= AR5K_SREV_RAD_5112A) {
			rf_regs = rf_regs_5112a;
			ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112a);
			ini_rfb = rfb_5112a;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5112a);
		} else {
			rf_regs = rf_regs_5112;
			ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112);
			ini_rfb = rfb_5112;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5112);
		}
		go = &rfgain_opt_5112;
		break;
	case AR5K_RF2413:
		rf_regs = rf_regs_2413;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2413);
		ini_rfb = rfb_2413;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2413);
		break;
	case AR5K_RF2316:
		rf_regs = rf_regs_2316;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2316);
		ini_rfb = rfb_2316;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2316);
		break;
	case AR5K_RF5413:
		rf_regs = rf_regs_5413;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5413);
		ini_rfb = rfb_5413;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5413);
		break;
	case AR5K_RF2317:
		rf_regs = rf_regs_2425;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2425);
		ini_rfb = rfb_2317;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2317);
		break;
	case AR5K_RF2425:
		rf_regs = rf_regs_2425;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2425);
		if (ah->ah_mac_srev < AR5K_SREV_AR2417) {
			ini_rfb = rfb_2425;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2425);
		} else {
			ini_rfb = rfb_2417;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2417);
		}
		break;
	default:
		return -EINVAL;
	}

	/* If it's the first time we set RF buffer, allocate
	 * ah->ah_rf_banks based on ah->ah_rf_banks_size
	 * we set above */
	if (ah->ah_rf_banks == NULL) {
		ah->ah_rf_banks = kmalloc(sizeof(u32) * ah->ah_rf_banks_size,
								GFP_KERNEL);
		if (ah->ah_rf_banks == NULL) {
			ATH5K_ERR(ah, "out of memory\n");
			return -ENOMEM;
		}
	}

	/* Copy values to modify them */
	rfb = ah->ah_rf_banks;

	for (i = 0; i < ah->ah_rf_banks_size; i++) {
		if (ini_rfb[i].rfb_bank >= AR5K_MAX_RF_BANKS) {
			ATH5K_ERR(ah, "invalid bank\n");
			return -EINVAL;
		}

		/* Bank changed, write down the offset */
		if (bank != ini_rfb[i].rfb_bank) {
			bank = ini_rfb[i].rfb_bank;
			ah->ah_offset[bank] = i;
		}

		rfb[i] = ini_rfb[i].rfb_mode_data[mode];
	}

	/* Set Output and Driver bias current (OB/DB) */
	if (channel->band == IEEE80211_BAND_2GHZ) {

		if (channel->hw_value == AR5K_MODE_11B)
			ee_mode = AR5K_EEPROM_MODE_11B;
		else
			ee_mode = AR5K_EEPROM_MODE_11G;

		/* For RF511X/RF211X combination we
		 * use b_OB and b_DB parameters stored
		 * in eeprom on ee->ee_ob[ee_mode][0]
		 *
		 * For all other chips we use OB/DB for 2GHz
		 * stored in the b/g modal section just like
		 * 802.11a on ee->ee_ob[ee_mode][1] */
		if ((ah->ah_radio == AR5K_RF5111) ||
		(ah->ah_radio == AR5K_RF5112))
			obdb = 0;
		else
			obdb = 1;

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_ob[ee_mode][obdb],
						AR5K_RF_OB_2GHZ, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_db[ee_mode][obdb],
						AR5K_RF_DB_2GHZ, true);

	/* RF5111 always needs OB/DB for 5GHz, even if we use 2GHz */
	} else if ((channel->band == IEEE80211_BAND_5GHZ) ||
			(ah->ah_radio == AR5K_RF5111)) {

		/* For 11a, Turbo and XR we need to choose
		 * OB/DB based on frequency range */
		ee_mode = AR5K_EEPROM_MODE_11A;
		obdb =	 channel->center_freq >= 5725 ? 3 :
			(channel->center_freq >= 5500 ? 2 :
			(channel->center_freq >= 5260 ? 1 :
			 (channel->center_freq > 4000 ? 0 : -1)));

		if (obdb < 0)
			return -EINVAL;

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_ob[ee_mode][obdb],
						AR5K_RF_OB_5GHZ, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_db[ee_mode][obdb],
						AR5K_RF_DB_5GHZ, true);
	}

	g_step = &go->go_step[ah->ah_gain.g_step_idx];

	/* Set turbo mode (N/A on RF5413) */
	if ((ah->ah_bwmode == AR5K_BWMODE_40MHZ) &&
	(ah->ah_radio != AR5K_RF5413))
		ath5k_hw_rfb_op(ah, rf_regs, 1, AR5K_RF_TURBO, false);

	/* Bank Modifications (chip-specific) */
	if (ah->ah_radio == AR5K_RF5111) {

		/* Set gain_F settings according to current step */
		if (channel->hw_value != AR5K_MODE_11B) {

			AR5K_REG_WRITE_BITS(ah, AR5K_PHY_FRAME_CTL,
					AR5K_PHY_FRAME_CTL_TX_CLIP,
					g_step->gos_param[0]);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[1],
							AR5K_RF_PWD_90, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[2],
							AR5K_RF_PWD_84, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[3],
						AR5K_RF_RFGAIN_SEL, true);

			/* We programmed gain_F parameters, switch back
			 * to active state */
			ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;

		}

		/* Bank 6/7 setup */

		ath5k_hw_rfb_op(ah, rf_regs, !ee->ee_xpd[ee_mode],
						AR5K_RF_PWD_XPD, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_x_gain[ee_mode],
						AR5K_RF_XPD_GAIN, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_i_gain[ee_mode],
						AR5K_RF_GAIN_I, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_xpd[ee_mode],
						AR5K_RF_PLO_SEL, true);

		/* Tweak power detectors for half/quarter rate support */
		if (ah->ah_bwmode == AR5K_BWMODE_5MHZ ||
		ah->ah_bwmode == AR5K_BWMODE_10MHZ) {
			u8 wait_i;

			ath5k_hw_rfb_op(ah, rf_regs, 0x1f,
						AR5K_RF_WAIT_S, true);

			wait_i = (ah->ah_bwmode == AR5K_BWMODE_5MHZ) ?
							0x1f : 0x10;

			ath5k_hw_rfb_op(ah, rf_regs, wait_i,
						AR5K_RF_WAIT_I, true);
			ath5k_hw_rfb_op(ah, rf_regs, 3,
						AR5K_RF_MAX_TIME, true);

		}
	}

	if (ah->ah_radio == AR5K_RF5112) {

		/* Set gain_F settings according to current step */
		if (channel->hw_value != AR5K_MODE_11B) {

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[0],
						AR5K_RF_MIXGAIN_OVR, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[1],
						AR5K_RF_PWD_138, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[2],
						AR5K_RF_PWD_137, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[3],
						AR5K_RF_PWD_136, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[4],
						AR5K_RF_PWD_132, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[5],
						AR5K_RF_PWD_131, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[6],
						AR5K_RF_PWD_130, true);

			/* We programmed gain_F parameters, switch back
			 * to active state */
			ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		}

		/* Bank 6/7 setup */

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_xpd[ee_mode],
						AR5K_RF_XPD_SEL, true);

		if (ah->ah_radio_5ghz_revision < AR5K_SREV_RAD_5112A) {
			/* Rev. 1 supports only one xpd */
			ath5k_hw_rfb_op(ah, rf_regs,
						ee->ee_x_gain[ee_mode],
						AR5K_RF_XPD_GAIN, true);

		} else {
			u8 *pdg_curve_to_idx = ee->ee_pdc_to_idx[ee_mode];
			if (ee->ee_pd_gains[ee_mode] > 1) {
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[0],
						AR5K_RF_PD_GAIN_LO, true);
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[1],
						AR5K_RF_PD_GAIN_HI, true);
			} else {
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[0],
						AR5K_RF_PD_GAIN_LO, true);
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[0],
						AR5K_RF_PD_GAIN_HI, true);
			}

			/* Lower synth voltage on Rev 2 */
			if (ah->ah_radio == AR5K_RF5112 &&
			    (ah->ah_radio_5ghz_revision & AR5K_SREV_REV) > 0) {
				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_HIGH_VC_CP, true);

				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_MID_VC_CP, true);

				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_LOW_VC_CP, true);

				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_PUSH_UP, true);
			}

			/* Decrease power consumption on 5213+ BaseBand */
			if (ah->ah_phy_revision >= AR5K_SREV_PHY_5212A) {
				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_PAD2GND, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_XB2_LVL, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_XB5_LVL, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_PWD_167, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_PWD_166, true);
			}
		}

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_i_gain[ee_mode],
						AR5K_RF_GAIN_I, true);

		/* Tweak power detector for half/quarter rates */
		if (ah->ah_bwmode == AR5K_BWMODE_5MHZ ||
		ah->ah_bwmode == AR5K_BWMODE_10MHZ) {
			u8 pd_delay;

			pd_delay = (ah->ah_bwmode == AR5K_BWMODE_5MHZ) ?
							0xf : 0x8;

			ath5k_hw_rfb_op(ah, rf_regs, pd_delay,
						AR5K_RF_PD_PERIOD_A, true);
			ath5k_hw_rfb_op(ah, rf_regs, 0xf,
						AR5K_RF_PD_DELAY_A, true);

		}
	}

	if (ah->ah_radio == AR5K_RF5413 &&
	channel->band == IEEE80211_BAND_2GHZ) {

		ath5k_hw_rfb_op(ah, rf_regs, 1, AR5K_RF_DERBY_CHAN_SEL_MODE,
									true);

		/* Set optimum value for early revisions (on pci-e chips) */
		if (ah->ah_mac_srev >= AR5K_SREV_AR5424 &&
		ah->ah_mac_srev < AR5K_SREV_AR5413)
			ath5k_hw_rfb_op(ah, rf_regs, ath5k_hw_bitswap(6, 3),
						AR5K_RF_PWD_ICLOBUF_2G, true);

	}

	/* Write RF banks on hw */
	for (i = 0; i < ah->ah_rf_banks_size; i++) {
		AR5K_REG_WAIT(i);
		ath5k_hw_reg_write(ah, rfb[i], ini_rfb[i].rfb_ctrl_register);
	}

	return 0;
}