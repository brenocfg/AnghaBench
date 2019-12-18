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
struct intel_iommu {int irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int arch_setup_dmar_msi (int) ; 
 int create_irq () ; 
 int /*<<< orphan*/  destroy_irq (int) ; 
 int /*<<< orphan*/  dmar_fault ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct intel_iommu*) ; 
 int /*<<< orphan*/  set_irq_data (int,struct intel_iommu*) ; 

int dmar_set_interrupt(struct intel_iommu *iommu)
{
	int irq, ret;

	/*
	 * Check if the fault interrupt is already initialized.
	 */
	if (iommu->irq)
		return 0;

	irq = create_irq();
	if (!irq) {
		pr_err("IOMMU: no free vectors\n");
		return -EINVAL;
	}

	set_irq_data(irq, iommu);
	iommu->irq = irq;

	ret = arch_setup_dmar_msi(irq);
	if (ret) {
		set_irq_data(irq, NULL);
		iommu->irq = 0;
		destroy_irq(irq);
		return ret;
	}

	ret = request_irq(irq, dmar_fault, 0, iommu->name, iommu);
	if (ret)
		pr_err("IOMMU: can't request irq\n");
	return ret;
}