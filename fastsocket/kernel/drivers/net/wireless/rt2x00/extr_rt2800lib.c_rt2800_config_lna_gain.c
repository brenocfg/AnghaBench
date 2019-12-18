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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int channel; } ;
struct rt2x00lib_conf {TYPE_1__ rf; } ;
struct rt2x00_dev {short lna_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_LNA ; 
 int /*<<< orphan*/  EEPROM_LNA_A0 ; 
 int /*<<< orphan*/  EEPROM_LNA_BG ; 
 int /*<<< orphan*/  EEPROM_RSSI_A2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A2_LNA_A2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG2_LNA_A1 ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 short rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_config_lna_gain(struct rt2x00_dev *rt2x00dev,
				   struct rt2x00lib_conf *libconf)
{
	u16 eeprom;
	short lna_gain;

	if (libconf->rf.channel <= 14) {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_LNA, &eeprom);
		lna_gain = rt2x00_get_field16(eeprom, EEPROM_LNA_BG);
	} else if (libconf->rf.channel <= 64) {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_LNA, &eeprom);
		lna_gain = rt2x00_get_field16(eeprom, EEPROM_LNA_A0);
	} else if (libconf->rf.channel <= 128) {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_BG2, &eeprom);
		lna_gain = rt2x00_get_field16(eeprom, EEPROM_RSSI_BG2_LNA_A1);
	} else {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_A2, &eeprom);
		lna_gain = rt2x00_get_field16(eeprom, EEPROM_RSSI_A2_LNA_A2);
	}

	rt2x00dev->lna_gain = lna_gain;
}