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
struct v4l2_ext_controls {int error_idx; int count; int /*<<< orphan*/  ctrl_class; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct ctrl_helper {int handled; } ;
typedef  int /*<<< orphan*/  helper ;

/* Variables and functions */
 int ARRAY_SIZE (struct ctrl_helper*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_CTRL_ID2CLASS (int /*<<< orphan*/ ) ; 
 int class_check (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ctrl_helper*) ; 
 struct ctrl_helper* kmalloc (int,int /*<<< orphan*/ ) ; 
 int prepare_ext_ctrls (struct v4l2_ctrl_handler*,struct v4l2_ext_controls*,struct ctrl_helper*,int) ; 
 int try_or_set_ext_ctrls (struct v4l2_ctrl_handler*,struct v4l2_ext_controls*,struct ctrl_helper*,int) ; 

__attribute__((used)) static int try_set_ext_ctrls(struct v4l2_ctrl_handler *hdl,
			     struct v4l2_ext_controls *cs,
			     bool set)
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
		if (!helpers)
			return -ENOMEM;
	}
	ret = prepare_ext_ctrls(hdl, cs, helpers, !set);
	if (ret)
		goto free;

	/* First 'try' all controls and abort on error */
	ret = try_or_set_ext_ctrls(hdl, cs, helpers, false);
	/* If this is a 'set' operation and the initial 'try' failed,
	   then set error_idx to count to tell the application that no
	   controls changed value yet. */
	if (set)
		cs->error_idx = cs->count;
	if (!ret && set) {
		/* Reset 'handled' state */
		for (i = 0; i < cs->count; i++)
			helpers[i].handled = false;
		ret = try_or_set_ext_ctrls(hdl, cs, helpers, true);
	}

free:
	if (cs->count > ARRAY_SIZE(helper))
		kfree(helpers);
	return ret;
}