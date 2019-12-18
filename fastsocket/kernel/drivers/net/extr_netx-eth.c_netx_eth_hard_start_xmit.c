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
struct sk_buff {unsigned char* data; unsigned int len; } ;
struct netx_eth_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  id; scalar_t__ sram_base; } ;
struct TYPE_2__ {unsigned int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int FIFO_PTR_FRAMELEN (unsigned int) ; 
 int FIFO_PTR_FRAMENO (int) ; 
 int FIFO_PTR_SEGMENT (int /*<<< orphan*/ ) ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  REQ_FIFO_PORT_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void*,unsigned int) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct netx_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pfifo_push (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
netx_eth_hard_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct netx_eth_priv *priv = netdev_priv(ndev);
	unsigned char *buf = skb->data;
	unsigned int len = skb->len;

	spin_lock_irq(&priv->lock);
	memcpy_toio(priv->sram_base + 1560, (void *)buf, len);
	if (len < 60) {
		memset_io(priv->sram_base + 1560 + len, 0, 60 - len);
		len = 60;
	}

	pfifo_push(REQ_FIFO_PORT_LO(priv->id),
	           FIFO_PTR_SEGMENT(priv->id) |
	           FIFO_PTR_FRAMENO(1) |
	           FIFO_PTR_FRAMELEN(len));

	ndev->trans_start = jiffies;
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += skb->len;

	netif_stop_queue(ndev);
	spin_unlock_irq(&priv->lock);
	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}