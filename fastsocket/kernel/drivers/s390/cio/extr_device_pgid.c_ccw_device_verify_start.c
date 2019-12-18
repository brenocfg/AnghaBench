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
struct TYPE_8__ {int /*<<< orphan*/  pam; } ;
struct TYPE_9__ {TYPE_2__ pmcw; } ;
struct subchannel {TYPE_3__ schib; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_6__* private; TYPE_1__ dev; } ;
struct TYPE_11__ {scalar_t__ doverify; int /*<<< orphan*/  mpath; int /*<<< orphan*/  pgroup; } ;
struct TYPE_10__ {int /*<<< orphan*/  mpath; int /*<<< orphan*/  pgroup; } ;
struct TYPE_12__ {TYPE_5__ flags; TYPE_4__ options; int /*<<< orphan*/  pgid_todo_mask; scalar_t__ pgid_valid_mask; int /*<<< orphan*/  pgid; int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_start (struct ccw_device*) ; 

void ccw_device_verify_start(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);

	CIO_TRACE_EVENT(4, "vrfy");
	CIO_HEX_EVENT(4, &cdev->private->dev_id, sizeof(cdev->private->dev_id));
	/* Initialize PGID data. */
	memset(cdev->private->pgid, 0, sizeof(cdev->private->pgid));
	cdev->private->pgid_valid_mask = 0;
	cdev->private->pgid_todo_mask = sch->schib.pmcw.pam;
	/*
	 * Initialize pathgroup and multipath state with target values.
	 * They may change in the course of path verification.
	 */
	cdev->private->flags.pgroup = cdev->private->options.pgroup;
	cdev->private->flags.mpath = cdev->private->options.mpath;
	cdev->private->flags.doverify = 0;
	verify_start(cdev);
}