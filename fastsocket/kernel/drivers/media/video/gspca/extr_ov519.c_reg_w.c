#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int usb_err; int /*<<< orphan*/ * usb_buf; int /*<<< orphan*/  dev; } ;
struct sd {int bridge; TYPE_1__ gspca_dev; } ;

/* Variables and functions */
#define  BRIDGE_OV511 131 
#define  BRIDGE_OV511PLUS 130 
#define  BRIDGE_OVFX2 129 
#define  BRIDGE_W9968CF 128 
 int /*<<< orphan*/  D_USBO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w(struct sd *sd, u16 index, u16 value)
{
	int ret, req = 0;

	if (sd->gspca_dev.usb_err < 0)
		return;

	switch (sd->bridge) {
	case BRIDGE_OV511:
	case BRIDGE_OV511PLUS:
		req = 2;
		break;
	case BRIDGE_OVFX2:
		req = 0x0a;
		/* fall through */
	case BRIDGE_W9968CF:
		PDEBUG(D_USBO, "SET %02x %04x %04x",
				req, value, index);
		ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, NULL, 0, 500);
		goto leave;
	default:
		req = 1;
	}

	PDEBUG(D_USBO, "SET %02x 0000 %04x %02x",
			req, index, value);
	sd->gspca_dev.usb_buf[0] = value;
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index,
			sd->gspca_dev.usb_buf, 1, 500);
leave:
	if (ret < 0) {
		err("reg_w %02x failed %d", index, ret);
		sd->gspca_dev.usb_err = ret;
		return;
	}
}