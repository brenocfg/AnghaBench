#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int sch_no; } ;
struct TYPE_10__ {scalar_t__ cda; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_8__ {int /*<<< orphan*/  count; int /*<<< orphan*/  cmd; } ;
struct qdio_irq {int state; int /*<<< orphan*/  setup_mutex; TYPE_4__ schid; TYPE_5__ ccw; TYPE_3__ aqueue; } ;
struct ccw_device {TYPE_2__* private; } ;
struct TYPE_6__ {int /*<<< orphan*/  sch_no; } ;
struct TYPE_7__ {scalar_t__ state; struct qdio_irq* qdio_data; TYPE_1__ schid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCWDEV_REPORT_ALL ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int) ; 
 int /*<<< orphan*/  DBF_EVENT (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int /*<<< orphan*/  DOIO_DENY_PREFETCH ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  QDIO_DOING_ACTIVATE ; 
 int /*<<< orphan*/  QDIO_IRQ_STATE_ACTIVE ; 
#define  QDIO_IRQ_STATE_ERR 129 
 int QDIO_IRQ_STATE_INACTIVE ; 
#define  QDIO_IRQ_STATE_STOPPED 128 
 int /*<<< orphan*/  ccw_device_set_options (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int ccw_device_start (struct ccw_device*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 scalar_t__ is_thinint_irq (struct qdio_irq*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdio_set_state (struct qdio_irq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tiqdio_add_input_queues (struct qdio_irq*) ; 

int qdio_activate(struct ccw_device *cdev)
{
	struct qdio_irq *irq_ptr;
	int rc;
	unsigned long saveflags;

	DBF_EVENT("qactivate:%4x", cdev->private->schid.sch_no);

	irq_ptr = cdev->private->qdio_data;
	if (!irq_ptr)
		return -ENODEV;

	if (cdev->private->state != DEV_STATE_ONLINE)
		return -EINVAL;

	mutex_lock(&irq_ptr->setup_mutex);
	if (irq_ptr->state == QDIO_IRQ_STATE_INACTIVE) {
		rc = -EBUSY;
		goto out;
	}

	irq_ptr->ccw.cmd_code = irq_ptr->aqueue.cmd;
	irq_ptr->ccw.flags = CCW_FLAG_SLI;
	irq_ptr->ccw.count = irq_ptr->aqueue.count;
	irq_ptr->ccw.cda = 0;

	spin_lock_irqsave(get_ccwdev_lock(cdev), saveflags);
	ccw_device_set_options(cdev, CCWDEV_REPORT_ALL);

	rc = ccw_device_start(cdev, &irq_ptr->ccw, QDIO_DOING_ACTIVATE,
			      0, DOIO_DENY_PREFETCH);
	if (rc) {
		DBF_ERROR("%4x act IO ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%4x", rc);
	}
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), saveflags);

	if (rc)
		goto out;

	if (is_thinint_irq(irq_ptr))
		tiqdio_add_input_queues(irq_ptr);

	/* wait for subchannel to become active */
	msleep(5);

	switch (irq_ptr->state) {
	case QDIO_IRQ_STATE_STOPPED:
	case QDIO_IRQ_STATE_ERR:
		rc = -EIO;
		break;
	default:
		qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ACTIVE);
		rc = 0;
	}
out:
	mutex_unlock(&irq_ptr->setup_mutex);
	return rc;
}