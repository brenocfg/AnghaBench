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
struct v4l2_queryctrl {scalar_t__ id; int /*<<< orphan*/  flags; } ;
struct cx231xx {int /*<<< orphan*/  mpeg_params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_DISABLED ; 
 int /*<<< orphan*/  ctrl_classes ; 
 scalar_t__ cx2341x_ctrl_query (int /*<<< orphan*/ *,struct v4l2_queryctrl*) ; 
 scalar_t__ v4l2_ctrl_next (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cx231xx_queryctrl(struct cx231xx *dev,
	struct v4l2_queryctrl *qctrl)
{
	qctrl->id = v4l2_ctrl_next(ctrl_classes, qctrl->id);
	if (qctrl->id == 0)
		return -EINVAL;

	/* MPEG V4L2 controls */
	if (cx2341x_ctrl_query(&dev->mpeg_params, qctrl))
		qctrl->flags |= V4L2_CTRL_FLAG_DISABLED;

	return 0;
}