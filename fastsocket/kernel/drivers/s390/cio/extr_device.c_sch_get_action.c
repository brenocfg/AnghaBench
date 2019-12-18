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
struct TYPE_8__ {scalar_t__ dev; int pam; } ;
struct TYPE_9__ {TYPE_3__ pmcw; } ;
struct subchannel {int opm; TYPE_4__ schib; } ;
struct ccw_device {TYPE_2__* private; scalar_t__ online; } ;
typedef  enum io_sch_action { ____Placeholder_io_sch_action } io_sch_action ;
struct TYPE_10__ {scalar_t__ devno; } ;
struct TYPE_6__ {int /*<<< orphan*/  resuming; } ;
struct TYPE_7__ {TYPE_1__ flags; TYPE_5__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_GONE ; 
 int /*<<< orphan*/  CIO_NO_PATH ; 
 int IO_SCH_ATTACH ; 
 int IO_SCH_DISC ; 
 int IO_SCH_NOP ; 
 int IO_SCH_ORPH_ATTACH ; 
 int IO_SCH_ORPH_UNREG ; 
 int IO_SCH_REPROBE ; 
 int IO_SCH_UNREG ; 
 int IO_SCH_UNREG_ATTACH ; 
 int IO_SCH_VERIFY ; 
 scalar_t__ NOTIFY_OK ; 
 scalar_t__ ccw_device_notify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 scalar_t__ device_is_disconnected (struct ccw_device*) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 

__attribute__((used)) static enum io_sch_action sch_get_action(struct subchannel *sch)
{
	struct ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	if (cio_update_schib(sch)) {
		/* Not operational. */
		if (!cdev)
			return IO_SCH_UNREG;
		if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
			return IO_SCH_UNREG;
		return IO_SCH_ORPH_UNREG;
	}
	/* Operational. */
	if (!cdev)
		return IO_SCH_ATTACH;
	if (sch->schib.pmcw.dev != cdev->private->dev_id.devno) {
		if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
			return IO_SCH_UNREG_ATTACH;
		return IO_SCH_ORPH_ATTACH;
	}
	if ((sch->schib.pmcw.pam & sch->opm) == 0) {
		if (ccw_device_notify(cdev, CIO_NO_PATH) != NOTIFY_OK)
			return IO_SCH_UNREG;
		return IO_SCH_DISC;
	}
	if (device_is_disconnected(cdev))
		return IO_SCH_REPROBE;
	if (cdev->online && !cdev->private->flags.resuming)
		return IO_SCH_VERIFY;
	return IO_SCH_NOP;
}