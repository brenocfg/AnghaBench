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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct mt9v011 {int global_gain; int blue_bal; } ;

/* Variables and functions */
 int /*<<< orphan*/  R2B_MT9V011_GREEN_1_GAIN ; 
 int /*<<< orphan*/  R2C_MT9V011_BLUE_GAIN ; 
 int /*<<< orphan*/  R2D_MT9V011_RED_GAIN ; 
 int /*<<< orphan*/  R2E_MT9V011_GREEN_2_GAIN ; 
 int /*<<< orphan*/  mt9v011_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct mt9v011* to_mt9v011 (struct v4l2_subdev*) ; 

__attribute__((used)) static void set_balance(struct v4l2_subdev *sd)
{
	struct mt9v011 *core = to_mt9v011(sd);
	u16 green1_gain, green2_gain, blue_gain, red_gain;

	green1_gain = core->global_gain;
	green2_gain = core->global_gain;

	blue_gain = core->global_gain +
		    core->global_gain * core->blue_bal / (1 << 9);

	red_gain = core->global_gain +
		   core->global_gain * core->blue_bal / (1 << 9);

	mt9v011_write(sd, R2B_MT9V011_GREEN_1_GAIN, green1_gain);
	mt9v011_write(sd, R2E_MT9V011_GREEN_2_GAIN,  green1_gain);
	mt9v011_write(sd, R2C_MT9V011_BLUE_GAIN, blue_gain);
	mt9v011_write(sd, R2D_MT9V011_RED_GAIN, red_gain);
}