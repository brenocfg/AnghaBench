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
struct irq_2_iommu {int sub_handle; int irte_index; int irte_mask; struct intel_iommu* iommu; } ;
struct intel_iommu {TYPE_1__* ir_table; } ;
struct TYPE_2__ {struct irte* base; } ;

/* Variables and functions */
 int qi_flush_iec (struct intel_iommu*,int,int) ; 
 int /*<<< orphan*/  set_64bit (unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clear_entries(struct irq_2_iommu *irq_iommu)
{
	struct irte *start, *entry, *end;
	struct intel_iommu *iommu;
	int index;

	if (irq_iommu->sub_handle)
		return 0;

	iommu = irq_iommu->iommu;
	index = irq_iommu->irte_index + irq_iommu->sub_handle;

	start = iommu->ir_table->base + index;
	end = start + (1 << irq_iommu->irte_mask);

	for (entry = start; entry < end; entry++) {
		set_64bit((unsigned long *)&entry->low, 0);
		set_64bit((unsigned long *)&entry->high, 0);
	}

	return qi_flush_iec(iommu, index, irq_iommu->irte_mask);
}