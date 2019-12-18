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
struct copy_block_struct {int ret; int /*<<< orphan*/  kref; int /*<<< orphan*/  wait; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_2__ {scalar_t__ state; struct copy_block_struct* cmb_wait; int /*<<< orphan*/  cmb; } ;

/* Variables and functions */
 int CMF_PENDING ; 
 scalar_t__ DEV_STATE_CMFUPDATE ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int cmf_copy_block (struct ccw_device*) ; 
 int /*<<< orphan*/  cmf_copy_block_release ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct copy_block_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cmf_cmb_copy_wait(struct ccw_device *cdev)
{
	struct copy_block_struct *copy_block;
	int ret;
	unsigned long flags;

	spin_lock_irqsave(cdev->ccwlock, flags);
	if (!cdev->private->cmb) {
		ret = -ENODEV;
		goto out;
	}
	copy_block = kzalloc(sizeof(struct copy_block_struct), GFP_ATOMIC);
	if (!copy_block) {
		ret = -ENOMEM;
		goto out;
	}
	init_waitqueue_head(&copy_block->wait);
	kref_init(&copy_block->kref);

	ret = cmf_copy_block(cdev);
	if (ret != -EBUSY)
		goto out_put;

	if (cdev->private->state != DEV_STATE_ONLINE) {
		ret = -EBUSY;
		goto out_put;
	}

	cdev->private->state = DEV_STATE_CMFUPDATE;
	copy_block->ret = CMF_PENDING;
	cdev->private->cmb_wait = copy_block;

	spin_unlock_irqrestore(cdev->ccwlock, flags);
	if (wait_event_interruptible(copy_block->wait,
				     copy_block->ret != CMF_PENDING)) {
		spin_lock_irqsave(cdev->ccwlock, flags);
		if (copy_block->ret == CMF_PENDING) {
			copy_block->ret = -ERESTARTSYS;
			if (cdev->private->state == DEV_STATE_CMFUPDATE)
				cdev->private->state = DEV_STATE_ONLINE;
		}
		spin_unlock_irqrestore(cdev->ccwlock, flags);
	}
	spin_lock_irqsave(cdev->ccwlock, flags);
	cdev->private->cmb_wait = NULL;
	ret = copy_block->ret;
out_put:
	kref_put(&copy_block->kref, cmf_copy_block_release);
out:
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	return ret;
}