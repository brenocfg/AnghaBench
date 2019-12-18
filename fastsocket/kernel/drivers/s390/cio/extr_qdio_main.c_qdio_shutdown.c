#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sch_no; } ;
struct qdio_irq {scalar_t__ state; int /*<<< orphan*/  setup_mutex; scalar_t__ orig_handler; TYPE_2__ schid; } ;
struct ccw_device {scalar_t__ handler; TYPE_3__* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  sch_no; } ;
struct TYPE_6__ {int /*<<< orphan*/  wait_q; TYPE_1__ schid; struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int) ; 
 int /*<<< orphan*/  DBF_EVENT (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int HZ ; 
 int /*<<< orphan*/  QDIO_DOING_CLEANUP ; 
 int QDIO_FLAG_CLEANUP_USING_CLEAR ; 
 scalar_t__ QDIO_IRQ_STATE_CLEANUP ; 
 scalar_t__ QDIO_IRQ_STATE_ERR ; 
 scalar_t__ QDIO_IRQ_STATE_INACTIVE ; 
 scalar_t__ QDIO_IRQ_STATE_STOPPED ; 
 int ccw_device_clear (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int ccw_device_halt (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ qdio_int_handler ; 
 int /*<<< orphan*/  qdio_set_state (struct qdio_irq*,scalar_t__) ; 
 int /*<<< orphan*/  qdio_shutdown_debug_entries (struct qdio_irq*,struct ccw_device*) ; 
 int /*<<< orphan*/  qdio_shutdown_queues (struct ccw_device*) ; 
 int /*<<< orphan*/  qdio_shutdown_thinint (struct qdio_irq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tiqdio_remove_input_queues (struct qdio_irq*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int qdio_shutdown(struct ccw_device *cdev, int how)
{
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;
	int rc;
	unsigned long flags;

	if (!irq_ptr)
		return -ENODEV;

	BUG_ON(irqs_disabled());
	DBF_EVENT("qshutdown:%4x", cdev->private->schid.sch_no);

	mutex_lock(&irq_ptr->setup_mutex);
	/*
	 * Subchannel was already shot down. We cannot prevent being called
	 * twice since cio may trigger a shutdown asynchronously.
	 */
	if (irq_ptr->state == QDIO_IRQ_STATE_INACTIVE) {
		mutex_unlock(&irq_ptr->setup_mutex);
		return 0;
	}

	/*
	 * Indicate that the device is going down. Scheduling the queue
	 * tasklets is forbidden from here on.
	 */
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_STOPPED);

	tiqdio_remove_input_queues(irq_ptr);
	qdio_shutdown_queues(cdev);
	qdio_shutdown_debug_entries(irq_ptr, cdev);

	/* cleanup subchannel */
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);

	if (how & QDIO_FLAG_CLEANUP_USING_CLEAR)
		rc = ccw_device_clear(cdev, QDIO_DOING_CLEANUP);
	else
		/* default behaviour is halt */
		rc = ccw_device_halt(cdev, QDIO_DOING_CLEANUP);
	if (rc) {
		DBF_ERROR("%4x SHUTD ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%4d", rc);
		goto no_cleanup;
	}

	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_CLEANUP);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	wait_event_interruptible_timeout(cdev->private->wait_q,
		irq_ptr->state == QDIO_IRQ_STATE_INACTIVE ||
		irq_ptr->state == QDIO_IRQ_STATE_ERR,
		10 * HZ);
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);

no_cleanup:
	qdio_shutdown_thinint(irq_ptr);

	/* restore interrupt handler */
	if ((void *)cdev->handler == (void *)qdio_int_handler)
		cdev->handler = irq_ptr->orig_handler;
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_INACTIVE);
	mutex_unlock(&irq_ptr->setup_mutex);
	if (rc)
		return rc;
	return 0;
}