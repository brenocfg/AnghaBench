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
struct v4l2_ext_controls {int count; int /*<<< orphan*/ * controls; } ;
struct v4l2_ctrl {struct v4l2_ctrl** cluster; } ;
struct ctrl_helper {int /*<<< orphan*/  handled; struct v4l2_ctrl* ctrl; } ;
typedef  int (* cluster_func ) (int /*<<< orphan*/ *,struct v4l2_ctrl*) ;

/* Variables and functions */

__attribute__((used)) static int cluster_walk(unsigned from,
			struct v4l2_ext_controls *cs,
			struct ctrl_helper *helpers,
			cluster_func f)
{
	struct v4l2_ctrl **cluster = helpers[from].ctrl->cluster;
	int ret = 0;
	int i;

	/* Find any controls from the same cluster and call the function */
	for (i = from; !ret && i < cs->count; i++) {
		struct v4l2_ctrl *ctrl = helpers[i].ctrl;

		if (!helpers[i].handled && ctrl->cluster == cluster)
			ret = f(&cs->controls[i], ctrl);
	}
	return ret;
}