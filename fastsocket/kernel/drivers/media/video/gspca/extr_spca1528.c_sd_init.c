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
struct gspca_dev {int usb_err; int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	reg_w(gspca_dev, 0x00, 0x0001, 0x2067);
	reg_w(gspca_dev, 0x00, 0x00d0, 0x206b);
	reg_w(gspca_dev, 0x00, 0x0000, 0x206c);
	reg_w(gspca_dev, 0x00, 0x0001, 0x2069);
	msleep(8);
	reg_w(gspca_dev, 0x00, 0x00c0, 0x206b);
	reg_w(gspca_dev, 0x00, 0x0000, 0x206c);
	reg_w(gspca_dev, 0x00, 0x0001, 0x2069);

	reg_r(gspca_dev, 0x20, 0x0000, 1);
	reg_r(gspca_dev, 0x20, 0x0000, 5);
	reg_r(gspca_dev, 0x23, 0x0000, 64);
	PDEBUG(D_PROBE, "%s%s", &gspca_dev->usb_buf[0x1c],
				&gspca_dev->usb_buf[0x30]);
	reg_r(gspca_dev, 0x23, 0x0001, 64);
	return gspca_dev->usb_err;
}