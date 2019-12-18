#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int actl; } ;
struct TYPE_8__ {TYPE_1__ cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  ena; } ;
struct TYPE_11__ {TYPE_2__ scsw; TYPE_4__ pmcw; } ;
struct subchannel {TYPE_5__ schib; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_6__* private; TYPE_3__ dev; } ;
struct TYPE_12__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_NOT_OPER ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int EINVAL ; 
 int ENODEV ; 
 int SCSW_ACTL_SUSPENDED ; 
 int cio_resume (struct subchannel*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

int ccw_device_resume(struct ccw_device *cdev)
{
	struct subchannel *sch;

	if (!cdev || !cdev->dev.parent)
		return -ENODEV;
	sch = to_subchannel(cdev->dev.parent);
	if (!sch->schib.pmcw.ena)
		return -EINVAL;
	if (cdev->private->state == DEV_STATE_NOT_OPER)
		return -ENODEV;
	if (cdev->private->state != DEV_STATE_ONLINE ||
	    !(sch->schib.scsw.cmd.actl & SCSW_ACTL_SUSPENDED))
		return -EINVAL;
	return cio_resume(sch);
}