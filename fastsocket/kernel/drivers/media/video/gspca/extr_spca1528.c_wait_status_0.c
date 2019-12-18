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
struct gspca_dev {scalar_t__* usb_buf; int /*<<< orphan*/  usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void wait_status_0(struct gspca_dev *gspca_dev)
{
	int i;

	i = 20;
	do {
		reg_r(gspca_dev, 0x21, 0x0000, 1);
		if (gspca_dev->usb_buf[0] == 0)
			return;
		msleep(30);
	} while (--i > 0);
	PDEBUG(D_ERR, "wait_status_0 timeout");
	gspca_dev->usb_err = -ETIME;
}