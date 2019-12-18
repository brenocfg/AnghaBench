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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct intel_iommu {int reg; int /*<<< orphan*/  register_lock; int /*<<< orphan*/  cap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DMAR_FSTS_REG ; 
 int DMA_FRCD_F ; 
 int DMA_FSTS_PPF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PRIMARY_FAULT_REG_LEN ; 
 int cap_fault_reg_offset (int /*<<< orphan*/ ) ; 
 int cap_num_fault_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_frcd_fault_reason (int) ; 
 int /*<<< orphan*/  dma_frcd_page_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_frcd_source_id (int) ; 
 int dma_frcd_type (int) ; 
 int dma_fsts_fault_record_index (int) ; 
 int /*<<< orphan*/  dmar_fault_do_one (struct intel_iommu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_readq (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int readl (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int) ; 

irqreturn_t dmar_fault(int irq, void *dev_id)
{
	struct intel_iommu *iommu = dev_id;
	int reg, fault_index;
	u32 fault_status;
	unsigned long flag;

	spin_lock_irqsave(&iommu->register_lock, flag);
	fault_status = readl(iommu->reg + DMAR_FSTS_REG);
	if (fault_status)
		pr_err("DRHD: handling fault status reg %x\n", fault_status);

	/* TBD: ignore advanced fault log currently */
	if (!(fault_status & DMA_FSTS_PPF))
		goto clear_rest;

	fault_index = dma_fsts_fault_record_index(fault_status);
	reg = cap_fault_reg_offset(iommu->cap);
	while (1) {
		u8 fault_reason;
		u16 source_id;
		u64 guest_addr;
		int type;
		u32 data;

		/* highest 32 bits */
		data = readl(iommu->reg + reg +
				fault_index * PRIMARY_FAULT_REG_LEN + 12);
		if (!(data & DMA_FRCD_F))
			break;

		fault_reason = dma_frcd_fault_reason(data);
		type = dma_frcd_type(data);

		data = readl(iommu->reg + reg +
				fault_index * PRIMARY_FAULT_REG_LEN + 8);
		source_id = dma_frcd_source_id(data);

		guest_addr = dmar_readq(iommu->reg + reg +
				fault_index * PRIMARY_FAULT_REG_LEN);
		guest_addr = dma_frcd_page_addr(guest_addr);
		/* clear the fault */
		writel(DMA_FRCD_F, iommu->reg + reg +
			fault_index * PRIMARY_FAULT_REG_LEN + 12);

		spin_unlock_irqrestore(&iommu->register_lock, flag);

		dmar_fault_do_one(iommu, type, fault_reason,
				source_id, guest_addr);

		fault_index++;
		if (fault_index >= cap_num_fault_regs(iommu->cap))
			fault_index = 0;
		spin_lock_irqsave(&iommu->register_lock, flag);
	}
clear_rest:
	/* clear all the other faults */
	fault_status = readl(iommu->reg + DMAR_FSTS_REG);
	writel(fault_status, iommu->reg + DMAR_FSTS_REG);

	spin_unlock_irqrestore(&iommu->register_lock, flag);
	return IRQ_HANDLED;
}