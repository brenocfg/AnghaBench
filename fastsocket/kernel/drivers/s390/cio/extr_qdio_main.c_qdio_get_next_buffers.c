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
struct qdio_q {int first_to_kick; int first_to_check; int qdio_error; TYPE_2__* irq_ptr; } ;
struct qdio_irq {struct qdio_q** input_qs; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ QDIO_IRQ_STATE_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_check_outbound_after_thinint (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_inbound_q_moved (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_sync_after_thinint (struct qdio_q*) ; 
 int /*<<< orphan*/  queue_irqs_enabled (struct qdio_q*) ; 
 int sub_buf (int,int) ; 
 scalar_t__ unlikely (int) ; 

int qdio_get_next_buffers(struct ccw_device *cdev, int nr, int *bufnr,
			  int *error)
{
	struct qdio_q *q;
	int start, end;
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;

	if (!irq_ptr)
		return -ENODEV;
	q = irq_ptr->input_qs[nr];
	WARN_ON(queue_irqs_enabled(q));

	qdio_sync_after_thinint(q);

	/*
	 * The interrupt could be caused by a PCI request. Check the
	 * PCI capable outbound queues.
	 */
	qdio_check_outbound_after_thinint(q);

	if (!qdio_inbound_q_moved(q))
		return 0;

	/* Note: upper-layer MUST stop processing immediately here ... */
	if (unlikely(q->irq_ptr->state != QDIO_IRQ_STATE_ACTIVE))
		return -EIO;

	start = q->first_to_kick;
	end = q->first_to_check;
	*bufnr = start;
	*error = q->qdio_error;

	/* for the next time */
	q->first_to_kick = end;
	q->qdio_error = 0;
	return sub_buf(end, start);
}