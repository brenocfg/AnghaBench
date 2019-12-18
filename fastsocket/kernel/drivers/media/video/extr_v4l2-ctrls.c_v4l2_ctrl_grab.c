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
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

void v4l2_ctrl_grab(struct v4l2_ctrl *ctrl, bool grabbed)
{
	if (ctrl == NULL)
		return;

	if (grabbed)
		/* set V4L2_CTRL_FLAG_GRABBED */
		set_bit(1, &ctrl->flags);
	else
		/* clear V4L2_CTRL_FLAG_GRABBED */
		clear_bit(1, &ctrl->flags);
}