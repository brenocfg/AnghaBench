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
struct sk_buff {int dummy; } ;
struct sbmac_softc {int /*<<< orphan*/  sbm_lock; int /*<<< orphan*/  sbm_txdma; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  jiffies ; 
 struct sbmac_softc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ sbdma_add_txbuffer (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sbmac_start_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct sbmac_softc *sc = netdev_priv(dev);
	unsigned long flags;

	/* lock eth irq */
	spin_lock_irqsave(&sc->sbm_lock, flags);

	/*
	 * Put the buffer on the transmit ring.  If we
	 * don't have room, stop the queue.
	 */

	if (sbdma_add_txbuffer(&(sc->sbm_txdma),skb)) {
		/* XXX save skb that we could not send */
		netif_stop_queue(dev);
		spin_unlock_irqrestore(&sc->sbm_lock, flags);

		return NETDEV_TX_BUSY;
	}

	dev->trans_start = jiffies;

	spin_unlock_irqrestore(&sc->sbm_lock, flags);

	return NETDEV_TX_OK;
}