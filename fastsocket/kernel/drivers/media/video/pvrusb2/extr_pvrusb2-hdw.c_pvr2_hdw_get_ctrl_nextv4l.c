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
struct pvr2_hdw {unsigned int control_cnt; struct pvr2_ctrl* controls; } ;
struct pvr2_ctrl {TYPE_1__* info; } ;
struct TYPE_2__ {int v4l_id; } ;

/* Variables and functions */

struct pvr2_ctrl *pvr2_hdw_get_ctrl_nextv4l(struct pvr2_hdw *hdw,
					    unsigned int ctl_id)
{
	struct pvr2_ctrl *cptr,*cp2;
	unsigned int idx;
	int i;

	/* This could be made a lot more efficient, but for now... */
	cp2 = NULL;
	for (idx = 0; idx < hdw->control_cnt; idx++) {
		cptr = hdw->controls + idx;
		i = cptr->info->v4l_id;
		if (!i) continue;
		if (i <= ctl_id) continue;
		if (cp2 && (cp2->info->v4l_id < i)) continue;
		cp2 = cptr;
	}
	return cp2;
	return NULL;
}