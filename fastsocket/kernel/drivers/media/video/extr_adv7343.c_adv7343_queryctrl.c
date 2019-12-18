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
struct v4l2_queryctrl {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_MAX ; 
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_MIN ; 
 int /*<<< orphan*/  ADV7343_GAIN_DEF ; 
 int /*<<< orphan*/  ADV7343_GAIN_MAX ; 
 int /*<<< orphan*/  ADV7343_GAIN_MIN ; 
 int /*<<< orphan*/  ADV7343_HUE_DEF ; 
 int /*<<< orphan*/  ADV7343_HUE_MAX ; 
 int /*<<< orphan*/  ADV7343_HUE_MIN ; 
#define  V4L2_CID_BRIGHTNESS 130 
#define  V4L2_CID_GAIN 129 
#define  V4L2_CID_HUE 128 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7343_queryctrl(struct v4l2_subdev *sd, struct v4l2_queryctrl *qc)
{
	switch (qc->id) {
	case V4L2_CID_BRIGHTNESS:
		return v4l2_ctrl_query_fill(qc, ADV7343_BRIGHTNESS_MIN,
						ADV7343_BRIGHTNESS_MAX, 1,
						ADV7343_BRIGHTNESS_DEF);
	case V4L2_CID_HUE:
		return v4l2_ctrl_query_fill(qc, ADV7343_HUE_MIN,
						ADV7343_HUE_MAX, 1 ,
						ADV7343_HUE_DEF);
	case V4L2_CID_GAIN:
		return v4l2_ctrl_query_fill(qc, ADV7343_GAIN_MIN,
						ADV7343_GAIN_MAX, 1,
						ADV7343_GAIN_DEF);
	default:
		break;
	}

	return 0;
}