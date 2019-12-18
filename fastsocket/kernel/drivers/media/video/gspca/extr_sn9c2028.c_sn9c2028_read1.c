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
struct gspca_dev {int* usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBI ; 
 int EIO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_GET_STATUS ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sn9c2028_read1(struct gspca_dev *gspca_dev)
{
	int rc;

	rc = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			USB_REQ_GET_STATUS,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			1, 0, gspca_dev->usb_buf, 1, 500);
	if (rc != 1) {
		err("read1 error %d", rc);
		return (rc < 0) ? rc : -EIO;
	}
	PDEBUG(D_USBI, "read1 response %02x", gspca_dev->usb_buf[0]);
	return gspca_dev->usb_buf[0];
}