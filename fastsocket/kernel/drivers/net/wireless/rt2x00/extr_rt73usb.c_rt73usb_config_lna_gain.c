#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00lib_conf {TYPE_3__* conf; } ;
struct rt2x00_dev {short lna_gain; int /*<<< orphan*/  cap_flags; } ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct TYPE_4__ {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_LNA_BG ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_A ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_A_1 ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_BG ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_BG_1 ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt73usb_config_lna_gain(struct rt2x00_dev *rt2x00dev,
				    struct rt2x00lib_conf *libconf)
{
	u16 eeprom;
	short lna_gain = 0;

	if (libconf->conf->chandef.chan->band == IEEE80211_BAND_2GHZ) {
		if (test_bit(CAPABILITY_EXTERNAL_LNA_BG, &rt2x00dev->cap_flags))
			lna_gain += 14;

		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_OFFSET_BG, &eeprom);
		lna_gain -= rt2x00_get_field16(eeprom, EEPROM_RSSI_OFFSET_BG_1);
	} else {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_OFFSET_A, &eeprom);
		lna_gain -= rt2x00_get_field16(eeprom, EEPROM_RSSI_OFFSET_A_1);
	}

	rt2x00dev->lna_gain = lna_gain;
}