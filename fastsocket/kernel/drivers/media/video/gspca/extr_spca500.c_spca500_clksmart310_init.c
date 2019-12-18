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
struct gspca_dev {int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  spca500_ping310 (struct gspca_dev*) ; 

__attribute__((used)) static void spca500_clksmart310_init(struct gspca_dev *gspca_dev)
{
	reg_r(gspca_dev, 0x0d05, 2);
	PDEBUG(D_STREAM, "ClickSmart310 init 0x0d05 0x%02x 0x%02x",
		gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	reg_w(gspca_dev, 0x00, 0x8167, 0x5a);
	spca500_ping310(gspca_dev);

	reg_w(gspca_dev, 0x00, 0x8168, 0x22);
	reg_w(gspca_dev, 0x00, 0x816a, 0xc0);
	reg_w(gspca_dev, 0x00, 0x816b, 0x0b);
	reg_w(gspca_dev, 0x00, 0x8169, 0x25);
	reg_w(gspca_dev, 0x00, 0x8157, 0x5b);
	reg_w(gspca_dev, 0x00, 0x8158, 0x5b);
	reg_w(gspca_dev, 0x00, 0x813f, 0x03);
	reg_w(gspca_dev, 0x00, 0x8151, 0x4a);
	reg_w(gspca_dev, 0x00, 0x8153, 0x78);
	reg_w(gspca_dev, 0x00, 0x0d01, 0x04);
						/* 00 for adjust shutter */
	reg_w(gspca_dev, 0x00, 0x0d02, 0x01);
	reg_w(gspca_dev, 0x00, 0x8169, 0x25);
	reg_w(gspca_dev, 0x00, 0x0d01, 0x02);
}