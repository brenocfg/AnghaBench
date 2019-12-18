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
struct TYPE_8__ {int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__ pmcw; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_4__ schid; TYPE_2__ schib; } ;
struct TYPE_7__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  devno; } ;
struct ccw_device_private {int /*<<< orphan*/  timer; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  cmb_list; int /*<<< orphan*/  state; TYPE_4__ schid; TYPE_3__ dev_id; } ;
struct ccw_device {struct ccw_device_private* private; int /*<<< orphan*/  ccwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_NOT_OPER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccw_device_init_count ; 
 int /*<<< orphan*/  ccw_device_recognition (struct ccw_device*) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sch_set_cdev (struct subchannel*,struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void io_subchannel_recog(struct ccw_device *cdev, struct subchannel *sch)
{
	struct ccw_device_private *priv;

	cdev->ccwlock = sch->lock;

	/* Init private data. */
	priv = cdev->private;
	priv->dev_id.devno = sch->schib.pmcw.dev;
	priv->dev_id.ssid = sch->schid.ssid;
	priv->schid = sch->schid;
	priv->state = DEV_STATE_NOT_OPER;
	INIT_LIST_HEAD(&priv->cmb_list);
	init_waitqueue_head(&priv->wait_q);
	init_timer(&priv->timer);

	/* Increase counter of devices currently in recognition. */
	atomic_inc(&ccw_device_init_count);

	/* Start async. device sensing. */
	spin_lock_irq(sch->lock);
	sch_set_cdev(sch, cdev);
	ccw_device_recognition(cdev);
	spin_unlock_irq(sch->lock);
}