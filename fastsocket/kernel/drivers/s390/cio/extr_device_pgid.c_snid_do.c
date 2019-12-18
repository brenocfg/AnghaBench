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
struct TYPE_8__ {int /*<<< orphan*/  pam; } ;
struct TYPE_7__ {TYPE_4__ pmcw; } ;
struct subchannel {TYPE_3__ schib; } ;
struct ccw_request {int /*<<< orphan*/  lpm; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_2__* private; TYPE_1__ dev; } ;
struct TYPE_6__ {scalar_t__ pgid_valid_mask; struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ccw_request_start (struct ccw_device*) ; 
 int /*<<< orphan*/  lpm_adjust (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snid_build_cp (struct ccw_device*) ; 
 int /*<<< orphan*/  snid_done (struct ccw_device*,int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snid_do(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_request *req = &cdev->private->req;

	/* Adjust lpm if paths are not set in pam. */
	req->lpm = lpm_adjust(req->lpm, sch->schib.pmcw.pam);
	if (!req->lpm)
		goto out_nopath;
	snid_build_cp(cdev);
	ccw_request_start(cdev);
	return;

out_nopath:
	snid_done(cdev, cdev->private->pgid_valid_mask ? 0 : -EACCES);
}