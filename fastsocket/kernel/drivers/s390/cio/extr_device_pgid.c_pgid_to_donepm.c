#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct subchannel {int opm; } ;
struct TYPE_9__ {scalar_t__ state1; scalar_t__ state3; } ;
struct TYPE_10__ {TYPE_4__ ps; } ;
struct pgid {TYPE_5__ inf; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; TYPE_1__ dev; } ;
struct TYPE_7__ {scalar_t__ mpath; } ;
struct TYPE_8__ {int pgid_valid_mask; TYPE_2__ flags; struct pgid* pgid; } ;

/* Variables and functions */
 scalar_t__ SNID_STATE1_GROUPED ; 
 scalar_t__ SNID_STATE1_UNGROUPED ; 
 scalar_t__ SNID_STATE3_MULTI_PATH ; 
 scalar_t__ SNID_STATE3_SINGLE_PATH ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 pgid_to_donepm(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct pgid *pgid;
	int i;
	int lpm;
	u8 donepm = 0;

	/* Set bits for paths which are already in the target state. */
	for (i = 0; i < 8; i++) {
		lpm = 0x80 >> i;
		if ((cdev->private->pgid_valid_mask & lpm) == 0)
			continue;
		pgid = &cdev->private->pgid[i];
		if (sch->opm & lpm) {
			if (pgid->inf.ps.state1 != SNID_STATE1_GROUPED)
				continue;
		} else {
			if (pgid->inf.ps.state1 != SNID_STATE1_UNGROUPED)
				continue;
		}
		if (cdev->private->flags.mpath) {
			if (pgid->inf.ps.state3 != SNID_STATE3_MULTI_PATH)
				continue;
		} else {
			if (pgid->inf.ps.state3 != SNID_STATE3_SINGLE_PATH)
				continue;
		}
		donepm |= lpm;
	}

	return donepm;
}