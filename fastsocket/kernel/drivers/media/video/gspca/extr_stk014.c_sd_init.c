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
struct gspca_dev {int usb_err; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	u8 ret;

	/* check if the device responds */
	usb_set_interface(gspca_dev->dev, gspca_dev->iface, 1);
	ret = reg_r(gspca_dev, 0x0740);
	if (gspca_dev->usb_err >= 0) {
		if (ret != 0xff) {
			err("init reg: 0x%02x", ret);
			gspca_dev->usb_err = -EIO;
		}
	}
	return gspca_dev->usb_err;
}