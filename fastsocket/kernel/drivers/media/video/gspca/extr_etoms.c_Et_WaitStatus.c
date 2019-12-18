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
 int /*<<< orphan*/  ET_ClCK ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int Et_WaitStatus(struct gspca_dev *gspca_dev)
{
	int retry = 10;

	while (retry--) {
		reg_r(gspca_dev, ET_ClCK, 1);
		if (gspca_dev->usb_buf[0] != 0)
			return 1;
	}
	return 0;
}