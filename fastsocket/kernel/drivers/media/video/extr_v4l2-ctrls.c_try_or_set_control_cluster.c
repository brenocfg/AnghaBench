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
struct v4l2_ctrl {int ncontrols; int flags; struct v4l2_ctrl** cluster; TYPE_1__* ops; scalar_t__ has_new; } ;
struct TYPE_2__ {int (* try_ctrl ) (struct v4l2_ctrl*) ;int (* s_ctrl ) (struct v4l2_ctrl*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int V4L2_CTRL_FLAG_GRABBED ; 
 scalar_t__ cluster_changed (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  cur_to_new (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  new_to_cur (struct v4l2_ctrl*) ; 
 int stub1 (struct v4l2_ctrl*) ; 
 int stub2 (struct v4l2_ctrl*) ; 
 int validate_new (struct v4l2_ctrl*) ; 

__attribute__((used)) static int try_or_set_control_cluster(struct v4l2_ctrl *master, bool set)
{
	bool try = !set;
	int ret = 0;
	int i;

	/* Go through the cluster and either validate the new value or
	   (if no new value was set), copy the current value to the new
	   value, ensuring a consistent view for the control ops when
	   called. */
	for (i = 0; !ret && i < master->ncontrols; i++) {
		struct v4l2_ctrl *ctrl = master->cluster[i];

		if (ctrl == NULL)
			continue;

		if (ctrl->has_new) {
			/* Double check this: it may have changed since the
			   last check in try_or_set_ext_ctrls(). */
			if (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED))
				return -EBUSY;

			/* Validate if required */
			if (!set)
				ret = validate_new(ctrl);
			continue;
		}
		/* No new value was set, so copy the current and force
		   a call to try_ctrl later, since the values for the cluster
		   may now have changed and the end result might be invalid. */
		try = true;
		cur_to_new(ctrl);
	}

	/* For larger clusters you have to call try_ctrl again to
	   verify that the controls are still valid after the
	   'cur_to_new' above. */
	if (!ret && master->ops->try_ctrl && try)
		ret = master->ops->try_ctrl(master);

	/* Don't set if there is no change */
	if (!ret && set && cluster_changed(master)) {
		ret = master->ops->s_ctrl(master);
		/* If OK, then make the new values permanent. */
		if (!ret)
			for (i = 0; i < master->ncontrols; i++)
				new_to_cur(master->cluster[i]);
	}
	return ret;
}