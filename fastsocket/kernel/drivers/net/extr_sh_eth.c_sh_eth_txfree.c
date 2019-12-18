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
struct sh_eth_txdesc {int status; scalar_t__ buffer_length; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct sh_eth_private {scalar_t__ cur_tx; int dirty_tx; TYPE_1__ stats; int /*<<< orphan*/ ** tx_skbuff; struct sh_eth_txdesc* tx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TD_TACT ; 
 int /*<<< orphan*/  TD_TDLE ; 
 int /*<<< orphan*/  TD_TFP ; 
 int TX_RING_SIZE ; 
 int cpu_to_edmac (struct sh_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int sh_eth_txfree(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_txdesc *txdesc;
	int freeNum = 0;
	int entry = 0;

	for (; mdp->cur_tx - mdp->dirty_tx > 0; mdp->dirty_tx++) {
		entry = mdp->dirty_tx % TX_RING_SIZE;
		txdesc = &mdp->tx_ring[entry];
		if (txdesc->status & cpu_to_edmac(mdp, TD_TACT))
			break;
		/* Free the original skb. */
		if (mdp->tx_skbuff[entry]) {
			dev_kfree_skb_irq(mdp->tx_skbuff[entry]);
			mdp->tx_skbuff[entry] = NULL;
			freeNum++;
		}
		txdesc->status = cpu_to_edmac(mdp, TD_TFP);
		if (entry >= TX_RING_SIZE - 1)
			txdesc->status |= cpu_to_edmac(mdp, TD_TDLE);

		mdp->stats.tx_packets++;
		mdp->stats.tx_bytes += txdesc->buffer_length;
	}
	return freeNum;
}