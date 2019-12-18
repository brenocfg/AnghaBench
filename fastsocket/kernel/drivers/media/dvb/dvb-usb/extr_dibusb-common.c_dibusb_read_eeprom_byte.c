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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int dibusb_i2c_msg (struct dvb_usb_device*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

int dibusb_read_eeprom_byte(struct dvb_usb_device *d, u8 offs, u8 *val)
{
	u8 wbuf[1] = { offs };
	return dibusb_i2c_msg(d, 0x50, wbuf, 1, val, 1);
}