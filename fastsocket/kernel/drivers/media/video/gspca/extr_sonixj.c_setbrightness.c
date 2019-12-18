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
struct sd {int sensor; void* exposure; TYPE_1__* ctrls; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 size_t BRIGHTNESS ; 
#define  SENSOR_ADCM1700 135 
#define  SENSOR_GC0307 134 
#define  SENSOR_HV7131R 133 
#define  SENSOR_MI0360 132 
#define  SENSOR_MI0360B 131 
#define  SENSOR_MO4000 130 
#define  SENSOR_MT9V111 129 
#define  SENSOR_OM6802 128 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 
 void* setexposure (struct gspca_dev*,unsigned int) ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	unsigned int expo;
	int brightness;
	u8 k2;

	brightness = sd->ctrls[BRIGHTNESS].val;
	k2 = (brightness - 0x80) >> 2;
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
		if (k2 > 0x1f)
			k2 = 0;		/* only positive Y offset */
		break;
	case SENSOR_HV7131R:
		expo = brightness << 12;
		if (expo > 0x002dc6c0)
			expo = 0x002dc6c0;
		else if (expo < 0x02a0)
			expo = 0x02a0;
		sd->exposure = setexposure(gspca_dev, expo);
		break;
	case SENSOR_MI0360:
	case SENSOR_MO4000:
		expo = brightness << 4;
		sd->exposure = setexposure(gspca_dev, expo);
		break;
	case SENSOR_MI0360B:
		expo = brightness << 2;
		sd->exposure = setexposure(gspca_dev, expo);
		break;
	case SENSOR_GC0307:
	case SENSOR_MT9V111:
		expo = brightness;
		sd->exposure = setexposure(gspca_dev, expo);
		return;			/* don't set the Y offset */
	case SENSOR_OM6802:
		expo = brightness << 2;
		sd->exposure = setexposure(gspca_dev, expo);
		k2 = brightness >> 3;
		break;
	}

	reg_w1(gspca_dev, 0x96, k2);	/* color matrix Y offset */
}