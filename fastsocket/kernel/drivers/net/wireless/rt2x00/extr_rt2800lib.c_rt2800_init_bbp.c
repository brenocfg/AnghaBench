#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rt2x00_dev {int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP152_RX_DEFAULT_ANT ; 
 int /*<<< orphan*/  BBP3_ADC_INIT_MODE ; 
 int /*<<< orphan*/  BBP3_ADC_MODE_SWITCH ; 
 int /*<<< orphan*/  BBP47_TSSI_ADC6 ; 
 int /*<<< orphan*/  CAPABILITY_BT_COEXIST ; 
 int EACCES ; 
 int /*<<< orphan*/  EEPROM_BBP_REG_ID ; 
 unsigned int EEPROM_BBP_SIZE ; 
 scalar_t__ EEPROM_BBP_START ; 
 int /*<<< orphan*/  EEPROM_BBP_VALUE ; 
 scalar_t__ EEPROM_NIC_CONF0 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_RXPATH ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_TXPATH ; 
 scalar_t__ EEPROM_NIC_CONF1 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_ANT_DIVERSITY ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int /*<<< orphan*/  GPIO_CTRL_DIR3 ; 
 int /*<<< orphan*/  GPIO_CTRL_DIR6 ; 
 int /*<<< orphan*/  GPIO_CTRL_VAL3 ; 
 int /*<<< orphan*/  GPIO_CTRL_VAL6 ; 
 int /*<<< orphan*/  REV_RT2860C ; 
 int /*<<< orphan*/  REV_RT2860D ; 
 int /*<<< orphan*/  REV_RT3070F ; 
 int /*<<< orphan*/  REV_RT3071E ; 
 int /*<<< orphan*/  REV_RT3090E ; 
 int /*<<< orphan*/  REV_RT3390E ; 
 int /*<<< orphan*/  REV_RT5390R ; 
 int /*<<< orphan*/  RT2860 ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3071 ; 
 int /*<<< orphan*/  RT3090 ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  RT3352 ; 
 int /*<<< orphan*/  RT3390 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  RT5390 ; 
 int /*<<< orphan*/  RT5392 ; 
 int /*<<< orphan*/  RT5592 ; 
 int /*<<< orphan*/  rt2800_bbp4_mac_if_ctrl (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_bbp_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_init_bbp_5592 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_freq_calibration (struct rt2x00_dev*) ; 
 scalar_t__ rt2800_is_305x_soc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2800_wait_bbp_ready (struct rt2x00_dev*) ; 
 scalar_t__ rt2800_wait_bbp_rf_ready (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,scalar_t__,int*) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev_gte (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rt2800_init_bbp(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	if (unlikely(rt2800_wait_bbp_rf_ready(rt2x00dev) ||
		     rt2800_wait_bbp_ready(rt2x00dev)))
		return -EACCES;

	if (rt2x00_rt(rt2x00dev, RT5592)) {
		rt2800_init_bbp_5592(rt2x00dev);
		return 0;
	}

	if (rt2x00_rt(rt2x00dev, RT3352)) {
		rt2800_bbp_write(rt2x00dev, 3, 0x00);
		rt2800_bbp_write(rt2x00dev, 4, 0x50);
	}

	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp4_mac_if_ctrl(rt2x00dev);

	if (rt2800_is_305x_soc(rt2x00dev) ||
	    rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT3572) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 31, 0x08);

	if (rt2x00_rt(rt2x00dev, RT3352))
		rt2800_bbp_write(rt2x00dev, 47, 0x48);

	rt2800_bbp_write(rt2x00dev, 65, 0x2c);
	rt2800_bbp_write(rt2x00dev, 66, 0x38);

	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 68, 0x0b);

	if (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860C)) {
		rt2800_bbp_write(rt2x00dev, 69, 0x16);
		rt2800_bbp_write(rt2x00dev, 73, 0x12);
	} else if (rt2x00_rt(rt2x00dev, RT3290) ||
		   rt2x00_rt(rt2x00dev, RT3352) ||
		   rt2x00_rt(rt2x00dev, RT5390) ||
		   rt2x00_rt(rt2x00dev, RT5392)) {
		rt2800_bbp_write(rt2x00dev, 69, 0x12);
		rt2800_bbp_write(rt2x00dev, 73, 0x13);
		rt2800_bbp_write(rt2x00dev, 75, 0x46);
		rt2800_bbp_write(rt2x00dev, 76, 0x28);

		if (rt2x00_rt(rt2x00dev, RT3290))
			rt2800_bbp_write(rt2x00dev, 77, 0x58);
		else
			rt2800_bbp_write(rt2x00dev, 77, 0x59);
	} else {
		rt2800_bbp_write(rt2x00dev, 69, 0x12);
		rt2800_bbp_write(rt2x00dev, 73, 0x10);
	}

	rt2800_bbp_write(rt2x00dev, 70, 0x0a);

	if (rt2x00_rt(rt2x00dev, RT3070) ||
	    rt2x00_rt(rt2x00dev, RT3071) ||
	    rt2x00_rt(rt2x00dev, RT3090) ||
	    rt2x00_rt(rt2x00dev, RT3390) ||
	    rt2x00_rt(rt2x00dev, RT3572) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392)) {
		rt2800_bbp_write(rt2x00dev, 79, 0x13);
		rt2800_bbp_write(rt2x00dev, 80, 0x05);
		rt2800_bbp_write(rt2x00dev, 81, 0x33);
	} else if (rt2800_is_305x_soc(rt2x00dev)) {
		rt2800_bbp_write(rt2x00dev, 78, 0x0e);
		rt2800_bbp_write(rt2x00dev, 80, 0x08);
	} else if (rt2x00_rt(rt2x00dev, RT3290)) {
		rt2800_bbp_write(rt2x00dev, 74, 0x0b);
		rt2800_bbp_write(rt2x00dev, 79, 0x18);
		rt2800_bbp_write(rt2x00dev, 80, 0x09);
		rt2800_bbp_write(rt2x00dev, 81, 0x33);
	} else if (rt2x00_rt(rt2x00dev, RT3352)) {
		rt2800_bbp_write(rt2x00dev, 78, 0x0e);
		rt2800_bbp_write(rt2x00dev, 80, 0x08);
		rt2800_bbp_write(rt2x00dev, 81, 0x37);
	} else {
		rt2800_bbp_write(rt2x00dev, 81, 0x37);
	}

	rt2800_bbp_write(rt2x00dev, 82, 0x62);
	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 83, 0x7a);
	else
		rt2800_bbp_write(rt2x00dev, 83, 0x6a);

	if (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860D))
		rt2800_bbp_write(rt2x00dev, 84, 0x19);
	else if (rt2x00_rt(rt2x00dev, RT3290) ||
		 rt2x00_rt(rt2x00dev, RT5390) ||
		 rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 84, 0x9a);
	else
		rt2800_bbp_write(rt2x00dev, 84, 0x99);

	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 86, 0x38);
	else
		rt2800_bbp_write(rt2x00dev, 86, 0x00);

	if (rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 88, 0x90);

	rt2800_bbp_write(rt2x00dev, 91, 0x04);

	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 92, 0x02);
	else
		rt2800_bbp_write(rt2x00dev, 92, 0x00);

	if (rt2x00_rt(rt2x00dev, RT5392)) {
		rt2800_bbp_write(rt2x00dev, 95, 0x9a);
		rt2800_bbp_write(rt2x00dev, 98, 0x12);
	}

	if (rt2x00_rt_rev_gte(rt2x00dev, RT3070, REV_RT3070F) ||
	    rt2x00_rt_rev_gte(rt2x00dev, RT3071, REV_RT3071E) ||
	    rt2x00_rt_rev_gte(rt2x00dev, RT3090, REV_RT3090E) ||
	    rt2x00_rt_rev_gte(rt2x00dev, RT3390, REV_RT3390E) ||
	    rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT3572) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392) ||
	    rt2800_is_305x_soc(rt2x00dev))
		rt2800_bbp_write(rt2x00dev, 103, 0xc0);
	else
		rt2800_bbp_write(rt2x00dev, 103, 0x00);

	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 104, 0x92);

	if (rt2800_is_305x_soc(rt2x00dev))
		rt2800_bbp_write(rt2x00dev, 105, 0x01);
	else if (rt2x00_rt(rt2x00dev, RT3290))
		rt2800_bbp_write(rt2x00dev, 105, 0x1c);
	else if (rt2x00_rt(rt2x00dev, RT3352))
		rt2800_bbp_write(rt2x00dev, 105, 0x34);
	else if (rt2x00_rt(rt2x00dev, RT5390) ||
		 rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 105, 0x3c);
	else
		rt2800_bbp_write(rt2x00dev, 105, 0x05);

	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT5390))
		rt2800_bbp_write(rt2x00dev, 106, 0x03);
	else if (rt2x00_rt(rt2x00dev, RT3352))
		rt2800_bbp_write(rt2x00dev, 106, 0x05);
	else if (rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 106, 0x12);
	else
		rt2800_bbp_write(rt2x00dev, 106, 0x35);

	if (rt2x00_rt(rt2x00dev, RT3352))
		rt2800_bbp_write(rt2x00dev, 120, 0x50);

	if (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_write(rt2x00dev, 128, 0x12);

	if (rt2x00_rt(rt2x00dev, RT5392)) {
		rt2800_bbp_write(rt2x00dev, 134, 0xd0);
		rt2800_bbp_write(rt2x00dev, 135, 0xf6);
	}

	if (rt2x00_rt(rt2x00dev, RT3352))
		rt2800_bbp_write(rt2x00dev, 137, 0x0f);

	if (rt2x00_rt(rt2x00dev, RT3071) ||
	    rt2x00_rt(rt2x00dev, RT3090) ||
	    rt2x00_rt(rt2x00dev, RT3390) ||
	    rt2x00_rt(rt2x00dev, RT3572) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392)) {
		rt2800_bbp_read(rt2x00dev, 138, &value);

		rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC_CONF0, &eeprom);
		if (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH) == 1)
			value |= 0x20;
		if (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH) == 1)
			value &= ~0x02;

		rt2800_bbp_write(rt2x00dev, 138, value);
	}

	if (rt2x00_rt(rt2x00dev, RT3290)) {
		rt2800_bbp_write(rt2x00dev, 67, 0x24);
		rt2800_bbp_write(rt2x00dev, 143, 0x04);
		rt2800_bbp_write(rt2x00dev, 142, 0x99);
		rt2800_bbp_write(rt2x00dev, 150, 0x30);
		rt2800_bbp_write(rt2x00dev, 151, 0x2e);
		rt2800_bbp_write(rt2x00dev, 152, 0x20);
		rt2800_bbp_write(rt2x00dev, 153, 0x34);
		rt2800_bbp_write(rt2x00dev, 154, 0x40);
		rt2800_bbp_write(rt2x00dev, 155, 0x3b);
		rt2800_bbp_write(rt2x00dev, 253, 0x04);

		rt2800_bbp_read(rt2x00dev, 47, &value);
		rt2x00_set_field8(&value, BBP47_TSSI_ADC6, 1);
		rt2800_bbp_write(rt2x00dev, 47, value);

		/* Use 5-bit ADC for Acquisition and 8-bit ADC for data */
		rt2800_bbp_read(rt2x00dev, 3, &value);
		rt2x00_set_field8(&value, BBP3_ADC_MODE_SWITCH, 1);
		rt2x00_set_field8(&value, BBP3_ADC_INIT_MODE, 1);
		rt2800_bbp_write(rt2x00dev, 3, value);
	}

	if (rt2x00_rt(rt2x00dev, RT3352)) {
		rt2800_bbp_write(rt2x00dev, 163, 0xbd);
		/* Set ITxBF timeout to 0x9c40=1000msec */
		rt2800_bbp_write(rt2x00dev, 179, 0x02);
		rt2800_bbp_write(rt2x00dev, 180, 0x00);
		rt2800_bbp_write(rt2x00dev, 182, 0x40);
		rt2800_bbp_write(rt2x00dev, 180, 0x01);
		rt2800_bbp_write(rt2x00dev, 182, 0x9c);
		rt2800_bbp_write(rt2x00dev, 179, 0x00);
		/* Reprogram the inband interface to put right values in RXWI */
		rt2800_bbp_write(rt2x00dev, 142, 0x04);
		rt2800_bbp_write(rt2x00dev, 143, 0x3b);
		rt2800_bbp_write(rt2x00dev, 142, 0x06);
		rt2800_bbp_write(rt2x00dev, 143, 0xa0);
		rt2800_bbp_write(rt2x00dev, 142, 0x07);
		rt2800_bbp_write(rt2x00dev, 143, 0xa1);
		rt2800_bbp_write(rt2x00dev, 142, 0x08);
		rt2800_bbp_write(rt2x00dev, 143, 0xa2);

		rt2800_bbp_write(rt2x00dev, 148, 0xc8);
	}

	if (rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392)) {
		int ant, div_mode;

		rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC_CONF1, &eeprom);
		div_mode = rt2x00_get_field16(eeprom,
					      EEPROM_NIC_CONF1_ANT_DIVERSITY);
		ant = (div_mode == 3) ? 1 : 0;

		/* check if this is a Bluetooth combo card */
		if (test_bit(CAPABILITY_BT_COEXIST, &rt2x00dev->cap_flags)) {
			u32 reg;

			rt2800_register_read(rt2x00dev, GPIO_CTRL, &reg);
			rt2x00_set_field32(&reg, GPIO_CTRL_DIR3, 0);
			rt2x00_set_field32(&reg, GPIO_CTRL_DIR6, 0);
			rt2x00_set_field32(&reg, GPIO_CTRL_VAL3, 0);
			rt2x00_set_field32(&reg, GPIO_CTRL_VAL6, 0);
			if (ant == 0)
				rt2x00_set_field32(&reg, GPIO_CTRL_VAL3, 1);
			else if (ant == 1)
				rt2x00_set_field32(&reg, GPIO_CTRL_VAL6, 1);
			rt2800_register_write(rt2x00dev, GPIO_CTRL, reg);
		}

		/* This chip has hardware antenna diversity*/
		if (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390R)) {
			rt2800_bbp_write(rt2x00dev, 150, 0); /* Disable Antenna Software OFDM */
			rt2800_bbp_write(rt2x00dev, 151, 0); /* Disable Antenna Software CCK */
			rt2800_bbp_write(rt2x00dev, 154, 0); /* Clear previously selected antenna */
		}

		rt2800_bbp_read(rt2x00dev, 152, &value);
		if (ant == 0)
			rt2x00_set_field8(&value, BBP152_RX_DEFAULT_ANT, 1);
		else
			rt2x00_set_field8(&value, BBP152_RX_DEFAULT_ANT, 0);
		rt2800_bbp_write(rt2x00dev, 152, value);

		rt2800_init_freq_calibration(rt2x00dev);
	}

	for (i = 0; i < EEPROM_BBP_SIZE; i++) {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_BBP_START + i, &eeprom);

		if (eeprom != 0xffff && eeprom != 0x0000) {
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt2800_bbp_write(rt2x00dev, reg_id, value);
		}
	}

	return 0;
}