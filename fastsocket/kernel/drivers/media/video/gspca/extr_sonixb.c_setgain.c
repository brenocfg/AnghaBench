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
struct sd {size_t sensor; scalar_t__ bridge; int gain; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_103 ; 
 int F_GAIN ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 TYPE_1__* sensor_data ; 
 int /*<<< orphan*/  setsensorgain (struct gspca_dev*) ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 gain;
	__u8 buf[3] = { 0, 0, 0 };

	if (sensor_data[sd->sensor].flags & F_GAIN) {
		/* Use the sensor gain to do the actual gain */
		setsensorgain(gspca_dev);
		return;
	}

	if (sd->bridge == BRIDGE_103) {
		gain = sd->gain >> 1;
		buf[0] = gain; /* Red */
		buf[1] = gain; /* Green */
		buf[2] = gain; /* Blue */
		reg_w(gspca_dev, 0x05, buf, 3);
	} else {
		gain = sd->gain >> 4;
		buf[0] = gain << 4 | gain; /* Red and blue */
		buf[1] = gain; /* Green */
		reg_w(gspca_dev, 0x10, buf, 2);
	}
}