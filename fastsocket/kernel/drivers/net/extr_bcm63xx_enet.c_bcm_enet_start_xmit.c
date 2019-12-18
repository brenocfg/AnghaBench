#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct TYPE_4__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct bcm_enet_priv {size_t tx_curr_desc; size_t tx_ring_size; int /*<<< orphan*/  tx_lock; TYPE_2__ stats; int /*<<< orphan*/  tx_desc_count; int /*<<< orphan*/  tx_chan; TYPE_1__* pdev; struct sk_buff** tx_skb; struct bcm_enet_desc* tx_desc_cpu; } ;
struct bcm_enet_desc {int len_stat; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMADESC_APPEND_CRC ; 
 int DMADESC_ESOP_MASK ; 
 int DMADESC_LENGTH_MASK ; 
 int DMADESC_LENGTH_SHIFT ; 
 int DMADESC_OWNER_MASK ; 
 int DMADESC_WRAP_MASK ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ENETDMA_CHANCFG_EN_MASK ; 
 int /*<<< orphan*/  ENETDMA_CHANCFG_REG (int /*<<< orphan*/ ) ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dma_writel (struct bcm_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int bcm_enet_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct bcm_enet_priv *priv;
	struct bcm_enet_desc *desc;
	u32 len_stat;
	int ret;

	priv = netdev_priv(dev);

	/* lock against tx reclaim */
	spin_lock(&priv->tx_lock);

	/* make sure  the tx hw queue  is not full,  should not happen
	 * since we stop queue before it's the case */
	if (unlikely(!priv->tx_desc_count)) {
		netif_stop_queue(dev);
		dev_err(&priv->pdev->dev, "xmit called with no tx desc "
			"available?\n");
		ret = NETDEV_TX_BUSY;
		goto out_unlock;
	}

	/* point to the next available desc */
	desc = &priv->tx_desc_cpu[priv->tx_curr_desc];
	priv->tx_skb[priv->tx_curr_desc] = skb;

	/* fill descriptor */
	desc->address = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
				       DMA_TO_DEVICE);

	len_stat = (skb->len << DMADESC_LENGTH_SHIFT) & DMADESC_LENGTH_MASK;
	len_stat |= DMADESC_ESOP_MASK |
		DMADESC_APPEND_CRC |
		DMADESC_OWNER_MASK;

	priv->tx_curr_desc++;
	if (priv->tx_curr_desc == priv->tx_ring_size) {
		priv->tx_curr_desc = 0;
		len_stat |= DMADESC_WRAP_MASK;
	}
	priv->tx_desc_count--;

	/* dma might be already polling, make sure we update desc
	 * fields in correct order */
	wmb();
	desc->len_stat = len_stat;
	wmb();

	/* kick tx dma */
	enet_dma_writel(priv, ENETDMA_CHANCFG_EN_MASK,
			ENETDMA_CHANCFG_REG(priv->tx_chan));

	/* stop queue if no more desc available */
	if (!priv->tx_desc_count)
		netif_stop_queue(dev);

	priv->stats.tx_bytes += skb->len;
	priv->stats.tx_packets++;
	dev->trans_start = jiffies;
	ret = NETDEV_TX_OK;

out_unlock:
	spin_unlock(&priv->tx_lock);
	return ret;
}