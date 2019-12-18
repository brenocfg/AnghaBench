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
typedef  int u8 ;
struct gspca_dev {int dummy; } ;
struct sd {int sensor; struct gspca_dev gspca_dev; TYPE_1__* ctrls; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 size_t HFLIP ; 
#define  SENSOR_HV7131R 131 
#define  SENSOR_OV7630 130 
#define  SENSOR_OV7648 129 
#define  SENSOR_PO2030N 128 
 size_t VFLIP ; 
 int /*<<< orphan*/  i2c_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sethvflip(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 comn;

	switch (sd->sensor) {
	case SENSOR_HV7131R:
		comn = 0x18;			/* clkdiv = 1, ablcen = 1 */
		if (sd->ctrls[VFLIP].val)
			comn |= 0x01;
		i2c_w1(gspca_dev, 0x01, comn);	/* sctra */
		break;
	case SENSOR_OV7630:
		comn = 0x02;
		if (!sd->ctrls[VFLIP].val)
			comn |= 0x80;
		i2c_w1(gspca_dev, 0x75, comn);
		break;
	case SENSOR_OV7648:
		comn = 0x06;
		if (sd->ctrls[VFLIP].val)
			comn |= 0x80;
		i2c_w1(gspca_dev, 0x75, comn);
		break;
	case SENSOR_PO2030N:
		/* Reg. 0x1E: Timing Generator Control Register 2 (Tgcontrol2)
		 * (reset value: 0x0A)
		 * bit7: HM: Horizontal Mirror: 0: disable, 1: enable
		 * bit6: VM: Vertical Mirror: 0: disable, 1: enable
		 * bit5: ST: Shutter Selection: 0: electrical, 1: mechanical
		 * bit4: FT: Single Frame Transfer: 0: disable, 1: enable
		 * bit3-0: X
		 */
		comn = 0x0a;
		if (sd->ctrls[HFLIP].val)
			comn |= 0x80;
		if (sd->ctrls[VFLIP].val)
			comn |= 0x40;
		i2c_w1(&sd->gspca_dev, 0x1e, comn);
		break;
	}
}