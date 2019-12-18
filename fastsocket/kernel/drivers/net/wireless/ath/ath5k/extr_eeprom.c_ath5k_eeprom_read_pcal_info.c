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
struct ath5k_eeprom_info {int /*<<< orphan*/  ee_misc0; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {scalar_t__ ah_ee_version; TYPE_1__ ah_capabilities; } ;

/* Variables and functions */
 int AR5K_EEPROM_EEMAP (int /*<<< orphan*/ ) ; 
 int AR5K_EEPROM_MODE_11A ; 
 int AR5K_EEPROM_MODE_11G ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_0 ; 
 scalar_t__ AR5K_EEPROM_VERSION_5_0 ; 
 int ath5k_eeprom_read_pcal_info_2413 (struct ath5k_hw*,int) ; 
 int ath5k_eeprom_read_pcal_info_5111 (struct ath5k_hw*,int) ; 
 int ath5k_eeprom_read_pcal_info_5112 (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_eeprom_read_target_rate_pwr_info (struct ath5k_hw*,int) ; 

__attribute__((used)) static int
ath5k_eeprom_read_pcal_info(struct ath5k_hw *ah)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	int (*read_pcal)(struct ath5k_hw *hw, int mode);
	int mode;
	int err;

	if ((ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0) &&
			(AR5K_EEPROM_EEMAP(ee->ee_misc0) == 1))
		read_pcal = ath5k_eeprom_read_pcal_info_5112;
	else if ((ah->ah_ee_version >= AR5K_EEPROM_VERSION_5_0) &&
			(AR5K_EEPROM_EEMAP(ee->ee_misc0) == 2))
		read_pcal = ath5k_eeprom_read_pcal_info_2413;
	else
		read_pcal = ath5k_eeprom_read_pcal_info_5111;


	for (mode = AR5K_EEPROM_MODE_11A; mode <= AR5K_EEPROM_MODE_11G;
	mode++) {
		err = read_pcal(ah, mode);
		if (err)
			return err;

		err = ath5k_eeprom_read_target_rate_pwr_info(ah, mode);
		if (err < 0)
			return err;
	}

	return 0;
}