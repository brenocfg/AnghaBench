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
struct v4l2_ext_controls {scalar_t__ ctrl_class; int count; int error_idx; TYPE_1__* controls; } ;
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  params; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 scalar_t__ V4L2_CTRL_CLASS_USER ; 
 int /*<<< orphan*/  VIDIOC_G_EXT_CTRLS ; 
 int cx18_g_ctrl (struct cx18*,struct v4l2_control*) ; 
 int cx2341x_ext_ctrls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 

int cx18_g_ext_ctrls(struct file *file, void *fh, struct v4l2_ext_controls *c)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	struct v4l2_control ctrl;

	if (c->ctrl_class == V4L2_CTRL_CLASS_USER) {
		int i;
		int err = 0;

		for (i = 0; i < c->count; i++) {
			ctrl.id = c->controls[i].id;
			ctrl.value = c->controls[i].value;
			err = cx18_g_ctrl(cx, &ctrl);
			c->controls[i].value = ctrl.value;
			if (err) {
				c->error_idx = i;
				break;
			}
		}
		return err;
	}
	if (c->ctrl_class == V4L2_CTRL_CLASS_MPEG)
		return cx2341x_ext_ctrls(&cx->params, 0, c, VIDIOC_G_EXT_CTRLS);
	return -EINVAL;
}