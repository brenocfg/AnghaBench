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
struct sd {TYPE_1__* ctrls; } ;
struct gspca_dev {int ctrl_inac; int* usb_buf; } ;
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 int ILLUM_BOT ; 
 int ILLUM_TOP ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  setilluminators (struct gspca_dev*) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_dev->ctrl_inac = (1 << ILLUM_TOP) | (1 << ILLUM_BOT);
	if (sd->ctrls[ILLUM_TOP].val || sd->ctrls[ILLUM_BOT].val) {
		sd->ctrls[ILLUM_TOP].val = 0;
		sd->ctrls[ILLUM_BOT].val = 0;
		setilluminators(gspca_dev);
		msleep(20);
	}

	gspca_dev->usb_buf[0] = 1;
	gspca_dev->usb_buf[1] = 0;
	reg_w(gspca_dev, 2);
}