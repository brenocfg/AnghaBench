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
struct isci_host {int /*<<< orphan*/  scic_lock; int /*<<< orphan*/  completion_tasklet; TYPE_1__* smu_registers; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SMU_ISR_COMPLETION ; 
 int /*<<< orphan*/  sci_controller_error_handler (struct isci_host*) ; 
 scalar_t__ sci_controller_error_isr (struct isci_host*) ; 
 scalar_t__ sci_controller_isr (struct isci_host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t isci_intx_isr(int vec, void *data)
{
	irqreturn_t ret = IRQ_NONE;
	struct isci_host *ihost = data;

	if (sci_controller_isr(ihost)) {
		writel(SMU_ISR_COMPLETION, &ihost->smu_registers->interrupt_status);
		tasklet_schedule(&ihost->completion_tasklet);
		ret = IRQ_HANDLED;
	} else if (sci_controller_error_isr(ihost)) {
		spin_lock(&ihost->scic_lock);
		sci_controller_error_handler(ihost);
		spin_unlock(&ihost->scic_lock);
		ret = IRQ_HANDLED;
	}

	return ret;
}