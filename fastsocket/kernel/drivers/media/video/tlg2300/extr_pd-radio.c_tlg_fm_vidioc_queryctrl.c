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
struct v4l2_queryctrl {int id; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_CID_TUNE_PREEMPHASIS ; 
 int V4L2_CTRL_FLAG_NEXT_CTRL ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_UPDATE ; 
 int /*<<< orphan*/  V4L2_PREEMPHASIS_50_uS ; 
 int /*<<< orphan*/  V4L2_PREEMPHASIS_75_uS ; 
 int /*<<< orphan*/  V4L2_PREEMPHASIS_DISABLED ; 
 int /*<<< orphan*/  v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tlg_fm_vidioc_queryctrl(struct file *file, void *priv,
		struct v4l2_queryctrl *ctrl)
{
	if (!(ctrl->id & V4L2_CTRL_FLAG_NEXT_CTRL))
		return -EINVAL;

	ctrl->id &= ~V4L2_CTRL_FLAG_NEXT_CTRL;
	if (ctrl->id != V4L2_CID_TUNE_PREEMPHASIS) {
		/* return the next supported control */
		ctrl->id = V4L2_CID_TUNE_PREEMPHASIS;
		v4l2_ctrl_query_fill(ctrl, V4L2_PREEMPHASIS_DISABLED,
					V4L2_PREEMPHASIS_75_uS, 1,
					V4L2_PREEMPHASIS_50_uS);
		ctrl->flags = V4L2_CTRL_FLAG_UPDATE;
		return 0;
	}
	return -EINVAL;
}