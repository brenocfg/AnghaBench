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
typedef  void* u8 ;
struct sd {int sensor; int i2c_addr; } ;
struct gspca_dev {int usb_err; int* usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,void*,void*) ; 
#define  SENSOR_ADCM1700 130 
#define  SENSOR_GC0307 129 
#define  SENSOR_OM6802 128 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_w1(struct gspca_dev *gspca_dev, u8 reg, u8 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	if (gspca_dev->usb_err < 0)
		return;
	PDEBUG(D_USBO, "i2c_w1 [%02x] = %02x", reg, val);
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
	case SENSOR_OM6802:
	case SENSOR_GC0307:		/* i2c command = a0 (100 kHz) */
		gspca_dev->usb_buf[0] = 0x80 | (2 << 4);
		break;
	default:			/* i2c command = a1 (400 kHz) */
		gspca_dev->usb_buf[0] = 0x81 | (2 << 4);
		break;
	}
	gspca_dev->usb_buf[1] = sd->i2c_addr;
	gspca_dev->usb_buf[2] = reg;
	gspca_dev->usb_buf[3] = val;
	gspca_dev->usb_buf[4] = 0;
	gspca_dev->usb_buf[5] = 0;
	gspca_dev->usb_buf[6] = 0;
	gspca_dev->usb_buf[7] = 0x10;
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x08,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0x08,			/* value = i2c */
			0,
			gspca_dev->usb_buf, 8,
			500);
	if (ret < 0) {
		err("i2c_w1 err %d", ret);
		gspca_dev->usb_err = ret;
	}
}