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
struct irte {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct irq_2_iommu {int irte_index; int sub_handle; struct intel_iommu* iommu; } ;
struct intel_iommu {TYPE_1__* ir_table; } ;
struct TYPE_2__ {struct irte* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iommu_flush_cache (struct intel_iommu*,struct irte*,int) ; 
 int /*<<< orphan*/  irq_2_ir_lock ; 
 int qi_flush_iec (struct intel_iommu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_64bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct irq_2_iommu* valid_irq_2_iommu (int) ; 

int modify_irte(int irq, struct irte *irte_modified)
{
	int rc;
	int index;
	struct irte *irte;
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
	irte = &iommu->ir_table->base[index];

	set_64bit((unsigned long *)&irte->low, irte_modified->low);
	set_64bit((unsigned long *)&irte->high, irte_modified->high);
	__iommu_flush_cache(iommu, irte, sizeof(*irte));

	rc = qi_flush_iec(iommu, index, 0);
	spin_unlock_irqrestore(&irq_2_ir_lock, flags);

	return rc;
}