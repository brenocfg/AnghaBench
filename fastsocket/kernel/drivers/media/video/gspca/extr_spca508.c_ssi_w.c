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
typedef  int u16 ;
struct usb_device {int dummy; } ;
struct gspca_dev {scalar_t__* usb_buf; struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int reg_read (struct gspca_dev*,int) ; 
 int reg_write (struct usb_device*,int,int) ; 

__attribute__((used)) static int ssi_w(struct gspca_dev *gspca_dev,
		u16 reg, u16 val)
{
	struct usb_device *dev = gspca_dev->dev;
	int ret, retry;

	ret = reg_write(dev, 0x8802, reg >> 8);
	if (ret < 0)
		goto out;
	ret = reg_write(dev, 0x8801, reg & 0x00ff);
	if (ret < 0)
		goto out;
	if ((reg & 0xff00) == 0x1000) {		/* if 2 bytes */
		ret = reg_write(dev, 0x8805, val & 0x00ff);
		if (ret < 0)
			goto out;
		val >>= 8;
	}
	ret = reg_write(dev, 0x8800, val);
	if (ret < 0)
		goto out;

	/* poll until not busy */
	retry = 10;
	for (;;) {
		ret = reg_read(gspca_dev, 0x8803);
		if (ret < 0)
			break;
		if (gspca_dev->usb_buf[0] == 0)
			break;
		if (--retry <= 0) {
			PDEBUG(D_ERR, "ssi_w busy %02x",
					gspca_dev->usb_buf[0]);
			ret = -1;
			break;
		}
		msleep(8);
	}

out:
	return ret;
}