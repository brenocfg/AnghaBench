#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {scalar_t__ do_ctrl; } ;
struct TYPE_2__ {int bulk_nurbs; } ;
struct gspca_dev {int /*<<< orphan*/ * urb; TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_dq_callback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	if (!sd->do_ctrl || gspca_dev->cam.bulk_nurbs != 0)
		return;
	sd->do_ctrl = 0;

	setexposure(gspca_dev);

	gspca_dev->cam.bulk_nurbs = 1;
	ret = usb_submit_urb(gspca_dev->urb[0], GFP_ATOMIC);
	if (ret < 0)
		err("sd_dq_callback() err %d", ret);

	/* wait a little time, otherwise the webcam crashes */
	msleep(100);
}