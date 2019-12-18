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
struct znet_private {int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  sia_size; int /*<<< orphan*/  sia_base; int /*<<< orphan*/  io_size; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct znet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_dma (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct net_device*) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  znet_interrupt ; 

__attribute__((used)) static int znet_request_resources (struct net_device *dev)
{
	struct znet_private *znet = netdev_priv(dev);

	if (request_irq (dev->irq, &znet_interrupt, 0, "ZNet", dev))
		goto failed;
	if (request_dma (znet->rx_dma, "ZNet rx"))
		goto free_irq;
	if (request_dma (znet->tx_dma, "ZNet tx"))
		goto free_rx_dma;
	if (!request_region (znet->sia_base, znet->sia_size, "ZNet SIA"))
		goto free_tx_dma;
	if (!request_region (dev->base_addr, znet->io_size, "ZNet I/O"))
		goto free_sia;

	return 0;				/* Happy ! */

 free_sia:
	release_region (znet->sia_base, znet->sia_size);
 free_tx_dma:
	free_dma (znet->tx_dma);
 free_rx_dma:
	free_dma (znet->rx_dma);
 free_irq:
	free_irq (dev->irq, dev);
 failed:
	return -1;
}