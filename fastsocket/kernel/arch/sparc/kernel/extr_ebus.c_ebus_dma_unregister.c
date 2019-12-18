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
typedef  int u32 ;
struct ebus_dma_info {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ EBDMA_CSR ; 
 int EBDMA_CSR_INT_EN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ebus_dma_info*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ebus_dma_unregister(struct ebus_dma_info *p)
{
	unsigned long flags;
	u32 csr;
	int irq_on = 0;

	spin_lock_irqsave(&p->lock, flags);
	csr = readl(p->regs + EBDMA_CSR);
	if (csr & EBDMA_CSR_INT_EN) {
		csr &= ~EBDMA_CSR_INT_EN;
		writel(csr, p->regs + EBDMA_CSR);
		irq_on = 1;
	}
	spin_unlock_irqrestore(&p->lock, flags);

	if (irq_on)
		free_irq(p->irq, p);
}