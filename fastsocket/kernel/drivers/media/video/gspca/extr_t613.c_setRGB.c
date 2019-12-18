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
struct sd {int red_gain; int blue_gain; int green_gain; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int*,int) ; 

__attribute__((used)) static void setRGB(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 all_gain_reg[6] =
		{0x87, 0x00, 0x88, 0x00, 0x89, 0x00};

	all_gain_reg[1] = sd->red_gain;
	all_gain_reg[3] = sd->blue_gain;
	all_gain_reg[5] = sd->green_gain;
	reg_w_buf(gspca_dev, all_gain_reg, sizeof all_gain_reg);
}