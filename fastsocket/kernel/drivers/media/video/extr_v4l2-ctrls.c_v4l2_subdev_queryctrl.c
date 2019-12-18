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
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_queryctrl {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_CTRL_FLAG_NEXT_CTRL ; 
 int v4l2_queryctrl (int /*<<< orphan*/ ,struct v4l2_queryctrl*) ; 

int v4l2_subdev_queryctrl(struct v4l2_subdev *sd, struct v4l2_queryctrl *qc)
{
	if (qc->id & V4L2_CTRL_FLAG_NEXT_CTRL)
		return -EINVAL;
	return v4l2_queryctrl(sd->ctrl_handler, qc);
}