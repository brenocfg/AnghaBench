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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ reg_r_12 (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void spca504_wait_status(struct gspca_dev *gspca_dev)
{
	int cnt;

	cnt = 256;
	while (--cnt > 0) {
		/* With this we get the status, when return 0 it's all ok */
		if (reg_r_12(gspca_dev, 0x06, 0x00, 1) == 0)
			return;
		msleep(10);
	}
}