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
struct gspca_dev {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reg_w (struct usb_device*,int,int,int) ; 
 int /*<<< orphan*/  spca506_Initi2c (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca506_SetNormeInput (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spca506_WriteI2c (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct usb_device *dev = gspca_dev->dev;

	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0xFF, 0x0003);
	reg_w(dev, 0x03, 0x00, 0x0000);
	reg_w(dev, 0x03, 0x1c, 0x0001);
	reg_w(dev, 0x03, 0x18, 0x0001);
	/* Init on PAL and composite input0 */
	spca506_SetNormeInput(gspca_dev, 0, 0);
	reg_w(dev, 0x03, 0x1c, 0x0001);
	reg_w(dev, 0x03, 0x18, 0x0001);
	reg_w(dev, 0x05, 0x00, 0x0000);
	reg_w(dev, 0x05, 0xef, 0x0001);
	reg_w(dev, 0x05, 0x00, 0x00c1);
	reg_w(dev, 0x05, 0x00, 0x00c2);
	reg_w(dev, 0x06, 0x18, 0x0002);
	reg_w(dev, 0x06, 0xf5, 0x0011);
	reg_w(dev, 0x06, 0x02, 0x0012);
	reg_w(dev, 0x06, 0xfb, 0x0013);
	reg_w(dev, 0x06, 0x00, 0x0014);
	reg_w(dev, 0x06, 0xa4, 0x0051);
	reg_w(dev, 0x06, 0x40, 0x0052);
	reg_w(dev, 0x06, 0x71, 0x0053);
	reg_w(dev, 0x06, 0x40, 0x0054);
	/************************************************/
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0x00, 0x0003);
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0xFF, 0x0003);
	reg_w(dev, 0x02, 0x00, 0x0000);
	reg_w(dev, 0x03, 0x60, 0x0000);
	reg_w(dev, 0x03, 0x18, 0x0001);
	/* for a better reading mx :)	  */
	/*sdca506_WriteI2c(value,register) */
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, 0x08, 0x01);
	spca506_WriteI2c(gspca_dev, 0xc0, 0x02);
						/* input composite video */
	spca506_WriteI2c(gspca_dev, 0x33, 0x03);
	spca506_WriteI2c(gspca_dev, 0x00, 0x04);
	spca506_WriteI2c(gspca_dev, 0x00, 0x05);
	spca506_WriteI2c(gspca_dev, 0x0d, 0x06);
	spca506_WriteI2c(gspca_dev, 0xf0, 0x07);
	spca506_WriteI2c(gspca_dev, 0x98, 0x08);
	spca506_WriteI2c(gspca_dev, 0x03, 0x09);
	spca506_WriteI2c(gspca_dev, 0x80, 0x0a);
	spca506_WriteI2c(gspca_dev, 0x47, 0x0b);
	spca506_WriteI2c(gspca_dev, 0x48, 0x0c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x0d);
	spca506_WriteI2c(gspca_dev, 0x03, 0x0e);	/* Chroma Pal adjust */
	spca506_WriteI2c(gspca_dev, 0x2a, 0x0f);
	spca506_WriteI2c(gspca_dev, 0x00, 0x10);
	spca506_WriteI2c(gspca_dev, 0x0c, 0x11);
	spca506_WriteI2c(gspca_dev, 0xb8, 0x12);
	spca506_WriteI2c(gspca_dev, 0x01, 0x13);
	spca506_WriteI2c(gspca_dev, 0x00, 0x14);
	spca506_WriteI2c(gspca_dev, 0x00, 0x15);
	spca506_WriteI2c(gspca_dev, 0x00, 0x16);
	spca506_WriteI2c(gspca_dev, 0x00, 0x17);
	spca506_WriteI2c(gspca_dev, 0x00, 0x18);
	spca506_WriteI2c(gspca_dev, 0x00, 0x19);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1a);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1b);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1d);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1e);
	spca506_WriteI2c(gspca_dev, 0xa1, 0x1f);
	spca506_WriteI2c(gspca_dev, 0x02, 0x40);
	spca506_WriteI2c(gspca_dev, 0xff, 0x41);
	spca506_WriteI2c(gspca_dev, 0xff, 0x42);
	spca506_WriteI2c(gspca_dev, 0xff, 0x43);
	spca506_WriteI2c(gspca_dev, 0xff, 0x44);
	spca506_WriteI2c(gspca_dev, 0xff, 0x45);
	spca506_WriteI2c(gspca_dev, 0xff, 0x46);
	spca506_WriteI2c(gspca_dev, 0xff, 0x47);
	spca506_WriteI2c(gspca_dev, 0xff, 0x48);
	spca506_WriteI2c(gspca_dev, 0xff, 0x49);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4a);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4b);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4c);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4d);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4e);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4f);
	spca506_WriteI2c(gspca_dev, 0xff, 0x50);
	spca506_WriteI2c(gspca_dev, 0xff, 0x51);
	spca506_WriteI2c(gspca_dev, 0xff, 0x52);
	spca506_WriteI2c(gspca_dev, 0xff, 0x53);
	spca506_WriteI2c(gspca_dev, 0xff, 0x54);
	spca506_WriteI2c(gspca_dev, 0xff, 0x55);
	spca506_WriteI2c(gspca_dev, 0xff, 0x56);
	spca506_WriteI2c(gspca_dev, 0xff, 0x57);
	spca506_WriteI2c(gspca_dev, 0x00, 0x58);
	spca506_WriteI2c(gspca_dev, 0x54, 0x59);
	spca506_WriteI2c(gspca_dev, 0x07, 0x5a);
	spca506_WriteI2c(gspca_dev, 0x83, 0x5b);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5d);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5e);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5f);
	spca506_WriteI2c(gspca_dev, 0x00, 0x60);
	spca506_WriteI2c(gspca_dev, 0x05, 0x61);
	spca506_WriteI2c(gspca_dev, 0x9f, 0x62);
	PDEBUG(D_STREAM, "** Close Init *");
	return 0;
}