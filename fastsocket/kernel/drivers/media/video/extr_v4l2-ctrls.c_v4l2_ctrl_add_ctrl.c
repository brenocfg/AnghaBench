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
struct v4l2_ctrl_handler {scalar_t__ error; } ;
struct v4l2_ctrl {struct v4l2_ctrl_handler* handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ handler_new_ref (struct v4l2_ctrl_handler*,struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  handler_set_err (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 

struct v4l2_ctrl *v4l2_ctrl_add_ctrl(struct v4l2_ctrl_handler *hdl,
					  struct v4l2_ctrl *ctrl)
{
	if (hdl == NULL || hdl->error)
		return NULL;
	if (ctrl == NULL) {
		handler_set_err(hdl, -EINVAL);
		return NULL;
	}
	if (ctrl->handler == hdl)
		return ctrl;
	return handler_new_ref(hdl, ctrl) ? NULL : ctrl;
}