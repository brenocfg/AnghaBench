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

__attribute__((used)) static void spca500_ping310(struct gspca_dev *gspca_dev)
{
	reg_r(gspca_dev, 0x0d04, 2);
	PDEBUG(D_STREAM, "ClickSmart310 ping 0x0d04 0x%02x 0x%02x",
		gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
}