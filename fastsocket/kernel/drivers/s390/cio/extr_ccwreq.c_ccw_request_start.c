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
struct ccw_request {int mask; int lpm; scalar_t__ cancel; scalar_t__ done; scalar_t__ drc; int /*<<< orphan*/  maxretries; int /*<<< orphan*/  retries; scalar_t__ singlepath; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ccwreq_do (struct ccw_device*) ; 
 int /*<<< orphan*/  ccwreq_stop (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int lpm_adjust (int,int) ; 

void ccw_request_start(struct ccw_device *cdev)
{
	struct ccw_request *req = &cdev->private->req;

	if (req->singlepath) {
		/* Try all paths twice to counter link flapping. */
		req->mask = 0x8080;
	} else
		req->mask = req->lpm;

	req->retries	= req->maxretries;
	req->mask	= lpm_adjust(req->mask, req->lpm);
	req->drc	= 0;
	req->done	= 0;
	req->cancel	= 0;
	if (!req->mask)
		goto out_nopath;
	ccwreq_do(cdev);
	return;

out_nopath:
	ccwreq_stop(cdev, -EACCES);
}