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
 int /*<<< orphan*/  DIBUSB_IOCTL_POWER_WAKEUP ; 
 int /*<<< orphan*/  DIBUSB_REQ_SET_IOCTL ; 
 int dvb_usb_generic_write (struct dvb_usb_device*,int /*<<< orphan*/ *,int) ; 

int dibusb2_0_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	if (onoff) {
		u8 b[3] = { DIBUSB_REQ_SET_IOCTL, DIBUSB_IOCTL_CMD_POWER_MODE, DIBUSB_IOCTL_POWER_WAKEUP };
		return dvb_usb_generic_write(d,b,3);
	} else
		return 0;
}