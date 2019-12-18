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
struct sd {unsigned char gain; int sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;
struct TYPE_2__ {int sensor_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
#define  SENSOR_HV7131D 135 
#define  SENSOR_OV6650 134 
#define  SENSOR_OV7630 133 
#define  SENSOR_PAS106 132 
#define  SENSOR_PAS202 131 
#define  SENSOR_TAS5110C 130 
#define  SENSOR_TAS5110D 129 
#define  SENSOR_TAS5130CXX 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 
 TYPE_1__* sensor_data ; 

__attribute__((used)) static void setsensorgain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	unsigned char gain = sd->gain;

	switch (sd->sensor) {
	case SENSOR_HV7131D: {
		__u8 i2c[] =
			{0xc0, 0x11, 0x31, 0x00, 0x00, 0x00, 0x00, 0x17};

		i2c[3] = 0x3f - (sd->gain / 4);
		i2c[4] = 0x3f - (sd->gain / 4);
		i2c[5] = 0x3f - (sd->gain / 4);

		if (i2c_w(gspca_dev, i2c) < 0)
			goto err;
		break;
	    }
	case SENSOR_TAS5110C:
	case SENSOR_TAS5130CXX: {
		__u8 i2c[] =
			{0x30, 0x11, 0x02, 0x20, 0x70, 0x00, 0x00, 0x10};

		i2c[4] = 255 - gain;
		if (i2c_w(gspca_dev, i2c) < 0)
			goto err;
		break;
	    }
	case SENSOR_TAS5110D: {
		__u8 i2c[] = {
			0xb0, 0x61, 0x02, 0x00, 0x10, 0x00, 0x00, 0x17 };
		gain = 255 - gain;
		/* The bits in the register are the wrong way around!! */
		i2c[3] |= (gain & 0x80) >> 7;
		i2c[3] |= (gain & 0x40) >> 5;
		i2c[3] |= (gain & 0x20) >> 3;
		i2c[3] |= (gain & 0x10) >> 1;
		i2c[3] |= (gain & 0x08) << 1;
		i2c[3] |= (gain & 0x04) << 3;
		i2c[3] |= (gain & 0x02) << 5;
		i2c[3] |= (gain & 0x01) << 7;
		if (i2c_w(gspca_dev, i2c) < 0)
			goto err;
		break;
	    }

	case SENSOR_OV6650:
		gain >>= 1;
		/* fall thru */
	case SENSOR_OV7630: {
		__u8 i2c[] = {0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10};

		i2c[1] = sensor_data[sd->sensor].sensor_addr;
		i2c[3] = gain >> 2;
		if (i2c_w(gspca_dev, i2c) < 0)
			goto err;
		break;
	    }
	case SENSOR_PAS106:
	case SENSOR_PAS202: {
		__u8 i2cpgain[] =
			{0xa0, 0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x15};
		__u8 i2cpcolorgain[] =
			{0xc0, 0x40, 0x07, 0x00, 0x00, 0x00, 0x00, 0x15};
		__u8 i2cpdoit[] =
			{0xa0, 0x40, 0x11, 0x01, 0x00, 0x00, 0x00, 0x16};

		/* PAS106 uses different regs (and has split green gains) */
		if (sd->sensor == SENSOR_PAS106) {
			i2cpgain[2] = 0x0e;
			i2cpcolorgain[0] = 0xd0;
			i2cpcolorgain[2] = 0x09;
			i2cpdoit[2] = 0x13;
		}

		i2cpgain[3] = sd->gain >> 3;
		i2cpcolorgain[3] = sd->gain >> 4;
		i2cpcolorgain[4] = sd->gain >> 4;
		i2cpcolorgain[5] = sd->gain >> 4;
		i2cpcolorgain[6] = sd->gain >> 4;

		if (i2c_w(gspca_dev, i2cpgain) < 0)
			goto err;
		if (i2c_w(gspca_dev, i2cpcolorgain) < 0)
			goto err;
		if (i2c_w(gspca_dev, i2cpdoit) < 0)
			goto err;
		break;
	    }
	}
	return;
err:
	PDEBUG(D_ERR, "i2c error gain");
}