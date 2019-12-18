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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct korina_private {int /*<<< orphan*/  und_irq; int /*<<< orphan*/  ovr_irq; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  napi; TYPE_2__* rx_dma_regs; TYPE_1__* tx_dma_regs; int /*<<< orphan*/  media_check_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmasm; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmasm; } ;

/* Variables and functions */
 int DMA_STAT_DONE ; 
 int DMA_STAT_ERR ; 
 int DMA_STAT_FINI ; 
 int DMA_STAT_HALT ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  korina_abort_rx (struct net_device*) ; 
 int /*<<< orphan*/  korina_abort_tx (struct net_device*) ; 
 int /*<<< orphan*/  korina_free_ring (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int korina_close(struct net_device *dev)
{
	struct korina_private *lp = netdev_priv(dev);
	u32 tmp;

	del_timer(&lp->media_check_timer);

	/* Disable interrupts */
	disable_irq(lp->rx_irq);
	disable_irq(lp->tx_irq);
	disable_irq(lp->ovr_irq);
	disable_irq(lp->und_irq);

	korina_abort_tx(dev);
	tmp = readl(&lp->tx_dma_regs->dmasm);
	tmp = tmp | DMA_STAT_FINI | DMA_STAT_ERR;
	writel(tmp, &lp->tx_dma_regs->dmasm);

	korina_abort_rx(dev);
	tmp = readl(&lp->rx_dma_regs->dmasm);
	tmp = tmp | DMA_STAT_DONE | DMA_STAT_HALT | DMA_STAT_ERR;
	writel(tmp, &lp->rx_dma_regs->dmasm);

	korina_free_ring(dev);

	napi_disable(&lp->napi);

	free_irq(lp->rx_irq, dev);
	free_irq(lp->tx_irq, dev);
	free_irq(lp->ovr_irq, dev);
	free_irq(lp->und_irq, dev);

	return 0;
}