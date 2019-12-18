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
struct msi_msg {void* address_hi; void* address_lo; void* data; } ;
struct intel_iommu {int /*<<< orphan*/  register_lock; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ DMAR_FEADDR_REG ; 
 scalar_t__ DMAR_FEDATA_REG ; 
 scalar_t__ DMAR_FEUADDR_REG ; 
 struct intel_iommu* get_irq_data (int) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dmar_msi_read(int irq, struct msi_msg *msg)
{
	struct intel_iommu *iommu = get_irq_data(irq);
	unsigned long flag;

	spin_lock_irqsave(&iommu->register_lock, flag);
	msg->data = readl(iommu->reg + DMAR_FEDATA_REG);
	msg->address_lo = readl(iommu->reg + DMAR_FEADDR_REG);
	msg->address_hi = readl(iommu->reg + DMAR_FEUADDR_REG);
	spin_unlock_irqrestore(&iommu->register_lock, flag);
}