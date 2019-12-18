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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ext_control {int /*<<< orphan*/  value; int /*<<< orphan*/  value64; int /*<<< orphan*/  string; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  val64; int /*<<< orphan*/  string; } ;
struct v4l2_ctrl {int type; TYPE_1__ cur; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOSPC ; 
#define  V4L2_CTRL_TYPE_INTEGER64 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cur_to_user(struct v4l2_ext_control *c,
		       struct v4l2_ctrl *ctrl)
{
	u32 len;

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_STRING:
		len = strlen(ctrl->cur.string);
		if (c->size < len + 1) {
			c->size = len + 1;
			return -ENOSPC;
		}
		return copy_to_user(c->string, ctrl->cur.string,
						len + 1) ? -EFAULT : 0;
	case V4L2_CTRL_TYPE_INTEGER64:
		c->value64 = ctrl->cur.val64;
		break;
	default:
		c->value = ctrl->cur.val;
		break;
	}
	return 0;
}