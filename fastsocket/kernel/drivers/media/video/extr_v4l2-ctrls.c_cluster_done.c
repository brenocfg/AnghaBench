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
struct v4l2_ext_controls {int count; } ;
struct v4l2_ctrl {int dummy; } ;
struct ctrl_helper {int handled; TYPE_1__* ctrl; } ;
struct TYPE_2__ {struct v4l2_ctrl** cluster; } ;

/* Variables and functions */

__attribute__((used)) static void cluster_done(unsigned from,
			 struct v4l2_ext_controls *cs,
			 struct ctrl_helper *helpers)
{
	struct v4l2_ctrl **cluster = helpers[from].ctrl->cluster;
	int i;

	/* Find any controls from the same cluster and mark them as handled */
	for (i = from; i < cs->count; i++)
		if (helpers[i].ctrl->cluster == cluster)
			helpers[i].handled = true;
}