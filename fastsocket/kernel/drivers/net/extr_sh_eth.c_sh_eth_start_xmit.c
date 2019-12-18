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
typedef  size_t u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct sh_eth_txdesc {scalar_t__ buffer_length; int /*<<< orphan*/  status; int /*<<< orphan*/  addr; } ;
struct sh_eth_private {int cur_tx; int dirty_tx; TYPE_1__* cd; struct sh_eth_txdesc* tx_ring; struct sk_buff** tx_skbuff; int /*<<< orphan*/  lock; } ;
struct net_device {int /*<<< orphan*/  trans_start; scalar_t__ base_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_swap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ EDTRR ; 
 int EDTRR_TRNS ; 
 scalar_t__ ETHERSMALL ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int TD_TACT ; 
 int TD_TDLE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  __flush_purge_region (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_edmac (struct sh_eth_private*,int) ; 
 int ctrl_inl (scalar_t__) ; 
 int /*<<< orphan*/  ctrl_outl (int,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_soft_swap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sh_eth_txfree (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_eth_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_txdesc *txdesc;
	u32 entry;
	unsigned long flags;

	spin_lock_irqsave(&mdp->lock, flags);
	if ((mdp->cur_tx - mdp->dirty_tx) >= (TX_RING_SIZE - 4)) {
		if (!sh_eth_txfree(ndev)) {
			netif_stop_queue(ndev);
			spin_unlock_irqrestore(&mdp->lock, flags);
			return NETDEV_TX_BUSY;
		}
	}
	spin_unlock_irqrestore(&mdp->lock, flags);

	entry = mdp->cur_tx % TX_RING_SIZE;
	mdp->tx_skbuff[entry] = skb;
	txdesc = &mdp->tx_ring[entry];
	txdesc->addr = virt_to_phys(skb->data);
	/* soft swap. */
	if (!mdp->cd->hw_swap)
		sh_eth_soft_swap(phys_to_virt(ALIGN(txdesc->addr, 4)),
				 skb->len + 2);
	/* write back */
	__flush_purge_region(skb->data, skb->len);
	if (skb->len < ETHERSMALL)
		txdesc->buffer_length = ETHERSMALL;
	else
		txdesc->buffer_length = skb->len;

	if (entry >= TX_RING_SIZE - 1)
		txdesc->status |= cpu_to_edmac(mdp, TD_TACT | TD_TDLE);
	else
		txdesc->status |= cpu_to_edmac(mdp, TD_TACT);

	mdp->cur_tx++;

	if (!(ctrl_inl(ndev->base_addr + EDTRR) & EDTRR_TRNS))
		ctrl_outl(EDTRR_TRNS, ndev->base_addr + EDTRR);

	ndev->trans_start = jiffies;

	return NETDEV_TX_OK;
}