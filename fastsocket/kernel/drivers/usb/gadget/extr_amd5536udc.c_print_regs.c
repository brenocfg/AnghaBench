#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udc {TYPE_2__* pdev; TYPE_1__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ep_irqmsk; int /*<<< orphan*/  ep_irqsts; int /*<<< orphan*/  irqmsk; int /*<<< orphan*/  irqsts; int /*<<< orphan*/  sts; int /*<<< orphan*/  ctl; int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct udc*,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 scalar_t__ use_dma ; 
 scalar_t__ use_dma_bufferfill_mode ; 
 scalar_t__ use_dma_ppb ; 
 scalar_t__ use_dma_ppb_du ; 

__attribute__((used)) static void print_regs(struct udc *dev)
{
	DBG(dev, "------- Device registers -------\n");
	DBG(dev, "dev config     = %08x\n", readl(&dev->regs->cfg));
	DBG(dev, "dev control    = %08x\n", readl(&dev->regs->ctl));
	DBG(dev, "dev status     = %08x\n", readl(&dev->regs->sts));
	DBG(dev, "\n");
	DBG(dev, "dev int's      = %08x\n", readl(&dev->regs->irqsts));
	DBG(dev, "dev intmask    = %08x\n", readl(&dev->regs->irqmsk));
	DBG(dev, "\n");
	DBG(dev, "dev ep int's   = %08x\n", readl(&dev->regs->ep_irqsts));
	DBG(dev, "dev ep intmask = %08x\n", readl(&dev->regs->ep_irqmsk));
	DBG(dev, "\n");
	DBG(dev, "USE DMA        = %d\n", use_dma);
	if (use_dma && use_dma_ppb && !use_dma_ppb_du) {
		DBG(dev, "DMA mode       = PPBNDU (packet per buffer "
			"WITHOUT desc. update)\n");
		dev_info(&dev->pdev->dev, "DMA mode (%s)\n", "PPBNDU");
	} else if (use_dma && use_dma_ppb_du && use_dma_ppb_du) {
		DBG(dev, "DMA mode       = PPBDU (packet per buffer "
			"WITH desc. update)\n");
		dev_info(&dev->pdev->dev, "DMA mode (%s)\n", "PPBDU");
	}
	if (use_dma && use_dma_bufferfill_mode) {
		DBG(dev, "DMA mode       = BF (buffer fill mode)\n");
		dev_info(&dev->pdev->dev, "DMA mode (%s)\n", "BF");
	}
	if (!use_dma) {
		dev_info(&dev->pdev->dev, "FIFO mode\n");
	}
	DBG(dev, "-------------------------------------------------------\n");
}