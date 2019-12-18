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
struct gspca_dev {int* usb_buf; int /*<<< orphan*/  usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_wb (struct gspca_dev*,int,int,int,int) ; 

__attribute__((used)) static void wait_status_1(struct gspca_dev *gspca_dev)
{
	int i;

	i = 10;
	do {
		reg_r(gspca_dev, 0x21, 0x0001, 1);
		msleep(10);
		if (gspca_dev->usb_buf[0] == 1) {
			reg_wb(gspca_dev, 0x21, 0x0000, 0x0001, 0x00);
			reg_r(gspca_dev, 0x21, 0x0001, 1);
			return;
		}
	} while (--i > 0);
	PDEBUG(D_ERR, "wait_status_1 timeout");
	gspca_dev->usb_err = -ETIME;
}