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
struct v4l2_ext_controls {int error_idx; int count; int /*<<< orphan*/  ctrl_class; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl {int flags; TYPE_1__* ops; scalar_t__ is_volatile; struct v4l2_ctrl** cluster; } ;
struct ctrl_helper {scalar_t__ handled; struct v4l2_ctrl* ctrl; } ;
typedef  int /*<<< orphan*/  helper ;
struct TYPE_2__ {int (* g_volatile_ctrl ) (struct v4l2_ctrl*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (struct ctrl_helper*) ; 
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V4L2_CTRL_FLAG_WRITE_ONLY ; 
 int /*<<< orphan*/  V4L2_CTRL_ID2CLASS (int /*<<< orphan*/ ) ; 
 int class_check (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_done (int,struct v4l2_ext_controls*,struct ctrl_helper*) ; 
 int cluster_walk (int,struct v4l2_ext_controls*,struct ctrl_helper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cur_to_user ; 
 int /*<<< orphan*/  kfree (struct ctrl_helper*) ; 
 struct ctrl_helper* kmalloc (int,int /*<<< orphan*/ ) ; 
 int prepare_ext_ctrls (struct v4l2_ctrl_handler*,struct v4l2_ext_controls*,struct ctrl_helper*,int) ; 
 int stub1 (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (struct v4l2_ctrl*) ; 

int v4l2_g_ext_ctrls(struct v4l2_ctrl_handler *hdl, struct v4l2_ext_controls *cs)
{
	struct ctrl_helper helper[4];
	struct ctrl_helper *helpers = helper;
	int ret;
	int i;

	cs->error_idx = cs->count;
	cs->ctrl_class = V4L2_CTRL_ID2CLASS(cs->ctrl_class);

	if (hdl == NULL)
		return -EINVAL;

	if (cs->count == 0)
		return class_check(hdl, cs->ctrl_class);

	if (cs->count > ARRAY_SIZE(helper)) {
		helpers = kmalloc(sizeof(helper[0]) * cs->count, GFP_KERNEL);
		if (helpers == NULL)
			return -ENOMEM;
	}

	ret = prepare_ext_ctrls(hdl, cs, helpers, false);

	for (i = 0; !ret && i < cs->count; i++)
		if (helpers[i].ctrl->flags & V4L2_CTRL_FLAG_WRITE_ONLY)
			ret = -EACCES;

	for (i = 0; !ret && i < cs->count; i++) {
		struct v4l2_ctrl *ctrl = helpers[i].ctrl;
		struct v4l2_ctrl *master = ctrl->cluster[0];

		if (helpers[i].handled)
			continue;

		cs->error_idx = i;

		v4l2_ctrl_lock(master);
		/* g_volatile_ctrl will update the current control values */
		if (ctrl->is_volatile && master->ops->g_volatile_ctrl)
			ret = master->ops->g_volatile_ctrl(master);
		/* If OK, then copy the current control values to the caller */
		if (!ret)
			ret = cluster_walk(i, cs, helpers, cur_to_user);
		v4l2_ctrl_unlock(master);
		cluster_done(i, cs, helpers);
	}

	if (cs->count > ARRAY_SIZE(helper))
		kfree(helpers);
	return ret;
}