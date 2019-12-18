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
struct irte {int dummy; } ;
struct irq_2_iommu {int irte_index; int sub_handle; TYPE_1__* iommu; } ;
struct TYPE_4__ {struct irte* base; } ;
struct TYPE_3__ {TYPE_2__* ir_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_2_ir_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct irq_2_iommu* valid_irq_2_iommu (int) ; 

int get_irte(int irq, struct irte *entry)
{
	int index;
	struct irq_2_iommu *irq_iommu;
	unsigned long flags;

	if (!entry)
		return -1;

	spin_lock_irqsave(&irq_2_ir_lock, flags);
	irq_iommu = valid_irq_2_iommu(irq);
	if (!irq_iommu) {
		spin_unlock_irqrestore(&irq_2_ir_lock, flags);
		return -1;
	}

	index = irq_iommu->irte_index + irq_iommu->sub_handle;
	*entry = *(irq_iommu->iommu->ir_table->base + index);

	spin_unlock_irqrestore(&irq_2_ir_lock, flags);
	return 0;
}