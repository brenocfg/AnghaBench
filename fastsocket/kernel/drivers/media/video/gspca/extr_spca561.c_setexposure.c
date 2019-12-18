#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sd {int exposure; } ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EXPOSURE_MAX ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i, expo = 0;

	/* Register 0x8309 controls exposure for the spca561,
	   the basic exposure setting goes from 1-2047, where 1 is completely
	   dark and 2047 is very bright. It not only influences exposure but
	   also the framerate (to allow for longer exposure) from 1 - 300 it
	   only raises the exposure time then from 300 - 600 it halves the
	   framerate to be able to further raise the exposure time and for every
	   300 more it halves the framerate again. This allows for a maximum
	   exposure time of circa 0.2 - 0.25 seconds (30 / (2000/3000) fps).
	   Sometimes this is not enough, the 1-2047 uses bits 0-10, bits 11-12
	   configure a divider for the base framerate which us used at the
	   exposure setting of 1-300. These bits configure the base framerate
	   according to the following formula: fps = 60 / (value + 2) */

	/* We choose to use the high bits setting the fixed framerate divisor
	   asap, as setting high basic exposure setting without the fixed
	   divider in combination with high gains makes the cam stop */
	int table[] =  { 0, 450, 550, 625, EXPOSURE_MAX };

	for (i = 0; i < ARRAY_SIZE(table) - 1; i++) {
		if (sd->exposure <= table[i + 1]) {
			expo  = sd->exposure - table[i];
			if (i)
				expo += 300;
			expo |= i << 11;
			break;
		}
	}

	gspca_dev->usb_buf[0] = expo;
	gspca_dev->usb_buf[1] = expo >> 8;
	reg_w_buf(gspca_dev, 0x8309, 2);
}