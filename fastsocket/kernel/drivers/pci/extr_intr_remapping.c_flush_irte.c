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
struct irq_2_iommu {int irte_index; int sub_handle; int /*<<< orphan*/  irte_mask; struct intel_iommu* iommu; } ;
struct intel_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_2_ir_lock ; 
 int qi_flush_iec (struct intel_iommu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct irq_2_iommu* valid_irq_2_iommu (int) ; 

int flush_irte(int irq)
{
	int rc;
	int index;
	struct intel_iommu *iommu;
	struct irq_2_iommu *irq_iommu;
	unsigned long flags;

	spin_lock_irqsave(&irq_2_ir_lock, flags);
	irq_iommu = valid_irq_2_iommu(irq);
	if (!irq_iommu) {
		spin_unlock_irqrestore(&irq_2_ir_lock, flags);
		return -1;
	}

	iommu = irq_iommu->iommu;

	index = irq_iommu->irte_index + irq_iommu->sub_handle;

	rc = qi_flush_iec(iommu, index, irq_iommu->irte_mask);
	spin_unlock_irqrestore(&irq_2_ir_lock, flags);

	return rc;
}