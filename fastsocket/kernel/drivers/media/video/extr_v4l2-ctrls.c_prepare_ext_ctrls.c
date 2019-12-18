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
typedef  size_t u32 ;
struct v4l2_ext_controls {size_t count; size_t error_idx; scalar_t__ ctrl_class; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {size_t id; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl {int flags; } ;
struct ctrl_helper {int handled; struct v4l2_ctrl* ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t V4L2_CID_PRIVATE_BASE ; 
 int V4L2_CTRL_FLAG_DISABLED ; 
 scalar_t__ V4L2_CTRL_ID2CLASS (size_t) ; 
 size_t V4L2_CTRL_ID_MASK ; 
 struct v4l2_ctrl* v4l2_ctrl_find (struct v4l2_ctrl_handler*,size_t) ; 

__attribute__((used)) static int prepare_ext_ctrls(struct v4l2_ctrl_handler *hdl,
			     struct v4l2_ext_controls *cs,
			     struct ctrl_helper *helpers,
			     bool try)
{
	u32 i;

	for (i = 0; i < cs->count; i++) {
		struct v4l2_ext_control *c = &cs->controls[i];
		struct v4l2_ctrl *ctrl;
		u32 id = c->id & V4L2_CTRL_ID_MASK;

		if (try)
			cs->error_idx = i;

		if (cs->ctrl_class && V4L2_CTRL_ID2CLASS(id) != cs->ctrl_class)
			return -EINVAL;

		/* Old-style private controls are not allowed for
		   extended controls */
		if (id >= V4L2_CID_PRIVATE_BASE)
			return -EINVAL;
		ctrl = v4l2_ctrl_find(hdl, id);
		if (ctrl == NULL)
			return -EINVAL;
		if (ctrl->flags & V4L2_CTRL_FLAG_DISABLED)
			return -EINVAL;

		helpers[i].ctrl = ctrl;
		helpers[i].handled = false;
	}
	return 0;
}