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
struct sonic_local {int /*<<< orphan*/ ** rx_skb; void** rx_laddr; int /*<<< orphan*/  device; int /*<<< orphan*/ ** tx_skb; void** tx_laddr; int /*<<< orphan*/ * tx_len; } ;
struct net_device {int dummy; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SONIC_CMD ; 
 int SONIC_CR_RST ; 
 int /*<<< orphan*/  SONIC_IMR ; 
 int /*<<< orphan*/  SONIC_ISR ; 
 int SONIC_NUM_RRS ; 
 int SONIC_NUM_TDS ; 
 int /*<<< orphan*/  SONIC_RBSIZE ; 
 int /*<<< orphan*/  SONIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int sonic_debug ; 

__attribute__((used)) static int sonic_close(struct net_device *dev)
{
	struct sonic_local *lp = netdev_priv(dev);
	int i;

	if (sonic_debug > 2)
		printk("sonic_close\n");

	netif_stop_queue(dev);

	/*
	 * stop the SONIC, disable interrupts
	 */
	SONIC_WRITE(SONIC_IMR, 0);
	SONIC_WRITE(SONIC_ISR, 0x7fff);
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);

	/* unmap and free skbs that haven't been transmitted */
	for (i = 0; i < SONIC_NUM_TDS; i++) {
		if(lp->tx_laddr[i]) {
			dma_unmap_single(lp->device, lp->tx_laddr[i], lp->tx_len[i], DMA_TO_DEVICE);
			lp->tx_laddr[i] = (dma_addr_t)0;
		}
		if(lp->tx_skb[i]) {
			dev_kfree_skb(lp->tx_skb[i]);
			lp->tx_skb[i] = NULL;
		}
	}

	/* unmap and free the receive buffers */
	for (i = 0; i < SONIC_NUM_RRS; i++) {
		if(lp->rx_laddr[i]) {
			dma_unmap_single(lp->device, lp->rx_laddr[i], SONIC_RBSIZE, DMA_FROM_DEVICE);
			lp->rx_laddr[i] = (dma_addr_t)0;
		}
		if(lp->rx_skb[i]) {
			dev_kfree_skb(lp->rx_skb[i]);
			lp->rx_skb[i] = NULL;
		}
	}

	return 0;
}