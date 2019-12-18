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
struct v4l2_ext_controls {int dummy; } ;
struct v4l2_ctrl_handler {int dummy; } ;

/* Variables and functions */
 int try_set_ext_ctrls (struct v4l2_ctrl_handler*,struct v4l2_ext_controls*,int) ; 

int v4l2_s_ext_ctrls(struct v4l2_ctrl_handler *hdl, struct v4l2_ext_controls *cs)
{
	return try_set_ext_ctrls(hdl, cs, true);
}