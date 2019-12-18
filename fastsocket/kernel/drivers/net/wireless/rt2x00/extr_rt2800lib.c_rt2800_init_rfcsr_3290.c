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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCSR29_RSSI_GAIN ; 
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_3xxx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_3290(struct rt2x00_dev *rt2x00dev)
{
	u8 rfcsr;

	rt2800_rf_init_calibration(rt2x00dev, 2);

	rt2800_rfcsr_write(rt2x00dev, 1, 0x0f);
	rt2800_rfcsr_write(rt2x00dev, 2, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_write(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 6, 0xa0);
	rt2800_rfcsr_write(rt2x00dev, 8, 0xf3);
	rt2800_rfcsr_write(rt2x00dev, 9, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 10, 0x53);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x4a);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x46);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x9f);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x83);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x82);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x09);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 34, 0x05);
	rt2800_rfcsr_write(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_write(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 38, 0x85);
	rt2800_rfcsr_write(rt2x00dev, 39, 0x1b);
	rt2800_rfcsr_write(rt2x00dev, 40, 0x0b);
	rt2800_rfcsr_write(rt2x00dev, 41, 0xbb);
	rt2800_rfcsr_write(rt2x00dev, 42, 0xd5);
	rt2800_rfcsr_write(rt2x00dev, 43, 0x7b);
	rt2800_rfcsr_write(rt2x00dev, 44, 0x0e);
	rt2800_rfcsr_write(rt2x00dev, 45, 0xa2);
	rt2800_rfcsr_write(rt2x00dev, 46, 0x73);
	rt2800_rfcsr_write(rt2x00dev, 47, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 48, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 49, 0x98);
	rt2800_rfcsr_write(rt2x00dev, 52, 0x38);
	rt2800_rfcsr_write(rt2x00dev, 53, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 54, 0x78);
	rt2800_rfcsr_write(rt2x00dev, 55, 0x43);
	rt2800_rfcsr_write(rt2x00dev, 56, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 57, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 58, 0x7f);
	rt2800_rfcsr_write(rt2x00dev, 59, 0x09);
	rt2800_rfcsr_write(rt2x00dev, 60, 0x45);
	rt2800_rfcsr_write(rt2x00dev, 61, 0xc1);

	rt2800_rfcsr_read(rt2x00dev, 29, &rfcsr);
	rt2x00_set_field8(&rfcsr, RFCSR29_RSSI_GAIN, 3);
	rt2800_rfcsr_write(rt2x00dev, 29, rfcsr);

	rt2800_led_open_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
}