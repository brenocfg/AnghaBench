#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct driver_data {int /*<<< orphan*/ * queue; TYPE_2__* disk; int /*<<< orphan*/  index; int /*<<< orphan*/  dd_flag; scalar_t__ mtip_svc_handler; TYPE_1__* port; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {scalar_t__ queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  svc_wait; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_DDF_INIT_DONE_BIT ; 
 int /*<<< orphan*/  MTIP_PF_SVC_THD_STOP_BIT ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_2__*) ; 
 TYPE_3__* disk_to_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct kobject* kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  mtip_hw_debugfs_exit (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_exit (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_sysfs_exit (struct driver_data*,struct kobject*) ; 
 int /*<<< orphan*/  put_disk (TYPE_2__*) ; 
 int /*<<< orphan*/  rssd_index_ida ; 
 int /*<<< orphan*/  rssd_index_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_block_remove(struct driver_data *dd)
{
	struct kobject *kobj;

	if (dd->mtip_svc_handler) {
		set_bit(MTIP_PF_SVC_THD_STOP_BIT, &dd->port->flags);
		wake_up_interruptible(&dd->port->svc_wait);
		kthread_stop(dd->mtip_svc_handler);
	}

	/* Clean up the sysfs attributes, if created */
	if (test_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag)) {
		kobj = kobject_get(&disk_to_dev(dd->disk)->kobj);
		if (kobj) {
			mtip_hw_sysfs_exit(dd, kobj);
			kobject_put(kobj);
		}
	}
	mtip_hw_debugfs_exit(dd);

	/*
	 * Delete our gendisk structure. This also removes the device
	 * from /dev
	 */
	if (dd->disk) {
		if (dd->disk->queue)
			del_gendisk(dd->disk);
		else
			put_disk(dd->disk);
	}

	spin_lock(&rssd_index_lock);
	ida_remove(&rssd_index_ida, dd->index);
	spin_unlock(&rssd_index_lock);

	blk_cleanup_queue(dd->queue);
	dd->disk  = NULL;
	dd->queue = NULL;

	/* De-initialize the protocol layer. */
	mtip_hw_exit(dd);

	return 0;
}