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
typedef  int /*<<< orphan*/  u16 ;
struct irq_2_iommu {int irte_index; int /*<<< orphan*/  sub_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_2_ir_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct irq_2_iommu* valid_irq_2_iommu (int) ; 

int map_irq_to_irte_handle(int irq, u16 *sub_handle)
{
	int index;
	struct irq_2_iommu *irq_iommu;
	unsigned long flags;

	spin_lock_irqsave(&irq_2_ir_lock, flags);
	irq_iommu = valid_irq_2_iommu(irq);
	if (!irq_iommu) {
		spin_unlock_irqrestore(&irq_2_ir_lock, flags);
		return -1;
	}

	*sub_handle = irq_iommu->sub_handle;
	index = irq_iommu->irte_index;
	spin_unlock_irqrestore(&irq_2_ir_lock, flags);
	return index;
}