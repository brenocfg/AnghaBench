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
struct sd {scalar_t__ sensor; int colors; } ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 scalar_t__ PAS106_REG9 ; 
 scalar_t__ SENSOR_PAS106 ; 
 int /*<<< orphan*/  i2c_r (struct gspca_dev*,scalar_t__) ; 

__attribute__((used)) static void getcolors(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_PAS106) {
/*		i2c_r(gspca_dev, PAS106_REG9);		 * blue */
		i2c_r(gspca_dev, PAS106_REG9 + 3);	/* red */
		sd->colors = gspca_dev->usb_buf[0] & 0x0f;
	}
}