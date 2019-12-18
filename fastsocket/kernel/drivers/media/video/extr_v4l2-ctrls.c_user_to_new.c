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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ext_control {int /*<<< orphan*/  value; int /*<<< orphan*/  string; int /*<<< orphan*/  size; int /*<<< orphan*/  value64; } ;
struct v4l2_ctrl {int has_new; int type; char* string; int /*<<< orphan*/  val; int /*<<< orphan*/  maximum; int /*<<< orphan*/  val64; } ;

/* Variables and functions */
 int EFAULT ; 
 int ERANGE ; 
#define  V4L2_CTRL_TYPE_INTEGER64 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 int copy_from_user (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int user_to_new(struct v4l2_ext_control *c,
		       struct v4l2_ctrl *ctrl)
{
	int ret;
	u32 size;

	ctrl->has_new = 1;
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER64:
		ctrl->val64 = c->value64;
		break;
	case V4L2_CTRL_TYPE_STRING:
		size = c->size;
		if (size == 0)
			return -ERANGE;
		if (size > ctrl->maximum + 1)
			size = ctrl->maximum + 1;
		ret = copy_from_user(ctrl->string, c->string, size);
		if (!ret) {
			char last = ctrl->string[size - 1];

			ctrl->string[size - 1] = 0;
			/* If the string was longer than ctrl->maximum,
			   then return an error. */
			if (strlen(ctrl->string) == ctrl->maximum && last)
				return -ERANGE;
		}
		return ret ? -EFAULT : 0;
	default:
		ctrl->val = c->value;
		break;
	}
	return 0;
}