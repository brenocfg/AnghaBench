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
typedef  int u16 ;
struct ath5k_eeprom_info {int** ee_pdc_to_idx; int* ee_x_gain; int* ee_pd_gains; scalar_t__ ee_version; int* ee_n_piers; struct ath5k_chan_pcal_info* ee_pwr_cal_g; int /*<<< orphan*/  ee_header; struct ath5k_chan_pcal_info* ee_pwr_cal_b; struct ath5k_chan_pcal_info* ee_pwr_cal_a; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info_rf5112 {int* pcdac_x0; int* pwr_x3; int* pcdac_x3; void** pwr_x0; } ;
struct ath5k_chan_pcal_info {void* max_pwr; struct ath5k_chan_pcal_info_rf5112 rf5112_info; } ;
typedef  void* s8 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_EEPROM_GROUP2_OFFSET ; 
 int /*<<< orphan*/  AR5K_EEPROM_GROUP3_OFFSET ; 
 int /*<<< orphan*/  AR5K_EEPROM_GROUP4_OFFSET ; 
 scalar_t__ AR5K_EEPROM_GROUPS_START (scalar_t__) ; 
 int /*<<< orphan*/  AR5K_EEPROM_HDR_11A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_EEPROM_HDR_11B (int /*<<< orphan*/ ) ; 
#define  AR5K_EEPROM_MODE_11A 130 
#define  AR5K_EEPROM_MODE_11B 129 
#define  AR5K_EEPROM_MODE_11G 128 
 int AR5K_EEPROM_N_PD_CURVES ; 
 int AR5K_EEPROM_N_XPD0_POINTS ; 
 int /*<<< orphan*/  AR5K_EEPROM_READ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_3 ; 
 int EINVAL ; 
 int ath5k_eeprom_convert_pcal_info_5112 (struct ath5k_hw*,int,struct ath5k_chan_pcal_info*) ; 
 int /*<<< orphan*/  ath5k_eeprom_init_11a_pcal_freq (struct ath5k_hw*,scalar_t__) ; 

__attribute__((used)) static int
ath5k_eeprom_read_pcal_info_5112(struct ath5k_hw *ah, int mode)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info_rf5112 *chan_pcal_info;
	struct ath5k_chan_pcal_info *gen_chan_info;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	u32 offset;
	u8 i, c;
	u16 val;
	u8 pd_gains = 0;

	/* Count how many curves we have and
	 * identify them (which one of the 4
	 * available curves we have on each count).
	 * Curves are stored from lower (x0) to
	 * higher (x3) gain */
	for (i = 0; i < AR5K_EEPROM_N_PD_CURVES; i++) {
		/* ee_x_gain[mode] is x gain mask */
		if ((ee->ee_x_gain[mode] >> i) & 0x1)
			pdgain_idx[pd_gains++] = i;
	}
	ee->ee_pd_gains[mode] = pd_gains;

	if (pd_gains == 0 || pd_gains > 2)
		return -EINVAL;

	switch (mode) {
	case AR5K_EEPROM_MODE_11A:
		/*
		 * Read 5GHz EEPROM channels
		 */
		offset = AR5K_EEPROM_GROUPS_START(ee->ee_version);
		ath5k_eeprom_init_11a_pcal_freq(ah, offset);

		offset += AR5K_EEPROM_GROUP2_OFFSET;
		gen_chan_info = ee->ee_pwr_cal_a;
		break;
	case AR5K_EEPROM_MODE_11B:
		offset = AR5K_EEPROM_GROUPS_START(ee->ee_version);
		if (AR5K_EEPROM_HDR_11A(ee->ee_header))
			offset += AR5K_EEPROM_GROUP3_OFFSET;

		/* NB: frequency piers parsed during mode init */
		gen_chan_info = ee->ee_pwr_cal_b;
		break;
	case AR5K_EEPROM_MODE_11G:
		offset = AR5K_EEPROM_GROUPS_START(ee->ee_version);
		if (AR5K_EEPROM_HDR_11A(ee->ee_header))
			offset += AR5K_EEPROM_GROUP4_OFFSET;
		else if (AR5K_EEPROM_HDR_11B(ee->ee_header))
			offset += AR5K_EEPROM_GROUP2_OFFSET;

		/* NB: frequency piers parsed during mode init */
		gen_chan_info = ee->ee_pwr_cal_g;
		break;
	default:
		return -EINVAL;
	}

	for (i = 0; i < ee->ee_n_piers[mode]; i++) {
		chan_pcal_info = &gen_chan_info[i].rf5112_info;

		/* Power values in quarter dB
		 * for the lower xpd gain curve
		 * (0 dBm -> higher output power) */
		for (c = 0; c < AR5K_EEPROM_N_XPD0_POINTS; c++) {
			AR5K_EEPROM_READ(offset++, val);
			chan_pcal_info->pwr_x0[c] = (s8) (val & 0xff);
			chan_pcal_info->pwr_x0[++c] = (s8) ((val >> 8) & 0xff);
		}

		/* PCDAC steps
		 * corresponding to the above power
		 * measurements */
		AR5K_EEPROM_READ(offset++, val);
		chan_pcal_info->pcdac_x0[1] = (val & 0x1f);
		chan_pcal_info->pcdac_x0[2] = ((val >> 5) & 0x1f);
		chan_pcal_info->pcdac_x0[3] = ((val >> 10) & 0x1f);

		/* Power values in quarter dB
		 * for the higher xpd gain curve
		 * (18 dBm -> lower output power) */
		AR5K_EEPROM_READ(offset++, val);
		chan_pcal_info->pwr_x3[0] = (s8) (val & 0xff);
		chan_pcal_info->pwr_x3[1] = (s8) ((val >> 8) & 0xff);

		AR5K_EEPROM_READ(offset++, val);
		chan_pcal_info->pwr_x3[2] = (val & 0xff);

		/* PCDAC steps
		 * corresponding to the above power
		 * measurements (fixed) */
		chan_pcal_info->pcdac_x3[0] = 20;
		chan_pcal_info->pcdac_x3[1] = 35;
		chan_pcal_info->pcdac_x3[2] = 63;

		if (ee->ee_version >= AR5K_EEPROM_VERSION_4_3) {
			chan_pcal_info->pcdac_x0[0] = ((val >> 8) & 0x3f);

			/* Last xpd0 power level is also channel maximum */
			gen_chan_info[i].max_pwr = chan_pcal_info->pwr_x0[3];
		} else {
			chan_pcal_info->pcdac_x0[0] = 1;
			gen_chan_info[i].max_pwr = (s8) ((val >> 8) & 0xff);
		}

	}

	return ath5k_eeprom_convert_pcal_info_5112(ah, mode, gen_chan_info);
}