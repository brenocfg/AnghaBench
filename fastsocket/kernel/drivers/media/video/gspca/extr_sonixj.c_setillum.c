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
struct sd {int sensor; TYPE_1__* ctrls; } ;
struct gspca_dev {int ctrl_dis; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int ILLUM ; 
#define  SENSOR_ADCM1700 129 
#define  SENSOR_MT9V111 128 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  starcam ; 

__attribute__((used)) static void setillum(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (gspca_dev->ctrl_dis & (1 << ILLUM))
		return;
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
		reg_w1(gspca_dev, 0x02,				/* gpio */
			sd->ctrls[ILLUM].val ? 0x64 : 0x60);
		break;
	case SENSOR_MT9V111:
		if (starcam)
			reg_w1(gspca_dev, 0x02,
				sd->ctrls[ILLUM].val ?
						0x55 : 0x54);	/* 370i */
		else
			reg_w1(gspca_dev, 0x02,
				sd->ctrls[ILLUM].val ?
						0x66 : 0x64);	/* Clip */
		break;
	}
}