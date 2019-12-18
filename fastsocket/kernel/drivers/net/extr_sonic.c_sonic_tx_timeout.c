#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct sonic_local {TYPE_1__ stats; int /*<<< orphan*/ ** tx_skb; scalar_t__* tx_laddr; int /*<<< orphan*/ * tx_len; int /*<<< orphan*/  device; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SONIC_CMD ; 
 int SONIC_CR_RST ; 
 int /*<<< orphan*/  SONIC_IMR ; 
 int /*<<< orphan*/  SONIC_ISR ; 
 int SONIC_NUM_TDS ; 
 int /*<<< orphan*/  SONIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  sonic_init (struct net_device*) ; 

__attribute__((used)) static void sonic_tx_timeout(struct net_device *dev)
{
	struct sonic_local *lp = netdev_priv(dev);
	int i;
	/*
	 * put the Sonic into software-reset mode and
	 * disable all interrupts before releasing DMA buffers
	 */
	SONIC_WRITE(SONIC_IMR, 0);
	SONIC_WRITE(SONIC_ISR, 0x7fff);
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);
	/* We could resend the original skbs. Easier to re-initialise. */
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
	/* Try to restart the adaptor. */
	sonic_init(dev);
	lp->stats.tx_errors++;
	dev->trans_start = jiffies;
	netif_wake_queue(dev);
}