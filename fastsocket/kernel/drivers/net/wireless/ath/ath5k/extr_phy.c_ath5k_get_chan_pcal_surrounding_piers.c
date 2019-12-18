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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct ieee80211_channel {scalar_t__ center_freq; int hw_value; } ;
struct ath5k_eeprom_info {size_t* ee_n_piers; struct ath5k_chan_pcal_info* ee_pwr_cal_g; struct ath5k_chan_pcal_info* ee_pwr_cal_b; struct ath5k_chan_pcal_info* ee_pwr_cal_a; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info {scalar_t__ freq; } ;

/* Variables and functions */
#define  AR5K_EEPROM_MODE_11A 130 
#define  AR5K_EEPROM_MODE_11B 129 
#define  AR5K_EEPROM_MODE_11G 128 

__attribute__((used)) static void
ath5k_get_chan_pcal_surrounding_piers(struct ath5k_hw *ah,
			struct ieee80211_channel *channel,
			struct ath5k_chan_pcal_info **pcinfo_l,
			struct ath5k_chan_pcal_info **pcinfo_r)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info *pcinfo;
	u8 idx_l, idx_r;
	u8 mode, max, i;
	u32 target = channel->center_freq;

	idx_l = 0;
	idx_r = 0;

	switch (channel->hw_value) {
	case AR5K_EEPROM_MODE_11A:
		pcinfo = ee->ee_pwr_cal_a;
		mode = AR5K_EEPROM_MODE_11A;
		break;
	case AR5K_EEPROM_MODE_11B:
		pcinfo = ee->ee_pwr_cal_b;
		mode = AR5K_EEPROM_MODE_11B;
		break;
	case AR5K_EEPROM_MODE_11G:
	default:
		pcinfo = ee->ee_pwr_cal_g;
		mode = AR5K_EEPROM_MODE_11G;
		break;
	}
	max = ee->ee_n_piers[mode] - 1;

	/* Frequency is below our calibrated
	 * range. Use the lowest power curve
	 * we have */
	if (target < pcinfo[0].freq) {
		idx_l = idx_r = 0;
		goto done;
	}

	/* Frequency is above our calibrated
	 * range. Use the highest power curve
	 * we have */
	if (target > pcinfo[max].freq) {
		idx_l = idx_r = max;
		goto done;
	}

	/* Frequency is inside our calibrated
	 * channel range. Pick the surrounding
	 * calibration piers so that we can
	 * interpolate */
	for (i = 0; i <= max; i++) {

		/* Frequency matches one of our calibration
		 * piers, no need to interpolate, just use
		 * that calibration pier */
		if (pcinfo[i].freq == target) {
			idx_l = idx_r = i;
			goto done;
		}

		/* We found a calibration pier that's above
		 * frequency, use this pier and the previous
		 * one to interpolate */
		if (target < pcinfo[i].freq) {
			idx_r = i;
			idx_l = idx_r - 1;
			goto done;
		}
	}

done:
	*pcinfo_l = &pcinfo[idx_l];
	*pcinfo_r = &pcinfo[idx_r];
}