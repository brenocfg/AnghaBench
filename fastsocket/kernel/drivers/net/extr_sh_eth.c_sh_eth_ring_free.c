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
struct sh_eth_private {scalar_t__* tx_skbuff; scalar_t__* rx_skbuff; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void sh_eth_ring_free(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int i;

	/* Free Rx skb ringbuffer */
	if (mdp->rx_skbuff) {
		for (i = 0; i < RX_RING_SIZE; i++) {
			if (mdp->rx_skbuff[i])
				dev_kfree_skb(mdp->rx_skbuff[i]);
		}
	}
	kfree(mdp->rx_skbuff);

	/* Free Tx skb ringbuffer */
	if (mdp->tx_skbuff) {
		for (i = 0; i < TX_RING_SIZE; i++) {
			if (mdp->tx_skbuff[i])
				dev_kfree_skb(mdp->tx_skbuff[i]);
		}
	}
	kfree(mdp->tx_skbuff);
}