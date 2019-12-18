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
struct v4l2_ctrl {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int set_ctrl (struct v4l2_ctrl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_is_int (struct v4l2_ctrl*) ; 

int v4l2_ctrl_s_ctrl(struct v4l2_ctrl *ctrl, s32 val)
{
	/* It's a driver bug if this happens. */
	WARN_ON(!type_is_int(ctrl));
	return set_ctrl(ctrl, &val);
}