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
typedef  int u8 ;
typedef  int u16 ;
struct sd {int backlight; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setbacklight(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u16 v;
	u8 data;

	data = (sd->backlight << 4) | 0x0f;
	i2c_write(gspca_dev, 0xaa, &data, 1);
	v = 613 + 12 * sd->backlight;
	data = v >> 8;
	i2c_write(gspca_dev, 0xc4, &data, 1);
	data = v;
	i2c_write(gspca_dev, 0xc5, &data, 1);
	v = 1093 - 12 * sd->backlight;
	data = v >> 8;
	i2c_write(gspca_dev, 0xc6, &data, 1);
	data = v;
	i2c_write(gspca_dev, 0xc7, &data, 1);
	v = 342 + 9 * sd->backlight;
	data = v >> 8;
	i2c_write(gspca_dev, 0xc8, &data, 1);
	data = v;
	i2c_write(gspca_dev, 0xc9, &data, 1);
	v = 702 - 9 * sd->backlight;
	data = v >> 8;
	i2c_write(gspca_dev, 0xca, &data, 1);
	data = v;
	i2c_write(gspca_dev, 0xcb, &data, 1);
}