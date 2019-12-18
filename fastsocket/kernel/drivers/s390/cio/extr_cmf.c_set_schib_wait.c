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
typedef  int /*<<< orphan*/  u32 ;
struct set_schib_struct {int mbfc; unsigned long address; int ret; int /*<<< orphan*/  kref; int /*<<< orphan*/  wait; int /*<<< orphan*/  mme; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_2__ {scalar_t__ state; struct set_schib_struct* cmb_wait; int /*<<< orphan*/  cmb; } ;

/* Variables and functions */
 int CMF_PENDING ; 
 scalar_t__ DEV_STATE_CMFCHANGE ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cmf_set_schib_release ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct set_schib_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int set_schib (struct ccw_device*,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_schib_wait(struct ccw_device *cdev, u32 mme,
				int mbfc, unsigned long address)
{
	struct set_schib_struct *set_data;
	int ret;

	spin_lock_irq(cdev->ccwlock);
	if (!cdev->private->cmb) {
		ret = -ENODEV;
		goto out;
	}
	set_data = kzalloc(sizeof(struct set_schib_struct), GFP_ATOMIC);
	if (!set_data) {
		ret = -ENOMEM;
		goto out;
	}
	init_waitqueue_head(&set_data->wait);
	kref_init(&set_data->kref);
	set_data->mme = mme;
	set_data->mbfc = mbfc;
	set_data->address = address;

	ret = set_schib(cdev, mme, mbfc, address);
	if (ret != -EBUSY)
		goto out_put;

	if (cdev->private->state != DEV_STATE_ONLINE) {
		/* if the device is not online, don't even try again */
		ret = -EBUSY;
		goto out_put;
	}

	cdev->private->state = DEV_STATE_CMFCHANGE;
	set_data->ret = CMF_PENDING;
	cdev->private->cmb_wait = set_data;

	spin_unlock_irq(cdev->ccwlock);
	if (wait_event_interruptible(set_data->wait,
				     set_data->ret != CMF_PENDING)) {
		spin_lock_irq(cdev->ccwlock);
		if (set_data->ret == CMF_PENDING) {
			set_data->ret = -ERESTARTSYS;
			if (cdev->private->state == DEV_STATE_CMFCHANGE)
				cdev->private->state = DEV_STATE_ONLINE;
		}
		spin_unlock_irq(cdev->ccwlock);
	}
	spin_lock_irq(cdev->ccwlock);
	cdev->private->cmb_wait = NULL;
	ret = set_data->ret;
out_put:
	kref_put(&set_data->kref, cmf_set_schib_release);
out:
	spin_unlock_irq(cdev->ccwlock);
	return ret;
}