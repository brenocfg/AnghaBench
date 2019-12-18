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
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct ath5k_eeprom_info {scalar_t__ ee_version; void*** ee_spur_chans; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;

/* Variables and functions */
 void* AR5K_EEPROM_5413_SPUR_CHAN_1 ; 
 void* AR5K_EEPROM_5413_SPUR_CHAN_2 ; 
 scalar_t__ AR5K_EEPROM_CTL (scalar_t__) ; 
 void* AR5K_EEPROM_NO_SPUR ; 
 scalar_t__ AR5K_EEPROM_N_CTLS (scalar_t__) ; 
 int AR5K_EEPROM_N_SPUR_CHANS ; 
 int /*<<< orphan*/  AR5K_EEPROM_READ (scalar_t__,void*) ; 
 scalar_t__ AR5K_EEPROM_VERSION_5_3 ; 

__attribute__((used)) static int
ath5k_eeprom_read_spur_chans(struct ath5k_hw *ah)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 offset;
	u16 val;
	int ret = 0, i;

	offset = AR5K_EEPROM_CTL(ee->ee_version) +
				AR5K_EEPROM_N_CTLS(ee->ee_version);

	if (ee->ee_version < AR5K_EEPROM_VERSION_5_3) {
		/* No spur info for 5GHz */
		ee->ee_spur_chans[0][0] = AR5K_EEPROM_NO_SPUR;
		/* 2 channels for 2GHz (2464/2420) */
		ee->ee_spur_chans[0][1] = AR5K_EEPROM_5413_SPUR_CHAN_1;
		ee->ee_spur_chans[1][1] = AR5K_EEPROM_5413_SPUR_CHAN_2;
		ee->ee_spur_chans[2][1] = AR5K_EEPROM_NO_SPUR;
	} else if (ee->ee_version >= AR5K_EEPROM_VERSION_5_3) {
		for (i = 0; i < AR5K_EEPROM_N_SPUR_CHANS; i++) {
			AR5K_EEPROM_READ(offset, val);
			ee->ee_spur_chans[i][0] = val;
			AR5K_EEPROM_READ(offset + AR5K_EEPROM_N_SPUR_CHANS,
									val);
			ee->ee_spur_chans[i][1] = val;
			offset++;
		}
	}

	return ret;
}