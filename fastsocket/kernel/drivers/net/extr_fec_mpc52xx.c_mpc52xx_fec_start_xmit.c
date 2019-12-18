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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; int /*<<< orphan*/  trans_start; } ;
struct mpc52xx_fec_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_dmatsk; } ;
struct bcom_fec_bd {int status; int /*<<< orphan*/  skb_pa; } ;

/* Variables and functions */
 int BCOM_FEC_TX_BD_TC ; 
 int BCOM_FEC_TX_BD_TFD ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ bcom_prepare_next_buffer (int /*<<< orphan*/ ) ; 
 scalar_t__ bcom_queue_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_submit_next_buffer (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ net_ratelimit () ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mpc52xx_fec_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct mpc52xx_fec_priv *priv = netdev_priv(dev);
	struct bcom_fec_bd *bd;
	unsigned long flags;

	if (bcom_queue_full(priv->tx_dmatsk)) {
		if (net_ratelimit())
			dev_err(&dev->dev, "transmit queue overrun\n");
		return NETDEV_TX_BUSY;
	}

	spin_lock_irqsave(&priv->lock, flags);
	dev->trans_start = jiffies;

	bd = (struct bcom_fec_bd *)
		bcom_prepare_next_buffer(priv->tx_dmatsk);

	bd->status = skb->len | BCOM_FEC_TX_BD_TFD | BCOM_FEC_TX_BD_TC;
	bd->skb_pa = dma_map_single(dev->dev.parent, skb->data, skb->len,
				    DMA_TO_DEVICE);

	bcom_submit_next_buffer(priv->tx_dmatsk, skb);

	if (bcom_queue_full(priv->tx_dmatsk)) {
		netif_stop_queue(dev);
	}

	spin_unlock_irqrestore(&priv->lock, flags);

	return NETDEV_TX_OK;
}