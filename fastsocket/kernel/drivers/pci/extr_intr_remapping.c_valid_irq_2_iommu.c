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
struct irq_2_iommu {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 struct irq_2_iommu* irq_2_iommu (unsigned int) ; 

__attribute__((used)) static struct irq_2_iommu *valid_irq_2_iommu(unsigned int irq)
{
	struct irq_2_iommu *irq_iommu;

	irq_iommu = irq_2_iommu(irq);

	if (!irq_iommu)
		return NULL;

	if (!irq_iommu->iommu)
		return NULL;

	return irq_iommu;
}