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
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

__attribute__((used)) static int vpx3220_queryctrl(struct v4l2_subdev *sd, struct v4l2_queryctrl *qc)
{
	switch (qc->id) {
	case V4L2_CID_BRIGHTNESS:
		v4l2_ctrl_query_fill(qc, -128, 127, 1, 0);
		break;

	case V4L2_CID_CONTRAST:
		v4l2_ctrl_query_fill(qc, 0, 63, 1, 32);
		break;

	case V4L2_CID_SATURATION:
		v4l2_ctrl_query_fill(qc, 0, 4095, 1, 2048);
		break;

	case V4L2_CID_HUE:
		v4l2_ctrl_query_fill(qc, -512, 511, 1, 0);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}