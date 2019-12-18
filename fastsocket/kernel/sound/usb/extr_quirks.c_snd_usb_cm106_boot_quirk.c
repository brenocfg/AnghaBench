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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int snd_usb_cm106_write_int_reg (struct usb_device*,int,int) ; 

__attribute__((used)) static int snd_usb_cm106_boot_quirk(struct usb_device *dev)
{
	/*
	 * Enable line-out driver mode, set headphone source to front
	 * channels, enable stereo mic.
	 */
	return snd_usb_cm106_write_int_reg(dev, 2, 0x8004);
}