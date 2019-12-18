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
struct w90p910_ether {int /*<<< orphan*/  rxirq; int /*<<< orphan*/  txirq; int /*<<< orphan*/  clk; int /*<<< orphan*/  rmiiclk; int /*<<< orphan*/  check_timer; int /*<<< orphan*/  tdesc_phys; int /*<<< orphan*/  tdesc; int /*<<< orphan*/  rdesc_phys; int /*<<< orphan*/  rdesc; struct platform_device* pdev; } ;
struct tran_pdesc {int dummy; } ;
struct recv_pdesc {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int w90p910_ether_close(struct net_device *dev)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	struct platform_device *pdev;

	pdev = ether->pdev;

	dma_free_coherent(&pdev->dev, sizeof(struct recv_pdesc),
					ether->rdesc, ether->rdesc_phys);
	dma_free_coherent(&pdev->dev, sizeof(struct tran_pdesc),
					ether->tdesc, ether->tdesc_phys);

	netif_stop_queue(dev);

	del_timer_sync(&ether->check_timer);
	clk_disable(ether->rmiiclk);
	clk_disable(ether->clk);

	free_irq(ether->txirq, dev);
	free_irq(ether->rxirq, dev);

	return 0;
}