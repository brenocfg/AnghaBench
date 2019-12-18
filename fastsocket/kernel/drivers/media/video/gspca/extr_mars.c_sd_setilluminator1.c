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
struct gspca_dev {int usb_err; } ;
typedef  scalar_t__ __s32 ;
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 size_t ILLUM_BOT ; 
 size_t ILLUM_TOP ; 
 int /*<<< orphan*/  setilluminators (struct gspca_dev*) ; 

__attribute__((used)) static int sd_setilluminator1(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* only one illuminator may be on */
	sd->ctrls[ILLUM_TOP].val = val;
	if (val)
		sd->ctrls[ILLUM_BOT].val = 0;
	setilluminators(gspca_dev);
	return gspca_dev->usb_err;
}