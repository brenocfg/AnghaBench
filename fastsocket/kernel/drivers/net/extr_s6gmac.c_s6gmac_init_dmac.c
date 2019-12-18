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
struct s6gmac {int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  tx_chan; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int S6_HIFDMA_GMACRX ; 
 int S6_HIFDMA_GMACTX ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  s6dmac_disable_chan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6dmac_disable_error_irqs (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void s6gmac_init_dmac(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	s6dmac_disable_chan(pd->tx_dma, pd->tx_chan);
	s6dmac_disable_chan(pd->rx_dma, pd->rx_chan);
	s6dmac_disable_error_irqs(pd->tx_dma, 1 << S6_HIFDMA_GMACTX);
	s6dmac_disable_error_irqs(pd->rx_dma, 1 << S6_HIFDMA_GMACRX);
}