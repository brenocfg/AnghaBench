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
struct dasd_device {TYPE_1__* cdev; } ;
struct dasd_block {struct dasd_device* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DASD_STOPPED_QUIESCE ; 
 int EACCES ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (struct dasd_block*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int dasd_ioctl_resume(struct dasd_block *block)
{
	unsigned long flags;
	struct dasd_device *base;

	base = block->base;
	if (!capable (CAP_SYS_ADMIN))
		return -EACCES;

	pr_info("%s: I/O operations have been resumed "
		"on the DASD\n", dev_name(&base->cdev->dev));
	spin_lock_irqsave(get_ccwdev_lock(base->cdev), flags);
	dasd_device_remove_stop_bits(base, DASD_STOPPED_QUIESCE);
	spin_unlock_irqrestore(get_ccwdev_lock(base->cdev), flags);

	dasd_schedule_block_bh(block);
	return 0;
}