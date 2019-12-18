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
struct v4l2_ctrl_handler {int /*<<< orphan*/  ctrl_refs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ find_ref_lock (struct v4l2_ctrl_handler*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int class_check(struct v4l2_ctrl_handler *hdl, u32 ctrl_class)
{
	if (ctrl_class == 0)
		return list_empty(&hdl->ctrl_refs) ? -EINVAL : 0;
	return find_ref_lock(hdl, ctrl_class | 1) ? 0 : -EINVAL;
}