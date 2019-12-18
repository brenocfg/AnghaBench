#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int vpm; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* drv; scalar_t__ online; TYPE_2__* private; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* path_event ) (struct ccw_device*,int*) ;} ;
struct TYPE_5__ {int path_gone_mask; int path_new_mask; int pgid_reset_mask; } ;

/* Variables and functions */
 int PE_NONE ; 
 int PE_PATHGROUP_ESTABLISHED ; 
 int PE_PATH_AVAILABLE ; 
 int PE_PATH_GONE ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccw_device_report_path_events(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	int path_event[8];
	int chp, mask;

	for (chp = 0, mask = 0x80; chp < 8; chp++, mask >>= 1) {
		path_event[chp] = PE_NONE;
		if (mask & cdev->private->path_gone_mask & ~(sch->vpm))
			path_event[chp] |= PE_PATH_GONE;
		if (mask & cdev->private->path_new_mask & sch->vpm)
			path_event[chp] |= PE_PATH_AVAILABLE;
		if (mask & cdev->private->pgid_reset_mask & sch->vpm)
			path_event[chp] |= PE_PATHGROUP_ESTABLISHED;
	}
	if (cdev->online && cdev->drv->path_event)
		cdev->drv->path_event(cdev, path_event);
}