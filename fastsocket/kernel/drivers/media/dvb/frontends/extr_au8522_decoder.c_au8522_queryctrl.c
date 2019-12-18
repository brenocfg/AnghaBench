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
struct v4l2_queryctrl {int id; scalar_t__ type; } ;

/* Variables and functions */
 int AU8522_TVDEC_CONTRAST_REG00BH_CVBS ; 
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

__attribute__((used)) static int au8522_queryctrl(struct v4l2_subdev *sd, struct v4l2_queryctrl *qc)
{
	switch (qc->id) {
	case V4L2_CID_CONTRAST:
		return v4l2_ctrl_query_fill(qc, 0, 255, 1,
					    AU8522_TVDEC_CONTRAST_REG00BH_CVBS);
	case V4L2_CID_BRIGHTNESS:
		return v4l2_ctrl_query_fill(qc, 0, 255, 1, 109);
	case V4L2_CID_SATURATION:
		return v4l2_ctrl_query_fill(qc, 0, 255, 1, 128);
	case V4L2_CID_HUE:
		return v4l2_ctrl_query_fill(qc, -32768, 32768, 1, 0);
	default:
		break;
	}

	qc->type = 0;
	return -EINVAL;
}