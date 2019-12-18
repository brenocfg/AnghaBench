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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REV_RT5592C ; 
 int /*<<< orphan*/  RT5592 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_adjust_freq_offset (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_5xxx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_rt_rev_gte (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev_lt (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_init_rfcsr_5592(struct rt2x00_dev *rt2x00dev)
{
	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_write(rt2x00dev, 1, 0x3F);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 6, 0xE4);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 16, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x4D);
	rt2800_rfcsr_write(rt2x00dev, 20, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 21, 0x8D);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x82);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 33, 0xC0);
	rt2800_rfcsr_write(rt2x00dev, 34, 0x07);
	rt2800_rfcsr_write(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_write(rt2x00dev, 47, 0x0C);
	rt2800_rfcsr_write(rt2x00dev, 53, 0x22);
	rt2800_rfcsr_write(rt2x00dev, 63, 0x07);

	rt2800_rfcsr_write(rt2x00dev, 2, 0x80);
	msleep(1);

	rt2800_adjust_freq_offset(rt2x00dev);

	/* Enable DC filter */
	if (rt2x00_rt_rev_gte(rt2x00dev, RT5592, REV_RT5592C))
		rt2800_bbp_write(rt2x00dev, 103, 0xc0);

	rt2800_normal_mode_setup_5xxx(rt2x00dev);

	if (rt2x00_rt_rev_lt(rt2x00dev, RT5592, REV_RT5592C))
		rt2800_rfcsr_write(rt2x00dev, 27, 0x03);

	rt2800_led_open_drain_enable(rt2x00dev);
}