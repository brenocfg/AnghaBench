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
struct sd {int colors; } ;
struct gspca_dev {int ctrl_dis; } ;

/* Variables and functions */
 int COLORS_IDX ; 
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setcolors(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 data;

	if (gspca_dev->ctrl_dis & (1 << COLORS_IDX))
		return;
	data = sd->colors - (sd->colors >> 3) - 1;
	i2c_write(gspca_dev, 0x94, &data, 1);
	i2c_write(gspca_dev, 0x95, &sd->colors, 1);
}