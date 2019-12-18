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
typedef  int u16 ;
struct sd {int red_gain; int blue_gain; int green_gain; size_t sensor; int /*<<< orphan*/  awb; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int reg80; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int*,int) ; 
 TYPE_1__* sensor_data ; 

__attribute__((used)) static void init_gains(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u16 reg80;
	u8 all_gain_reg[8] =
		{0x87, 0x00, 0x88, 0x00, 0x89, 0x00, 0x80, 0x00};

	all_gain_reg[1] = sd->red_gain;
	all_gain_reg[3] = sd->blue_gain;
	all_gain_reg[5] = sd->green_gain;
	reg80 = sensor_data[sd->sensor].reg80;
	if (!sd->awb)
		reg80 &= ~0x04;
	all_gain_reg[7] = reg80;
	reg_w_buf(gspca_dev, all_gain_reg, sizeof all_gain_reg);

	reg_w(gspca_dev, (sd->red_gain  << 8) + 0x87);
	reg_w(gspca_dev, (sd->blue_gain << 8) + 0x88);
	reg_w(gspca_dev, (sd->green_gain  << 8) + 0x89);
}