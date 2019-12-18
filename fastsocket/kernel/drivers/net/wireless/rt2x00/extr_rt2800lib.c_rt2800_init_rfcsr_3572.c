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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDO_CFG0 ; 
 int /*<<< orphan*/  LDO_CFG0_BGSEL ; 
 int /*<<< orphan*/  LDO_CFG0_LDO_CORE_VLEVEL ; 
 int /*<<< orphan*/  RFCSR6_R2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_3xxx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rx_filter_calibration (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_3572(struct rt2x00_dev *rt2x00dev)
{
	u8 rfcsr;
	u32 reg;

	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_write(rt2x00dev, 0, 0x70);
	rt2800_rfcsr_write(rt2x00dev, 1, 0x81);
	rt2800_rfcsr_write(rt2x00dev, 2, 0xf1);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 4, 0x4c);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x05);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x4a);
	rt2800_rfcsr_write(rt2x00dev, 7, 0xd8);
	rt2800_rfcsr_write(rt2x00dev, 9, 0xc3);
	rt2800_rfcsr_write(rt2x00dev, 10, 0xf1);
	rt2800_rfcsr_write(rt2x00dev, 11, 0xb9);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x70);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x65);
	rt2800_rfcsr_write(rt2x00dev, 14, 0xa0);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x53);
	rt2800_rfcsr_write(rt2x00dev, 16, 0x4c);
	rt2800_rfcsr_write(rt2x00dev, 17, 0x23);
	rt2800_rfcsr_write(rt2x00dev, 18, 0xac);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x93);
	rt2800_rfcsr_write(rt2x00dev, 20, 0xb3);
	rt2800_rfcsr_write(rt2x00dev, 21, 0xd0);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 23, 0x3c);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x16);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x15);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x85);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x9b);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x09);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x10);

	rt2800_rfcsr_read(rt2x00dev, 6, &rfcsr);
	rt2x00_set_field8(&rfcsr, RFCSR6_R2, 1);
	rt2800_rfcsr_write(rt2x00dev, 6, rfcsr);

	rt2800_register_read(rt2x00dev, LDO_CFG0, &reg);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
	rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
	rt2800_register_write(rt2x00dev, LDO_CFG0, reg);
	msleep(1);
	rt2800_register_read(rt2x00dev, LDO_CFG0, &reg);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 0);
	rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
	rt2800_register_write(rt2x00dev, LDO_CFG0, reg);

	rt2800_rx_filter_calibration(rt2x00dev);
	rt2800_led_open_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
}