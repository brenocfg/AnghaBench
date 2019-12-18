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
typedef  int u16 ;
struct sd {size_t sensor; void* green_gain; void* blue_gain; void* red_gain; int /*<<< orphan*/  awb; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int reg80; } ;

/* Variables and functions */
 void* reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 TYPE_1__* sensor_data ; 

__attribute__((used)) static void setawb(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u16 reg80;

	reg80 = (sensor_data[sd->sensor].reg80 << 8) | 0x80;

	/* on awb leave defaults values */
	if (!sd->awb) {
		/* shoud we wait here.. */
		/* update and reset RGB gains with webcam values */
		sd->red_gain = reg_r(gspca_dev, 0x0087);
		sd->blue_gain = reg_r(gspca_dev, 0x0088);
		sd->green_gain = reg_r(gspca_dev, 0x0089);
		reg80 &= ~0x0400;		/* AWB off */
	}
	reg_w(gspca_dev, reg80);
	reg_w(gspca_dev, reg80);
}