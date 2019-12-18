#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lcs_channel {TYPE_1__* ccwdev; int /*<<< orphan*/  state; scalar_t__ io_idx; scalar_t__ ccws; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DOIO_ALLOW_SUSPEND ; 
 int DOIO_DENY_PREFETCH ; 
 int /*<<< orphan*/  LCS_CH_STATE_RUNNING ; 
 int /*<<< orphan*/  LCS_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ccw_device_start (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_start_channel(struct lcs_channel *channel)
{
	unsigned long flags;
	int rc;

	LCS_DBF_TEXT_(4, trace,"ssch%s", dev_name(&channel->ccwdev->dev));
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_start(channel->ccwdev,
			      channel->ccws + channel->io_idx, 0, 0,
			      DOIO_DENY_PREFETCH | DOIO_ALLOW_SUSPEND);
	if (rc == 0)
		channel->state = LCS_CH_STATE_RUNNING;
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	if (rc) {
		LCS_DBF_TEXT_(4,trace,"essh%s",
			      dev_name(&channel->ccwdev->dev));
		dev_err(&channel->ccwdev->dev,
			"Starting an LCS device resulted in an error,"
			" rc=%d!\n", rc);
	}
	return rc;
}