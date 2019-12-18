#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tcw {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ena; } ;
struct TYPE_7__ {TYPE_2__ pmcw; } ;
struct subchannel {int /*<<< orphan*/  lpm; TYPE_3__ schib; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_4__* private; TYPE_1__ dev; } ;
struct TYPE_8__ {scalar_t__ state; unsigned long intparm; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_ONLINE ; 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int cio_tm_start_key (struct subchannel*,struct tcw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

int ccw_device_tm_start_key(struct ccw_device *cdev, struct tcw *tcw,
			    unsigned long intparm, u8 lpm, u8 key)
{
	struct subchannel *sch;
	int rc;

	sch = to_subchannel(cdev->dev.parent);
	if (!sch->schib.pmcw.ena)
		return -EINVAL;
	if (cdev->private->state != DEV_STATE_ONLINE)
		return -EIO;
	/* Adjust requested path mask to exclude unusable paths. */
	if (lpm) {
		lpm &= sch->lpm;
		if (lpm == 0)
			return -EACCES;
	}
	rc = cio_tm_start_key(sch, tcw, lpm, key);
	if (rc == 0)
		cdev->private->intparm = intparm;
	return rc;
}