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
struct TYPE_2__ {int usb_err; int* usb_buf; int /*<<< orphan*/  dev; } ;
struct sd {TYPE_1__ gspca_dev; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  W9968CF_I2C_BUS_DELAY ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w9968cf_read_sb(struct sd *sd)
{
	int ret;

	if (sd->gspca_dev.usb_err < 0)
		return -1;

	/* We don't use reg_r here, as the w9968cf is special and has 16
	   bit registers instead of 8 bit */
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_rcvctrlpipe(sd->gspca_dev.dev, 0),
			1,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, 0x01, sd->gspca_dev.usb_buf, 2, 500);
	if (ret >= 0) {
		ret = sd->gspca_dev.usb_buf[0] |
		      (sd->gspca_dev.usb_buf[1] << 8);
	} else {
		err("Read SB reg [01] failed");
		sd->gspca_dev.usb_err = ret;
	}

	udelay(W9968CF_I2C_BUS_DELAY);

	return ret;
}