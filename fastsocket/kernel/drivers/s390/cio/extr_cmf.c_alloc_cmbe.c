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
struct cmbe {int size; struct cmbe* last_block; struct cmbe* hw_block; } ;
struct cmb_data {int size; struct cmb_data* last_block; struct cmb_data* hw_block; } ;
struct ccw_device {TYPE_1__* private; int /*<<< orphan*/  ccwlock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmb_list; struct cmbe* cmb; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ cmb_area ; 
 int /*<<< orphan*/  cmf_activate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct cmbe*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_cmbe(struct ccw_device *cdev)
{
	struct cmbe *cmbe;
	struct cmb_data *cmb_data;
	int ret;

	cmbe = kzalloc (sizeof (*cmbe) * 2, GFP_KERNEL);
	if (!cmbe)
		return -ENOMEM;
	cmb_data = kzalloc(sizeof(struct cmb_data), GFP_KERNEL);
	if (!cmb_data) {
		ret = -ENOMEM;
		goto out_free;
	}
	cmb_data->last_block = kzalloc(sizeof(struct cmbe), GFP_KERNEL);
	if (!cmb_data->last_block) {
		ret = -ENOMEM;
		goto out_free;
	}
	cmb_data->size = sizeof(struct cmbe);
	spin_lock_irq(cdev->ccwlock);
	if (cdev->private->cmb) {
		spin_unlock_irq(cdev->ccwlock);
		ret = -EBUSY;
		goto out_free;
	}
	cmb_data->hw_block = cmbe;
	cdev->private->cmb = cmb_data;
	spin_unlock_irq(cdev->ccwlock);

	/* activate global measurement if this is the first channel */
	spin_lock(&cmb_area.lock);
	if (list_empty(&cmb_area.list))
		cmf_activate(NULL, 1);
	list_add_tail(&cdev->private->cmb_list, &cmb_area.list);
	spin_unlock(&cmb_area.lock);

	return 0;
out_free:
	if (cmb_data)
		kfree(cmb_data->last_block);
	kfree(cmb_data);
	kfree(cmbe);
	return ret;
}