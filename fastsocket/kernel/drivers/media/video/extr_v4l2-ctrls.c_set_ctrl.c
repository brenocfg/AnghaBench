#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct v4l2_ctrl {int flags; int ncontrols; int has_new; TYPE_1__ cur; int /*<<< orphan*/  val; struct v4l2_ctrl** cluster; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int EACCES ; 
 int V4L2_CTRL_FLAG_READ_ONLY ; 
 int try_or_set_control_cluster (struct v4l2_ctrl*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (struct v4l2_ctrl*) ; 

__attribute__((used)) static int set_ctrl(struct v4l2_ctrl *ctrl, s32 *val)
{
	struct v4l2_ctrl *master = ctrl->cluster[0];
	int ret;
	int i;

	if (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY)
		return -EACCES;

	v4l2_ctrl_lock(ctrl);

	/* Reset the 'has_new' flags of the cluster */
	for (i = 0; i < master->ncontrols; i++)
		if (master->cluster[i])
			master->cluster[i]->has_new = 0;

	ctrl->val = *val;
	ctrl->has_new = 1;
	ret = try_or_set_control_cluster(master, false);
	if (!ret)
		ret = try_or_set_control_cluster(master, true);
	*val = ctrl->cur.val;
	v4l2_ctrl_unlock(ctrl);
	return ret;
}