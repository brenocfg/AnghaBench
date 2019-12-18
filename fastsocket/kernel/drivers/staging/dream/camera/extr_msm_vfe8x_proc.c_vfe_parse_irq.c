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
typedef  int uint32_t ;
struct vfe_irq_thread_msg {int vfeIrqStatus; } ;
struct isr_queue_cmd {int /*<<< orphan*/  list; int /*<<< orphan*/  vfePmData; int /*<<< orphan*/  vfeCamifStatusLocal; int /*<<< orphan*/  vfeBpcFrameInfo; int /*<<< orphan*/  vfeAsfFrameInfo; int /*<<< orphan*/  vfeInterruptStatus; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int vfeImaskPacked; scalar_t__ vfebase; int /*<<< orphan*/  tasklet_lock; int /*<<< orphan*/  tasklet_q; int /*<<< orphan*/  ack_lock; scalar_t__ vfeStopAckPending; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int VFE_IMASK_ERROR_ONLY ; 
 int VFE_IMASK_WHILE_STOPPING ; 
 scalar_t__ VFE_IRQ_CLEAR ; 
 TYPE_1__* ctrl ; 
 struct isr_queue_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfe_get_asf_frame_info (struct vfe_irq_thread_msg*) ; 
 int /*<<< orphan*/  vfe_get_camif_status (struct vfe_irq_thread_msg*) ; 
 int /*<<< orphan*/  vfe_get_demosaic_frame_info (struct vfe_irq_thread_msg*) ; 
 int /*<<< orphan*/  vfe_get_performance_monitor_data (struct vfe_irq_thread_msg*) ; 
 int /*<<< orphan*/  vfe_parse_interrupt_status (int) ; 
 int /*<<< orphan*/  vfe_read_irq_status (struct vfe_irq_thread_msg*) ; 
 int /*<<< orphan*/  vfe_tasklet ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t vfe_parse_irq(int irq_num, void *data)
{
	unsigned long flags;
	uint32_t irqStatusLocal;
	struct vfe_irq_thread_msg irq;
	struct isr_queue_cmd *qcmd;

	CDBG("vfe_parse_irq\n");

	vfe_read_irq_status(&irq);

	if (irq.vfeIrqStatus == 0) {
		CDBG("vfe_parse_irq: irq.vfeIrqStatus is 0\n");
		return IRQ_HANDLED;
	}

	qcmd = kzalloc(sizeof(struct isr_queue_cmd),
		GFP_ATOMIC);
	if (!qcmd) {
		CDBG("vfe_parse_irq: qcmd malloc failed!\n");
		return IRQ_HANDLED;
	}

	spin_lock_irqsave(&ctrl->ack_lock, flags);

	if (ctrl->vfeStopAckPending)
		irqStatusLocal =
			(VFE_IMASK_WHILE_STOPPING & irq.vfeIrqStatus);
	else
		irqStatusLocal =
			((ctrl->vfeImaskPacked | VFE_IMASK_ERROR_ONLY) &
				irq.vfeIrqStatus);

	spin_unlock_irqrestore(&ctrl->ack_lock, flags);

	/* first parse the interrupt status to local data structures. */
	qcmd->vfeInterruptStatus = vfe_parse_interrupt_status(irqStatusLocal);
	qcmd->vfeAsfFrameInfo = vfe_get_asf_frame_info(&irq);
	qcmd->vfeBpcFrameInfo = vfe_get_demosaic_frame_info(&irq);
	qcmd->vfeCamifStatusLocal = vfe_get_camif_status(&irq);
	qcmd->vfePmData = vfe_get_performance_monitor_data(&irq);

	spin_lock_irqsave(&ctrl->tasklet_lock, flags);
	list_add_tail(&qcmd->list, &ctrl->tasklet_q);
	spin_unlock_irqrestore(&ctrl->tasklet_lock, flags);
	tasklet_schedule(&vfe_tasklet);

	/* clear the pending interrupt of the same kind.*/
	writel(irq.vfeIrqStatus, ctrl->vfebase + VFE_IRQ_CLEAR);

	return IRQ_HANDLED;
}