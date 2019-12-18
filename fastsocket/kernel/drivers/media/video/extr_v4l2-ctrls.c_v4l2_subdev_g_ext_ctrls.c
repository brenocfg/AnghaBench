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
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_ext_controls {int dummy; } ;

/* Variables and functions */
 int v4l2_g_ext_ctrls (int /*<<< orphan*/ ,struct v4l2_ext_controls*) ; 

int v4l2_subdev_g_ext_ctrls(struct v4l2_subdev *sd, struct v4l2_ext_controls *cs)
{
	return v4l2_g_ext_ctrls(sd->ctrl_handler, cs);
}