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
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  val64; int /*<<< orphan*/  string; } ;
struct v4l2_ctrl {int type; TYPE_1__ cur; int /*<<< orphan*/  val; int /*<<< orphan*/  val64; int /*<<< orphan*/  string; } ;

/* Variables and functions */
#define  V4L2_CTRL_TYPE_INTEGER64 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cur_to_new(struct v4l2_ctrl *ctrl)
{
	if (ctrl == NULL)
		return;
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_STRING:
		/* strings are always 0-terminated */
		strcpy(ctrl->string, ctrl->cur.string);
		break;
	case V4L2_CTRL_TYPE_INTEGER64:
		ctrl->val64 = ctrl->cur.val64;
		break;
	default:
		ctrl->val = ctrl->cur.val;
		break;
	}
}