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
struct ccw_request {int lpm; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {int pgid_valid_mask; struct ccw_request req; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  snid_do (struct ccw_device*) ; 
 int /*<<< orphan*/  snid_done (struct ccw_device*,int) ; 

__attribute__((used)) static void snid_callback(struct ccw_device *cdev, void *data, int rc)
{
	struct ccw_request *req = &cdev->private->req;

	if (rc == 0)
		cdev->private->pgid_valid_mask |= req->lpm;
	else if (rc != -EACCES)
		goto err;
	req->lpm >>= 1;
	snid_do(cdev);
	return;

err:
	snid_done(cdev, rc);
}