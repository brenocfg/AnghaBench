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
struct sd {int colors; scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  PAS106_REG13 ; 
 int /*<<< orphan*/  PAS106_REG9 ; 
 scalar_t__ SENSOR_PAS106 ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static void setcolors(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 I2cc[] = { 0x05, 0x02, 0x02, 0x05, 0x0d };
	__u8 i2cflags = 0x01;
	/* __u8 green = 0; */
	__u8 colors = sd->colors;

	I2cc[3] = colors;	/* red */
	I2cc[0] = 15 - colors;	/* blue */
	/* green = 15 - ((((7*I2cc[0]) >> 2 ) + I2cc[3]) >> 1); */
	/* I2cc[1] = I2cc[2] = green; */
	if (sd->sensor == SENSOR_PAS106) {
		i2c_w(gspca_dev, PAS106_REG13, &i2cflags, 1, 3);
		i2c_w(gspca_dev, PAS106_REG9, I2cc, sizeof I2cc, 1);
	}
/*	PDEBUG(D_CONF , "Etoms red %d blue %d green %d",
		I2cc[3], I2cc[0], green); */
}