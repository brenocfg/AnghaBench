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
typedef  int u32 ;
struct v4l2_querymenu {int index; int /*<<< orphan*/  name; scalar_t__ reserved; int /*<<< orphan*/  id; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl {char** qmenu; int minimum; int maximum; int menu_skip_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 

int v4l2_querymenu(struct v4l2_ctrl_handler *hdl, struct v4l2_querymenu *qm)
{
	struct v4l2_ctrl *ctrl;
	u32 i = qm->index;

	ctrl = v4l2_ctrl_find(hdl, qm->id);
	if (!ctrl)
		return -EINVAL;

	qm->reserved = 0;
	/* Sanity checks */
	if (ctrl->qmenu == NULL ||
	    i < ctrl->minimum || i > ctrl->maximum)
		return -EINVAL;
	/* Use mask to see if this menu item should be skipped */
	if (ctrl->menu_skip_mask & (1 << i))
		return -EINVAL;
	/* Empty menu items should also be skipped */
	if (ctrl->qmenu[i] == NULL || ctrl->qmenu[i][0] == '\0')
		return -EINVAL;
	strlcpy(qm->name, ctrl->qmenu[i], sizeof(qm->name));
	return 0;
}