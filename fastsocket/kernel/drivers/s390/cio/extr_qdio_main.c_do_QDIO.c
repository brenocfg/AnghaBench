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
struct qdio_irq {scalar_t__ state; int /*<<< orphan*/ * output_qs; int /*<<< orphan*/ * input_qs; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct qdio_irq*,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned int QDIO_FLAG_SYNC_INPUT ; 
 unsigned int QDIO_FLAG_SYNC_OUTPUT ; 
 scalar_t__ QDIO_IRQ_STATE_ACTIVE ; 
 unsigned int QDIO_MAX_BUFFERS_PER_Q ; 
 int handle_inbound (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int handle_outbound (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

int do_QDIO(struct ccw_device *cdev, unsigned int callflags,
	    int q_nr, unsigned int bufnr, unsigned int count)
{
	struct qdio_irq *irq_ptr;


	if (bufnr >= QDIO_MAX_BUFFERS_PER_Q || count > QDIO_MAX_BUFFERS_PER_Q)
		return -EINVAL;

	irq_ptr = cdev->private->qdio_data;
	if (!irq_ptr)
		return -ENODEV;

	DBF_DEV_EVENT(DBF_INFO, irq_ptr,
		      "do%02x b:%02x c:%02x", callflags, bufnr, count);

	if (irq_ptr->state != QDIO_IRQ_STATE_ACTIVE)
		return -EBUSY;

	if (callflags & QDIO_FLAG_SYNC_INPUT)
		return handle_inbound(irq_ptr->input_qs[q_nr],
				      callflags, bufnr, count);
	else if (callflags & QDIO_FLAG_SYNC_OUTPUT)
		return handle_outbound(irq_ptr->output_qs[q_nr],
				       callflags, bufnr, count);
	return -EINVAL;
}