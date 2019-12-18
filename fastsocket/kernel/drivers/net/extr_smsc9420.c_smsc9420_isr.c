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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct smsc9420_pdata {int software_irq_signal; int /*<<< orphan*/  int_lock; int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; int /*<<< orphan*/  base_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMAC_INTR_ENA ; 
 int DMAC_INTR_ENA_RX_ ; 
 int /*<<< orphan*/  DMAC_STATUS ; 
 int DMAC_STS_NIS_ ; 
 int DMAC_STS_RX_ ; 
 int DMAC_STS_TX_ ; 
 int /*<<< orphan*/  INT_CFG ; 
 int INT_CFG_IRQ_EN_ ; 
 int INT_CFG_IRQ_INT_ ; 
 int /*<<< orphan*/  INT_CTL ; 
 int INT_CTL_SW_INT_EN_ ; 
 int /*<<< orphan*/  INT_STAT ; 
 int INT_STAT_DMAC_INT_ ; 
 int INT_STAT_SW_INT_ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  smsc9420_pci_flush_write (struct smsc9420_pdata*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t smsc9420_isr(int irq, void *dev_id)
{
	struct smsc9420_pdata *pd = dev_id;
	u32 int_cfg, int_sts, int_ctl;
	irqreturn_t ret = IRQ_NONE;
	ulong flags;

	BUG_ON(!pd);
	BUG_ON(!pd->base_addr);

	int_cfg = smsc9420_reg_read(pd, INT_CFG);

	/* check if it's our interrupt */
	if ((int_cfg & (INT_CFG_IRQ_EN_ | INT_CFG_IRQ_INT_)) !=
	    (INT_CFG_IRQ_EN_ | INT_CFG_IRQ_INT_))
		return IRQ_NONE;

	int_sts = smsc9420_reg_read(pd, INT_STAT);

	if (likely(INT_STAT_DMAC_INT_ & int_sts)) {
		u32 status = smsc9420_reg_read(pd, DMAC_STATUS);
		u32 ints_to_clear = 0;

		if (status & DMAC_STS_TX_) {
			ints_to_clear |= (DMAC_STS_TX_ | DMAC_STS_NIS_);
			netif_wake_queue(pd->dev);
		}

		if (status & DMAC_STS_RX_) {
			/* mask RX DMAC interrupts */
			u32 dma_intr_ena = smsc9420_reg_read(pd, DMAC_INTR_ENA);
			dma_intr_ena &= (~DMAC_INTR_ENA_RX_);
			smsc9420_reg_write(pd, DMAC_INTR_ENA, dma_intr_ena);
			smsc9420_pci_flush_write(pd);

			ints_to_clear |= (DMAC_STS_RX_ | DMAC_STS_NIS_);
			napi_schedule(&pd->napi);
		}

		if (ints_to_clear)
			smsc9420_reg_write(pd, DMAC_STATUS, ints_to_clear);

		ret = IRQ_HANDLED;
	}

	if (unlikely(INT_STAT_SW_INT_ & int_sts)) {
		/* mask software interrupt */
		spin_lock_irqsave(&pd->int_lock, flags);
		int_ctl = smsc9420_reg_read(pd, INT_CTL);
		int_ctl &= (~INT_CTL_SW_INT_EN_);
		smsc9420_reg_write(pd, INT_CTL, int_ctl);
		spin_unlock_irqrestore(&pd->int_lock, flags);

		smsc9420_reg_write(pd, INT_STAT, INT_STAT_SW_INT_);
		pd->software_irq_signal = true;
		smp_wmb();

		ret = IRQ_HANDLED;
	}

	/* to ensure PCI write completion, we must perform a PCI read */
	smsc9420_pci_flush_write(pd);

	return ret;
}