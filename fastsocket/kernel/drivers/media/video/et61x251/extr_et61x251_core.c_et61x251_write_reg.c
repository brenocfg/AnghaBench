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
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct et61x251_device {int /*<<< orphan*/ * control_buffer; struct usb_device* usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ET61X251_CTRL_TIMEOUT ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int et61x251_write_reg(struct et61x251_device* cam, u8 value, u16 index)
{
	struct usb_device* udev = cam->usbdev;
	u8* buff = cam->control_buffer;
	int res;

	*buff = value;

	res = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x00, 0x41,
			      0, index, buff, 1, ET61X251_CTRL_TIMEOUT);
	if (res < 0) {
		DBG(3, "Failed to write a register (value 0x%02X, index "
		       "0x%02X, error %d)", value, index, res);
		return -1;
	}

	return 0;
}