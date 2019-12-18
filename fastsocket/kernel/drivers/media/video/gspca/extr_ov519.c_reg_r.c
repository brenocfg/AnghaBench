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
struct TYPE_2__ {int usb_err; int* usb_buf; int /*<<< orphan*/  dev; } ;
struct sd {int bridge; TYPE_1__ gspca_dev; } ;

/* Variables and functions */
#define  BRIDGE_OV511 130 
#define  BRIDGE_OV511PLUS 129 
#define  BRIDGE_OVFX2 128 
 int /*<<< orphan*/  D_USBI ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_r(struct sd *sd, u16 index)
{
	int ret;
	int req;

	if (sd->gspca_dev.usb_err < 0)
		return -1;

	switch (sd->bridge) {
	case BRIDGE_OV511:
	case BRIDGE_OV511PLUS:
		req = 3;
		break;
	case BRIDGE_OVFX2:
		req = 0x0b;
		break;
	default:
		req = 1;
	}

	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_rcvctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index, sd->gspca_dev.usb_buf, 1, 500);

	if (ret >= 0) {
		ret = sd->gspca_dev.usb_buf[0];
		PDEBUG(D_USBI, "GET %02x 0000 %04x %02x",
			req, index, ret);
	} else {
		err("reg_r %02x failed %d", index, ret);
		sd->gspca_dev.usb_err = ret;
	}

	return ret;
}