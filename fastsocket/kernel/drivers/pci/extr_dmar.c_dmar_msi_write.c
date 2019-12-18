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
struct msi_msg {int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  data; } ;
struct intel_iommu {int /*<<< orphan*/  register_lock; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ DMAR_FEADDR_REG ; 
 scalar_t__ DMAR_FEDATA_REG ; 
 scalar_t__ DMAR_FEUADDR_REG ; 
 struct intel_iommu* get_irq_data (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void dmar_msi_write(int irq, struct msi_msg *msg)
{
	struct intel_iommu *iommu = get_irq_data(irq);
	unsigned long flag;

	spin_lock_irqsave(&iommu->register_lock, flag);
	writel(msg->data, iommu->reg + DMAR_FEDATA_REG);
	writel(msg->address_lo, iommu->reg + DMAR_FEADDR_REG);
	writel(msg->address_hi, iommu->reg + DMAR_FEUADDR_REG);
	spin_unlock_irqrestore(&iommu->register_lock, flag);
}