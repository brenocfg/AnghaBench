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
struct TYPE_3__ {int /*<<< orphan*/  resetAckIrq; } ;
struct TYPE_4__ {scalar_t__ vfebase; int /*<<< orphan*/  vfeImaskPacked; TYPE_1__ vfeImaskLocal; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VFE_CLEAR_ALL_IRQS ; 
 int /*<<< orphan*/  VFE_DISABLE_ALL_IRQS ; 
 scalar_t__ VFE_GLOBAL_RESET_CMD ; 
 scalar_t__ VFE_IRQ_CLEAR ; 
 scalar_t__ VFE_IRQ_COMPOSITE_MASK ; 
 scalar_t__ VFE_IRQ_MASK ; 
 int /*<<< orphan*/  VFE_RESET_UPON_RESET_CMD ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  vfe_irq_pack (TYPE_1__) ; 
 int /*<<< orphan*/  vfe_reset_internal_variables () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void vfe_reset(void)
{
	vfe_reset_internal_variables();

	ctrl->vfeImaskLocal.resetAckIrq = TRUE;
	ctrl->vfeImaskPacked = vfe_irq_pack(ctrl->vfeImaskLocal);

	/* disable all interrupts. */
	writel(VFE_DISABLE_ALL_IRQS,
		ctrl->vfebase + VFE_IRQ_COMPOSITE_MASK);

	/* clear all pending interrupts*/
	writel(VFE_CLEAR_ALL_IRQS,
		ctrl->vfebase + VFE_IRQ_CLEAR);

	/* enable reset_ack interrupt.  */
	writel(ctrl->vfeImaskPacked,
		ctrl->vfebase + VFE_IRQ_MASK);

	writel(VFE_RESET_UPON_RESET_CMD,
		ctrl->vfebase + VFE_GLOBAL_RESET_CMD);
}