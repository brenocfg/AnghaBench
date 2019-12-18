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
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {int id; int value; } ;
struct mt9v011 {int global_gain; int red_bal; int blue_bal; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BLUE_BALANCE 132 
#define  V4L2_CID_GAIN 131 
#define  V4L2_CID_HFLIP 130 
#define  V4L2_CID_RED_BALANCE 129 
#define  V4L2_CID_VFLIP 128 
 int /*<<< orphan*/  debug ; 
 struct mt9v011* to_mt9v011 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int mt9v011_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct mt9v011 *core = to_mt9v011(sd);

	v4l2_dbg(1, debug, sd, "g_ctrl called\n");

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		ctrl->value = core->global_gain;
		return 0;
	case V4L2_CID_RED_BALANCE:
		ctrl->value = core->red_bal;
		return 0;
	case V4L2_CID_BLUE_BALANCE:
		ctrl->value = core->blue_bal;
		return 0;
	case V4L2_CID_HFLIP:
		ctrl->value = core->hflip ? 1 : 0;
		return 0;
	case V4L2_CID_VFLIP:
		ctrl->value = core->vflip ? 1 : 0;
		return 0;
	}
	return -EINVAL;
}