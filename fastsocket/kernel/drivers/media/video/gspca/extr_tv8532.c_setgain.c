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
struct sd {int /*<<< orphan*/  gain; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R20_GAIN_G1L ; 
 int /*<<< orphan*/  R22_GAIN_RL ; 
 int /*<<< orphan*/  R24_GAIN_BL ; 
 int /*<<< orphan*/  R26_GAIN_G2L ; 
 int /*<<< orphan*/  reg_w2 (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_w2(gspca_dev, R20_GAIN_G1L, sd->gain);
	reg_w2(gspca_dev, R22_GAIN_RL, sd->gain);
	reg_w2(gspca_dev, R24_GAIN_BL, sd->gain);
	reg_w2(gspca_dev, R26_GAIN_G2L, sd->gain);
}