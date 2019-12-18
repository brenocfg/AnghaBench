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
struct gspca_dev {int /*<<< orphan*/ * usb_buf; struct usb_device* dev; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBI ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_BUF_SZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_r(struct gspca_dev *gspca_dev,
		  __u16 index,
		  __u16 len)
{
	struct usb_device *dev = gspca_dev->dev;

#ifdef GSPCA_DEBUG
	if (len > USB_BUF_SZ) {
		err("reg_r: buffer overflow");
		return;
	}
#endif
	usb_control_msg(dev,
			usb_rcvctrlpipe(dev, 0),
			0,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0,
			index, gspca_dev->usb_buf, len, 500);
	PDEBUG(D_USBI, "reg read [%02x] -> %02x ..",
			index, gspca_dev->usb_buf[0]);
}