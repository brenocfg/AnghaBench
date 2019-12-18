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
struct v4l2_ext_controls {unsigned int error_idx; unsigned int count; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl {int flags; unsigned int ncontrols; scalar_t__ has_new; struct v4l2_ctrl** cluster; } ;
struct ctrl_helper {scalar_t__ handled; struct v4l2_ctrl* ctrl; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int V4L2_CTRL_FLAG_GRABBED ; 
 int V4L2_CTRL_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  cluster_done (unsigned int,struct v4l2_ext_controls*,struct ctrl_helper*) ; 
 int cluster_walk (unsigned int,struct v4l2_ext_controls*,struct ctrl_helper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_to_user ; 
 int try_or_set_control_cluster (struct v4l2_ctrl*,int) ; 
 int /*<<< orphan*/  user_to_new ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (struct v4l2_ctrl*) ; 

__attribute__((used)) static int try_or_set_ext_ctrls(struct v4l2_ctrl_handler *hdl,
				struct v4l2_ext_controls *cs,
				struct ctrl_helper *helpers,
				bool set)
{
	unsigned i, j;
	int ret = 0;

	cs->error_idx = cs->count;
	for (i = 0; i < cs->count; i++) {
		struct v4l2_ctrl *ctrl = helpers[i].ctrl;

		if (!set)
			cs->error_idx = i;

		if (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY)
			return -EACCES;
		/* This test is also done in try_set_control_cluster() which
		   is called in atomic context, so that has the final say,
		   but it makes sense to do an up-front check as well. Once
		   an error occurs in try_set_control_cluster() some other
		   controls may have been set already and we want to do a
		   best-effort to avoid that. */
		if (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED))
			return -EBUSY;
	}

	for (i = 0; !ret && i < cs->count; i++) {
		struct v4l2_ctrl *ctrl = helpers[i].ctrl;
		struct v4l2_ctrl *master = ctrl->cluster[0];

		cs->error_idx = i;

		if (helpers[i].handled)
			continue;

		v4l2_ctrl_lock(ctrl);

		/* Reset the 'has_new' flags of the cluster */
		for (j = 0; j < master->ncontrols; j++)
			if (master->cluster[j])
				master->cluster[j]->has_new = 0;

		/* Copy the new caller-supplied control values.
		   user_to_new() sets 'has_new' to 1. */
		ret = cluster_walk(i, cs, helpers, user_to_new);

		if (!ret)
			ret = try_or_set_control_cluster(master, set);

		/* Copy the new values back to userspace. */
		if (!ret)
			ret = cluster_walk(i, cs, helpers, new_to_user);

		v4l2_ctrl_unlock(ctrl);
		cluster_done(i, cs, helpers);
	}
	return ret;
}