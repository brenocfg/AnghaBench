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
 int EIO ; 
 scalar_t__ rt73usb_init_bbp (struct rt2x00_dev*) ; 
 scalar_t__ rt73usb_init_registers (struct rt2x00_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rt73usb_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	/*
	 * Initialize all registers.
	 */
	if (unlikely(rt73usb_init_registers(rt2x00dev) ||
		     rt73usb_init_bbp(rt2x00dev)))
		return -EIO;

	return 0;
}