#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct list_head {int dummy; } ;
struct dasd_device {int /*<<< orphan*/  cdev; int /*<<< orphan*/  tasklet_scheduled; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  __dasd_device_check_expire (struct dasd_device*) ; 
 int /*<<< orphan*/  __dasd_device_check_path_events (struct dasd_device*) ; 
 int /*<<< orphan*/  __dasd_device_process_ccw_queue (struct dasd_device*,struct list_head*) ; 
 int /*<<< orphan*/  __dasd_device_process_final_queue (struct dasd_device*,struct list_head*) ; 
 int /*<<< orphan*/  __dasd_device_start_head (struct dasd_device*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_waitq ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_device_tasklet(struct dasd_device *device)
{
	struct list_head final_queue;

	atomic_set (&device->tasklet_scheduled, 0);
	INIT_LIST_HEAD(&final_queue);
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Check expire time of first request on the ccw queue. */
	__dasd_device_check_expire(device);
	/* find final requests on ccw queue */
	__dasd_device_process_ccw_queue(device, &final_queue);
	__dasd_device_check_path_events(device);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	/* Now call the callback function of requests with final status */
	__dasd_device_process_final_queue(device, &final_queue);
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Now check if the head of the ccw queue needs to be started. */
	__dasd_device_start_head(device);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	if (waitqueue_active(&shutdown_waitq))
		wake_up(&shutdown_waitq);
	dasd_put_device(device);
}