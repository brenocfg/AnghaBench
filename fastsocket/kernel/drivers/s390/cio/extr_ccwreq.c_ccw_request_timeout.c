#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int dummy; } ;
struct ccw_request {int /*<<< orphan*/  drc; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_2__* private; TYPE_1__ dev; } ;
struct TYPE_4__ {struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  ccwreq_next_path (struct ccw_device*) ; 
 int /*<<< orphan*/  ccwreq_stop (struct ccw_device*,int) ; 
 int cio_clear (struct subchannel*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

void ccw_request_timeout(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_request *req = &cdev->private->req;
	int rc;

	if (!ccwreq_next_path(cdev)) {
		/* set the final return code for this request */
		req->drc = -ETIME;
	}
	rc = cio_clear(sch);
	if (rc)
		goto err;
	return;

err:
	ccwreq_stop(cdev, rc);
}