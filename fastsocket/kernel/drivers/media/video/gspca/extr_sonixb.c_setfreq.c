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
struct sd {int sensor; int /*<<< orphan*/  freq; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;
struct TYPE_2__ {int sensor_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
#define  SENSOR_OV6650 129 
#define  SENSOR_OV7630 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 
 TYPE_1__* sensor_data ; 

__attribute__((used)) static void setfreq(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_OV6650:
	case SENSOR_OV7630: {
		/* Framerate adjust register for artificial light 50 hz flicker
		   compensation, for the ov6650 this is identical to ov6630
		   0x2b register, see ov6630 datasheet.
		   0x4f / 0x8a -> (30 fps -> 25 fps), 0x00 -> no adjustment */
		__u8 i2c[] = {0xa0, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x10};
		switch (sd->freq) {
		default:
/*		case 0:			 * no filter*/
/*		case 2:			 * 60 hz */
			i2c[3] = 0;
			break;
		case 1:			/* 50 hz */
			i2c[3] = (sd->sensor == SENSOR_OV6650)
					? 0x4f : 0x8a;
			break;
		}
		i2c[1] = sensor_data[sd->sensor].sensor_addr;
		if (i2c_w(gspca_dev, i2c) < 0)
			PDEBUG(D_ERR, "i2c error setfreq");
		break;
	    }
	}
}