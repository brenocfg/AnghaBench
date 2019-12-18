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
struct temac_local {int /*<<< orphan*/  ndev; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int IRQ_COAL ; 
 unsigned int IRQ_DLY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TX_IRQ_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 unsigned int temac_dma_in32 (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_dma_out32 (struct temac_local*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  temac_start_xmit_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ll_temac_tx_irq(int irq, void *_ndev)
{
	struct net_device *ndev = _ndev;
	struct temac_local *lp = netdev_priv(ndev);
	unsigned int status;

	status = temac_dma_in32(lp, TX_IRQ_REG);
	temac_dma_out32(lp, TX_IRQ_REG, status);

	if (status & (IRQ_COAL | IRQ_DLY))
		temac_start_xmit_done(lp->ndev);
	if (status & 0x080)
		dev_err(&ndev->dev, "DMA error 0x%x\n", status);

	return IRQ_HANDLED;
}