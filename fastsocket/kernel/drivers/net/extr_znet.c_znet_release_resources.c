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
struct znet_private {int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  io_size; int /*<<< orphan*/  sia_size; int /*<<< orphan*/  sia_base; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct znet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void znet_release_resources (struct net_device *dev)
{
	struct znet_private *znet = netdev_priv(dev);

	release_region (znet->sia_base, znet->sia_size);
	release_region (dev->base_addr, znet->io_size);
	free_dma (znet->tx_dma);
	free_dma (znet->rx_dma);
	free_irq (dev->irq, dev);
}