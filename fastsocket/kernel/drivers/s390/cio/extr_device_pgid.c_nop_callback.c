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
struct subchannel {int vpm; } ;
struct ccw_request {int lpm; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_2__* private; TYPE_1__ dev; } ;
struct TYPE_4__ {struct ccw_request req; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  nop_do (struct ccw_device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_done (struct ccw_device*,int) ; 

__attribute__((used)) static void nop_callback(struct ccw_device *cdev, void *data, int rc)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_request *req = &cdev->private->req;

	if (rc == 0)
		sch->vpm |= req->lpm;
	else if (rc != -EACCES)
		goto err;
	req->lpm >>= 1;
	nop_do(cdev);
	return;

err:
	verify_done(cdev, rc);
}