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
struct gspca_dev {int* usb_buf; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 size_t SHARPNESS ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 

__attribute__((used)) static void setsharpness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_dev->usb_buf[0] = 0x67;
	gspca_dev->usb_buf[1] = sd->ctrls[SHARPNESS].val * 4 + 3;
	reg_w(gspca_dev, 2);
}