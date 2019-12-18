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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ tx; scalar_t__ rx; } ;
struct rt2x00_dev {void* rssi_offset; int /*<<< orphan*/  cap_flags; int /*<<< orphan*/  led_qual; int /*<<< orphan*/  led_radio; TYPE_1__ default_ant; } ;

/* Variables and functions */
 void* ANTENNA_HW_DIVERSITY ; 
 scalar_t__ ANTENNA_SW_DIVERSITY ; 
 int /*<<< orphan*/  CAPABILITY_HW_BUTTON ; 
 int /*<<< orphan*/  EEPROM_ANTENNA ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_HARDWARE_RADIO ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_LED_MODE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RF_TYPE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_TX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_CALIBRATE_OFFSET ; 
 int /*<<< orphan*/  EEPROM_CALIBRATE_OFFSET_RSSI ; 
 int ENODEV ; 
 int LED_MODE_ASUS ; 
 int LED_MODE_DEFAULT ; 
 int LED_MODE_TXRX_ACTIVITY ; 
 int /*<<< orphan*/  LED_TYPE_ACTIVITY ; 
 int /*<<< orphan*/  LED_TYPE_RADIO ; 
 int /*<<< orphan*/  MAC_CSR0 ; 
 int /*<<< orphan*/  RF2522 ; 
 int /*<<< orphan*/  RF2523 ; 
 int /*<<< orphan*/  RF2524 ; 
 int /*<<< orphan*/  RF2525 ; 
 int /*<<< orphan*/  RF2525E ; 
 int /*<<< orphan*/  RF5222 ; 
 int /*<<< orphan*/  RT2570 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2500usb_init_led (struct rt2x00_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 void* rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_rf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_chip (struct rt2x00_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rt2500usb_init_eeprom(struct rt2x00_dev *rt2x00dev)
{
	u16 reg;
	u16 value;
	u16 eeprom;

	/*
	 * Read EEPROM word for configuration.
	 */
	rt2x00_eeprom_read(rt2x00dev, EEPROM_ANTENNA, &eeprom);

	/*
	 * Identify RF chipset.
	 */
	value = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RF_TYPE);
	rt2500usb_register_read(rt2x00dev, MAC_CSR0, &reg);
	rt2x00_set_chip(rt2x00dev, RT2570, value, reg);

	if (((reg & 0xfff0) != 0) || ((reg & 0x0000000f) == 0)) {
		rt2x00_err(rt2x00dev, "Invalid RT chipset detected\n");
		return -ENODEV;
	}

	if (!rt2x00_rf(rt2x00dev, RF2522) &&
	    !rt2x00_rf(rt2x00dev, RF2523) &&
	    !rt2x00_rf(rt2x00dev, RF2524) &&
	    !rt2x00_rf(rt2x00dev, RF2525) &&
	    !rt2x00_rf(rt2x00dev, RF2525E) &&
	    !rt2x00_rf(rt2x00dev, RF5222)) {
		rt2x00_err(rt2x00dev, "Invalid RF chipset detected\n");
		return -ENODEV;
	}

	/*
	 * Identify default antenna configuration.
	 */
	rt2x00dev->default_ant.tx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_TX_DEFAULT);
	rt2x00dev->default_ant.rx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RX_DEFAULT);

	/*
	 * When the eeprom indicates SW_DIVERSITY use HW_DIVERSITY instead.
	 * I am not 100% sure about this, but the legacy drivers do not
	 * indicate antenna swapping in software is required when
	 * diversity is enabled.
	 */
	if (rt2x00dev->default_ant.tx == ANTENNA_SW_DIVERSITY)
		rt2x00dev->default_ant.tx = ANTENNA_HW_DIVERSITY;
	if (rt2x00dev->default_ant.rx == ANTENNA_SW_DIVERSITY)
		rt2x00dev->default_ant.rx = ANTENNA_HW_DIVERSITY;

	/*
	 * Store led mode, for correct led behaviour.
	 */
#ifdef CONFIG_RT2X00_LIB_LEDS
	value = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_LED_MODE);

	rt2500usb_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	if (value == LED_MODE_TXRX_ACTIVITY ||
	    value == LED_MODE_DEFAULT ||
	    value == LED_MODE_ASUS)
		rt2500usb_init_led(rt2x00dev, &rt2x00dev->led_qual,
				   LED_TYPE_ACTIVITY);
#endif /* CONFIG_RT2X00_LIB_LEDS */

	/*
	 * Detect if this device has an hardware controlled radio.
	 */
	if (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_HARDWARE_RADIO))
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);

	/*
	 * Read the RSSI <-> dBm offset information.
	 */
	rt2x00_eeprom_read(rt2x00dev, EEPROM_CALIBRATE_OFFSET, &eeprom);
	rt2x00dev->rssi_offset =
	    rt2x00_get_field16(eeprom, EEPROM_CALIBRATE_OFFSET_RSSI);

	return 0;
}