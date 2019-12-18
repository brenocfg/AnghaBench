#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int* data; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int tx_bytes; } ;
struct TYPE_5__ {int tx_irq_disabled; scalar_t__ tx_free_frames; TYPE_1__ linux_stats; } ;
typedef  TYPE_2__ mace_private ;

/* Variables and functions */
 scalar_t__ AM2150_MACE_BASE ; 
 scalar_t__ AM2150_XMT ; 
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ MACE_IMR ; 
 int MACE_IMR_DEFAULT ; 
 int MACE_IR_XMTINT ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outsw (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t mace_start_xmit(struct sk_buff *skb,
					 struct net_device *dev)
{
  mace_private *lp = netdev_priv(dev);
  unsigned int ioaddr = dev->base_addr;

  netif_stop_queue(dev);

  DEBUG(3, "%s: mace_start_xmit(length = %ld) called.\n",
	dev->name, (long)skb->len);

#if (!TX_INTERRUPTABLE)
  /* Disable MACE TX interrupts. */
  outb(MACE_IMR_DEFAULT | MACE_IR_XMTINT,
    ioaddr + AM2150_MACE_BASE + MACE_IMR);
  lp->tx_irq_disabled=1;
#endif /* #if (!TX_INTERRUPTABLE) */

  {
    /* This block must not be interrupted by another transmit request!
       mace_tx_timeout will take care of timer-based retransmissions from
       the upper layers.  The interrupt handler is guaranteed never to
       service a transmit interrupt while we are in here.
    */

    lp->linux_stats.tx_bytes += skb->len;
    lp->tx_free_frames--;

    /* WARNING: Write the _exact_ number of bytes written in the header! */
    /* Put out the word header [must be an outw()] . . . */
    outw(skb->len, ioaddr + AM2150_XMT);
    /* . . . and the packet [may be any combination of outw() and outb()] */
    outsw(ioaddr + AM2150_XMT, skb->data, skb->len >> 1);
    if (skb->len & 1) {
      /* Odd byte transfer */
      outb(skb->data[skb->len-1], ioaddr + AM2150_XMT);
    }

    dev->trans_start = jiffies;

#if MULTI_TX
    if (lp->tx_free_frames > 0)
      netif_start_queue(dev);
#endif /* #if MULTI_TX */
  }

#if (!TX_INTERRUPTABLE)
  /* Re-enable MACE TX interrupts. */
  lp->tx_irq_disabled=0;
  outb(MACE_IMR_DEFAULT, ioaddr + AM2150_MACE_BASE + MACE_IMR);
#endif /* #if (!TX_INTERRUPTABLE) */

  dev_kfree_skb(skb);

  return NETDEV_TX_OK;
}