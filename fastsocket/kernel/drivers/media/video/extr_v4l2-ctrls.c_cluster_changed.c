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
struct v4l2_ctrl {int ncontrols; int type; TYPE_1__ cur; int /*<<< orphan*/  val; int /*<<< orphan*/  val64; int /*<<< orphan*/  string; struct v4l2_ctrl** cluster; } ;

/* Variables and functions */
#define  V4L2_CTRL_TYPE_BUTTON 130 
#define  V4L2_CTRL_TYPE_INTEGER64 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cluster_changed(struct v4l2_ctrl *master)
{
	int diff = 0;
	int i;

	for (i = 0; !diff && i < master->ncontrols; i++) {
		struct v4l2_ctrl *ctrl = master->cluster[i];

		if (ctrl == NULL)
			continue;
		switch (ctrl->type) {
		case V4L2_CTRL_TYPE_BUTTON:
			/* Button controls are always 'different' */
			return 1;
		case V4L2_CTRL_TYPE_STRING:
			/* strings are always 0-terminated */
			diff = strcmp(ctrl->string, ctrl->cur.string);
			break;
		case V4L2_CTRL_TYPE_INTEGER64:
			diff = ctrl->val64 != ctrl->cur.val64;
			break;
		default:
			diff = ctrl->val != ctrl->cur.val;
			break;
		}
	}
	return diff;
}