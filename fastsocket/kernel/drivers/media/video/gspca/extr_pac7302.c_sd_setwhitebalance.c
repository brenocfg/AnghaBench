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
struct sd {int /*<<< orphan*/  white_balance; } ;
struct gspca_dev {int usb_err; scalar_t__ streaming; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  setwhitebalance (struct gspca_dev*) ; 

__attribute__((used)) static int sd_setwhitebalance(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->white_balance = val;
	if (gspca_dev->streaming)
		setwhitebalance(gspca_dev);
	return gspca_dev->usb_err;
}