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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_SWITCH ; 
 int /*<<< orphan*/  GPIO_SWITCH_5 ; 
 int /*<<< orphan*/  REV_RT3390E ; 
 int /*<<< orphan*/  RT3390 ; 
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_3xxx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rx_filter_calibration (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt_rev_lt (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_init_rfcsr_3390(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_write(rt2x00dev, 0, 0xa0);
	rt2800_rfcsr_write(rt2x00dev, 1, 0xe1);
	rt2800_rfcsr_write(rt2x00dev, 2, 0xf1);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x62);
	rt2800_rfcsr_write(rt2x00dev, 4, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x8b);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x42);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x34);
	rt2800_rfcsr_write(rt2x00dev, 8, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 9, 0xc0);
	rt2800_rfcsr_write(rt2x00dev, 10, 0x61);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x21);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x3b);
	rt2800_rfcsr_write(rt2x00dev, 13, 0xe0);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x90);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x53);
	rt2800_rfcsr_write(rt2x00dev, 16, 0xe0);
	rt2800_rfcsr_write(rt2x00dev, 17, 0x94);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x5c);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x4a);
	rt2800_rfcsr_write(rt2x00dev, 20, 0xb2);
	rt2800_rfcsr_write(rt2x00dev, 21, 0xf6);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 23, 0x14);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x08);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x3d);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x85);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x41);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x8f);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x0f);

	rt2800_register_read(rt2x00dev, GPIO_SWITCH, &reg);
	rt2x00_set_field32(&reg, GPIO_SWITCH_5, 0);
	rt2800_register_write(rt2x00dev, GPIO_SWITCH, reg);

	rt2800_rx_filter_calibration(rt2x00dev);

	if (rt2x00_rt_rev_lt(rt2x00dev, RT3390, REV_RT3390E))
		rt2800_rfcsr_write(rt2x00dev, 27, 0x03);

	rt2800_led_open_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
}