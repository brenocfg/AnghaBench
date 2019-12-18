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
typedef  int u16 ;
struct ath5k_eeprom_info {scalar_t__ ee_version; int* ee_n_piers; struct ath5k_chan_pcal_info* ee_pwr_cal_a; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {int /*<<< orphan*/  ah_ee_version; TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info {int freq; } ;

/* Variables and functions */
 int AR5K_EEPROM_FREQ_M (int /*<<< orphan*/ ) ; 
 size_t AR5K_EEPROM_MODE_11A ; 
 int AR5K_EEPROM_N_5GHZ_CHAN ; 
 int /*<<< orphan*/  AR5K_EEPROM_READ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_3 ; 
 int ath5k_eeprom_bin2freq (struct ath5k_eeprom_info*,int,size_t) ; 
 int /*<<< orphan*/  ath5k_eeprom_read_freq_list (struct ath5k_hw*,int*,int,struct ath5k_chan_pcal_info*,size_t) ; 

__attribute__((used)) static int
ath5k_eeprom_init_11a_pcal_freq(struct ath5k_hw *ah, int offset)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info *pcal = ee->ee_pwr_cal_a;
	int i;
	u16 val;
	u8 mask;

	if (ee->ee_version >= AR5K_EEPROM_VERSION_3_3) {
		ath5k_eeprom_read_freq_list(ah, &offset,
			AR5K_EEPROM_N_5GHZ_CHAN, pcal,
			AR5K_EEPROM_MODE_11A);
	} else {
		mask = AR5K_EEPROM_FREQ_M(ah->ah_ee_version);

		AR5K_EEPROM_READ(offset++, val);
		pcal[0].freq  = (val >> 9) & mask;
		pcal[1].freq  = (val >> 2) & mask;
		pcal[2].freq  = (val << 5) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[2].freq |= (val >> 11) & 0x1f;
		pcal[3].freq  = (val >> 4) & mask;
		pcal[4].freq  = (val << 3) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[4].freq |= (val >> 13) & 0x7;
		pcal[5].freq  = (val >> 6) & mask;
		pcal[6].freq  = (val << 1) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[6].freq |= (val >> 15) & 0x1;
		pcal[7].freq  = (val >> 8) & mask;
		pcal[8].freq  = (val >> 1) & mask;
		pcal[9].freq  = (val << 6) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[9].freq |= (val >> 10) & 0x3f;

		/* Fixed number of piers */
		ee->ee_n_piers[AR5K_EEPROM_MODE_11A] = 10;

		for (i = 0; i < AR5K_EEPROM_N_5GHZ_CHAN; i++) {
			pcal[i].freq = ath5k_eeprom_bin2freq(ee,
				pcal[i].freq, AR5K_EEPROM_MODE_11A);
		}
	}

	return 0;
}