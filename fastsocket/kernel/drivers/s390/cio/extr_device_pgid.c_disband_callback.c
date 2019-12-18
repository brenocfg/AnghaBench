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
struct TYPE_6__ {scalar_t__ mp; } ;
struct subchannel {TYPE_2__ config; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_4__* private; TYPE_3__ dev; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {scalar_t__ mpath; } ;
struct TYPE_8__ {TYPE_1__ flags; struct ccw_dev_id dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ccw_device_disband_done (struct ccw_device*,int) ; 
 int cio_commit_config (struct subchannel*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disband_callback(struct ccw_device *cdev, void *data, int rc)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_dev_id *id = &cdev->private->dev_id;

	if (rc)
		goto out;
	/* Ensure consistent multipathing state at device and channel. */
	cdev->private->flags.mpath = 0;
	if (sch->config.mp) {
		sch->config.mp = 0;
		rc = cio_commit_config(sch);
	}
out:
	CIO_MSG_EVENT(0, "disb: device 0.%x.%04x: rc=%d\n", id->ssid, id->devno,
		      rc);
	ccw_device_disband_done(cdev, rc);
}