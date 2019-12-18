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
struct gspca_dev {scalar_t__* usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_w_1 (struct gspca_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spca504B_PollingDataReady (struct gspca_dev*) ; 

__attribute__((used)) static void spca504B_WaitCmdStatus(struct gspca_dev *gspca_dev)
{
	int count = 50;

	while (--count > 0) {
		reg_r(gspca_dev, 0x21, 1, 1);
		if (gspca_dev->usb_buf[0] != 0) {
			reg_w_1(gspca_dev, 0x21, 0, 1, 0);
			reg_r(gspca_dev, 0x21, 1, 1);
			spca504B_PollingDataReady(gspca_dev);
			break;
		}
		msleep(10);
	}
}