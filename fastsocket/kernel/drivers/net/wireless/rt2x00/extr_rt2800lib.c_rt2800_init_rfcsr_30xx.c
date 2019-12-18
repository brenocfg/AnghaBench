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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_NIC_CONF1 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_DAC_TEST ; 
 int /*<<< orphan*/  GPIO_SWITCH ; 
 int /*<<< orphan*/  GPIO_SWITCH_5 ; 
 int /*<<< orphan*/  LDO_CFG0 ; 
 int /*<<< orphan*/  LDO_CFG0_BGSEL ; 
 int /*<<< orphan*/  LDO_CFG0_LDO_CORE_VLEVEL ; 
 int /*<<< orphan*/  REV_RT3070F ; 
 int /*<<< orphan*/  REV_RT3071E ; 
 int /*<<< orphan*/  REV_RT3090E ; 
 int /*<<< orphan*/  RFCSR6_R2 ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3071 ; 
 int /*<<< orphan*/  RT3090 ; 
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_3xxx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rx_filter_calibration (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev_lt (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_30xx(struct rt2x00_dev *rt2x00dev)
{
	u8 rfcsr;
	u16 eeprom;
	u32 reg;

	/* XXX vendor driver do this only for 3070 */
	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_write(rt2x00dev, 4, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x60);
	rt2800_rfcsr_write(rt2x00dev, 9, 0x0f);
	rt2800_rfcsr_write(rt2x00dev, 10, 0x41);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x21);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x7b);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x90);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x58);
	rt2800_rfcsr_write(rt2x00dev, 16, 0xb3);
	rt2800_rfcsr_write(rt2x00dev, 17, 0x92);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x2c);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 20, 0xba);
	rt2800_rfcsr_write(rt2x00dev, 21, 0xdb);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x16);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x01);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x1f);

	if (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F)) {
		rt2800_register_read(rt2x00dev, LDO_CFG0, &reg);
		rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
		rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
		rt2800_register_write(rt2x00dev, LDO_CFG0, reg);
	} else if (rt2x00_rt(rt2x00dev, RT3071) ||
		   rt2x00_rt(rt2x00dev, RT3090)) {
		rt2800_rfcsr_write(rt2x00dev, 31, 0x14);

		rt2800_rfcsr_read(rt2x00dev, 6, &rfcsr);
		rt2x00_set_field8(&rfcsr, RFCSR6_R2, 1);
		rt2800_rfcsr_write(rt2x00dev, 6, rfcsr);

		rt2800_register_read(rt2x00dev, LDO_CFG0, &reg);
		rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
		if (rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
		    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E)) {
			rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC_CONF1, &eeprom);
			if (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_DAC_TEST))
				rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
			else
				rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 0);
		}
		rt2800_register_write(rt2x00dev, LDO_CFG0, reg);

		rt2800_register_read(rt2x00dev, GPIO_SWITCH, &reg);
		rt2x00_set_field32(&reg, GPIO_SWITCH_5, 0);
		rt2800_register_write(rt2x00dev, GPIO_SWITCH, reg);
	}

	rt2800_rx_filter_calibration(rt2x00dev);

	if (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E))
		rt2800_rfcsr_write(rt2x00dev, 27, 0x03);

	rt2800_led_open_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
}