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
struct intel_iommu {int /*<<< orphan*/  register_lock; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ DMAR_FECTL_REG ; 
 struct intel_iommu* get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void dmar_msi_unmask(unsigned int irq)
{
	struct intel_iommu *iommu = get_irq_data(irq);
	unsigned long flag;

	/* unmask it */
	spin_lock_irqsave(&iommu->register_lock, flag);
	writel(0, iommu->reg + DMAR_FECTL_REG);
	/* Read a reg to force flush the post write */
	readl(iommu->reg + DMAR_FECTL_REG);
	spin_unlock_irqrestore(&iommu->register_lock, flag);
}