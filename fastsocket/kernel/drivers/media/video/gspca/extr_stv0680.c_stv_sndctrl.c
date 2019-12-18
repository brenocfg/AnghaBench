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
typedef  int /*<<< orphan*/  u16 ;
struct gspca_dev {int /*<<< orphan*/  usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int,int,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv_sndctrl(struct gspca_dev *gspca_dev, int set, u8 req, u16 val,
		       int size)
{
	int ret = -1;
	u8 req_type = 0;
	unsigned int pipe = 0;

	switch (set) {
	case 0: /*  0xc1  */
		req_type = USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_ENDPOINT;
		pipe = usb_rcvctrlpipe(gspca_dev->dev, 0);
		break;
	case 1: /*  0x41  */
		req_type = USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_ENDPOINT;
		pipe = usb_sndctrlpipe(gspca_dev->dev, 0);
		break;
	case 2:	/*  0x80  */
		req_type = USB_DIR_IN | USB_RECIP_DEVICE;
		pipe = usb_rcvctrlpipe(gspca_dev->dev, 0);
		break;
	case 3:	/*  0x40  */
		req_type = USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
		pipe = usb_sndctrlpipe(gspca_dev->dev, 0);
		break;
	}

	ret = usb_control_msg(gspca_dev->dev, pipe,
			      req, req_type,
			      val, 0, gspca_dev->usb_buf, size, 500);

	if ((ret < 0) && (req != 0x0a))
		err("usb_control_msg error %i, request = 0x%x, error = %i",
		       set, req, ret);

	return ret;
}