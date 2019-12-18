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
 int /*<<< orphan*/  DIBUSB_IOCTL_CMD_POWER_MODE ; 
 int /*<<< orphan*/  DIBUSB_IOCTL_POWER_SLEEP ; 
 int /*<<< orphan*/  DIBUSB_IOCTL_POWER_WAKEUP ; 
 int /*<<< orphan*/  DIBUSB_REQ_SET_IOCTL ; 
 int dvb_usb_generic_write (struct dvb_usb_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

int dibusb_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	u8 b[3];
	int ret;
	b[0] = DIBUSB_REQ_SET_IOCTL;
	b[1] = DIBUSB_IOCTL_CMD_POWER_MODE;
	b[2] = onoff ? DIBUSB_IOCTL_POWER_WAKEUP : DIBUSB_IOCTL_POWER_SLEEP;
	ret = dvb_usb_generic_write(d,b,3);
	msleep(10);
	return ret;
}