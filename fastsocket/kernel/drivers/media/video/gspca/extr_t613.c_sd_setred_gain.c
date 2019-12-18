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
struct sd {int red_gain; } ;
struct gspca_dev {scalar_t__ streaming; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 

__attribute__((used)) static int sd_setred_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->red_gain = val;
	if (gspca_dev->streaming)
		reg_w(gspca_dev, (val << 8) + 0x87);

	return 0;
}