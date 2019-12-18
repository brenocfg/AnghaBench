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
struct dvb_usb_device {scalar_t__ state; int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  bufs ;

/* Variables and functions */
 int CMD_I2C_WRITE ; 
 int CMD_POWER_OFF ; 
 int CMD_POWER_ON ; 
 scalar_t__ DVB_USB_STATE_INIT ; 
 int EREMOTEIO ; 
 int cxusb_ctrl_msg (struct dvb_usb_device*,int,int*,int,int*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxusb_aver_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	int ret;
	if (!onoff)
		return cxusb_ctrl_msg(d, CMD_POWER_OFF, NULL, 0, NULL, 0);
	if (d->state == DVB_USB_STATE_INIT &&
	    usb_set_interface(d->udev, 0, 0) < 0)
		err("set interface failed");
	do {} while (!(ret = cxusb_ctrl_msg(d, CMD_POWER_ON, NULL, 0, NULL, 0)) &&
		   !(ret = cxusb_ctrl_msg(d, 0x15, NULL, 0, NULL, 0)) &&
		   !(ret = cxusb_ctrl_msg(d, 0x17, NULL, 0, NULL, 0)) && 0);
	if (!ret) {
		/* FIXME: We don't know why, but we need to configure the
		 * lgdt3303 with the register settings below on resume */
		int i;
		u8 buf, bufs[] = {
			0x0e, 0x2, 0x00, 0x7f,
			0x0e, 0x2, 0x02, 0xfe,
			0x0e, 0x2, 0x02, 0x01,
			0x0e, 0x2, 0x00, 0x03,
			0x0e, 0x2, 0x0d, 0x40,
			0x0e, 0x2, 0x0e, 0x87,
			0x0e, 0x2, 0x0f, 0x8e,
			0x0e, 0x2, 0x10, 0x01,
			0x0e, 0x2, 0x14, 0xd7,
			0x0e, 0x2, 0x47, 0x88,
		};
		msleep(20);
		for (i = 0; i < sizeof(bufs)/sizeof(u8); i += 4/sizeof(u8)) {
			ret = cxusb_ctrl_msg(d, CMD_I2C_WRITE,
					     bufs+i, 4, &buf, 1);
			if (ret)
				break;
			if (buf != 0x8)
				return -EREMOTEIO;
		}
	}
	return ret;
}