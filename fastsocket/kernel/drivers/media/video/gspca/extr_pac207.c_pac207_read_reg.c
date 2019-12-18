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
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct gspca_dev {int* usb_buf; struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAC207_CTRL_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pac207_read_reg(struct gspca_dev *gspca_dev, u16 index)
{
	struct usb_device *udev = gspca_dev->dev;
	int res;

	res = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x00,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0x00, index,
			gspca_dev->usb_buf, 1, PAC207_CTRL_TIMEOUT);
	if (res < 0) {
		err("Failed to read a register (index 0x%04X, error %d)",
			index, res);
		return res;
	}

	return gspca_dev->usb_buf[0];
}