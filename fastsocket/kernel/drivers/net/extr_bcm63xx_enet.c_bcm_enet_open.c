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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct sk_buff {int dummy; } ;
struct phy_device {int supported; int advertising; TYPE_2__* drv; int /*<<< orphan*/  addr; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct bcm_enet_priv {int old_duplex; int old_pause; int rx_ring_size; int rx_desc_dma; unsigned int rx_desc_alloc_size; int tx_ring_size; int tx_desc_dma; unsigned int tx_desc_alloc_size; int tx_desc_count; struct phy_device* phydev; int /*<<< orphan*/  irq_rx; int /*<<< orphan*/  irq_tx; struct bcm_enet_desc* rx_desc_cpu; struct bcm_enet_desc* tx_desc_cpu; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  rx_skb_size; scalar_t__ has_phy; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  napi; int /*<<< orphan*/  hw_mtu; scalar_t__ rx_curr_desc; scalar_t__ rx_dirty_desc; scalar_t__ rx_desc_count; int /*<<< orphan*/  tx_lock; scalar_t__ tx_curr_desc; scalar_t__ tx_dirty_desc; scalar_t__ old_link; scalar_t__ pause_tx; scalar_t__ pause_rx; scalar_t__ pause_auto; int /*<<< orphan*/  phy_id; scalar_t__ mac_id; TYPE_1__* pdev; } ;
struct bcm_enet_desc {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  phy_id ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int BCMENET_DMA_MAXBURST ; 
 int /*<<< orphan*/  BCMENET_TX_FIFO_TRESH ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENETDMA_BUFALLOC_FORCE_MASK ; 
 int /*<<< orphan*/  ENETDMA_BUFALLOC_REG (int /*<<< orphan*/ ) ; 
 int ENETDMA_CFG_EN_MASK ; 
 int /*<<< orphan*/  ENETDMA_CFG_REG ; 
 int ENETDMA_CHANCFG_EN_MASK ; 
 int /*<<< orphan*/  ENETDMA_CHANCFG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_FLOWCH_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_FLOWCL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_IRMASK_REG (int /*<<< orphan*/ ) ; 
 int ENETDMA_IR_PKTDONE_MASK ; 
 int /*<<< orphan*/  ENETDMA_IR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_MAXBURST_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_RSTART_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_SRAM2_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_SRAM3_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_SRAM4_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENET_CTL_ENABLE_MASK ; 
 int /*<<< orphan*/  ENET_CTL_REG ; 
 int /*<<< orphan*/  ENET_IRMASK_REG ; 
 int /*<<< orphan*/  ENET_IR_MIB ; 
 int /*<<< orphan*/  ENET_IR_REG ; 
 int /*<<< orphan*/  ENET_PMH_REG (int) ; 
 int /*<<< orphan*/  ENET_PML_REG (int) ; 
 int /*<<< orphan*/  ENET_RXMAXLEN_REG ; 
 int /*<<< orphan*/  ENET_TXMAXLEN_REG ; 
 int /*<<< orphan*/  ENET_TXWMARK_REG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_DISABLED ; 
 int IRQF_SAMPLE_RANDOM ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* PHY_ID_FMT ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (struct phy_device*) ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  bcm_enet_adjust_link (struct net_device*) ; 
 int /*<<< orphan*/  bcm_enet_adjust_phy_link ; 
 int /*<<< orphan*/  bcm_enet_isr_dma ; 
 int /*<<< orphan*/  bcm_enet_isr_mac ; 
 scalar_t__ bcm_enet_refill_rx (struct net_device*) ; 
 int /*<<< orphan*/  bcm_enet_set_mac_address (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (struct device*,unsigned int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,unsigned int,struct bcm_enet_desc*,int) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dma_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_writel (struct bcm_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 struct phy_device* phy_connect (struct net_device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int bcm_enet_open(struct net_device *dev)
{
	struct bcm_enet_priv *priv;
	struct sockaddr addr;
	struct device *kdev;
	struct phy_device *phydev;
	int i, ret;
	unsigned int size;
	char phy_id[MII_BUS_ID_SIZE + 3];
	void *p;
	u32 val;

	priv = netdev_priv(dev);
	kdev = &priv->pdev->dev;

	if (priv->has_phy) {
		/* connect to PHY */
		snprintf(phy_id, sizeof(phy_id), PHY_ID_FMT,
			 priv->mac_id ? "1" : "0", priv->phy_id);

		phydev = phy_connect(dev, phy_id, &bcm_enet_adjust_phy_link, 0,
				     PHY_INTERFACE_MODE_MII);

		if (IS_ERR(phydev)) {
			dev_err(kdev, "could not attach to PHY\n");
			return PTR_ERR(phydev);
		}

		/* mask with MAC supported features */
		phydev->supported &= (SUPPORTED_10baseT_Half |
				      SUPPORTED_10baseT_Full |
				      SUPPORTED_100baseT_Half |
				      SUPPORTED_100baseT_Full |
				      SUPPORTED_Autoneg |
				      SUPPORTED_Pause |
				      SUPPORTED_MII);
		phydev->advertising = phydev->supported;

		if (priv->pause_auto && priv->pause_rx && priv->pause_tx)
			phydev->advertising |= SUPPORTED_Pause;
		else
			phydev->advertising &= ~SUPPORTED_Pause;

		dev_info(kdev, "attached PHY at address %d [%s]\n",
			 phydev->addr, phydev->drv->name);

		priv->old_link = 0;
		priv->old_duplex = -1;
		priv->old_pause = -1;
		priv->phydev = phydev;
	}

	/* mask all interrupts and request them */
	enet_writel(priv, 0, ENET_IRMASK_REG);
	enet_dma_writel(priv, 0, ENETDMA_IRMASK_REG(priv->rx_chan));
	enet_dma_writel(priv, 0, ENETDMA_IRMASK_REG(priv->tx_chan));

	ret = request_irq(dev->irq, bcm_enet_isr_mac, 0, dev->name, dev);
	if (ret)
		goto out_phy_disconnect;

	ret = request_irq(priv->irq_rx, bcm_enet_isr_dma,
			  IRQF_SAMPLE_RANDOM | IRQF_DISABLED, dev->name, dev);
	if (ret)
		goto out_freeirq;

	ret = request_irq(priv->irq_tx, bcm_enet_isr_dma,
			  IRQF_DISABLED, dev->name, dev);
	if (ret)
		goto out_freeirq_rx;

	/* initialize perfect match registers */
	for (i = 0; i < 4; i++) {
		enet_writel(priv, 0, ENET_PML_REG(i));
		enet_writel(priv, 0, ENET_PMH_REG(i));
	}

	/* write device mac address */
	memcpy(addr.sa_data, dev->dev_addr, ETH_ALEN);
	bcm_enet_set_mac_address(dev, &addr);

	/* allocate rx dma ring */
	size = priv->rx_ring_size * sizeof(struct bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->rx_desc_dma, GFP_KERNEL);
	if (!p) {
		dev_err(kdev, "cannot allocate rx ring %u\n", size);
		ret = -ENOMEM;
		goto out_freeirq_tx;
	}

	memset(p, 0, size);
	priv->rx_desc_alloc_size = size;
	priv->rx_desc_cpu = p;

	/* allocate tx dma ring */
	size = priv->tx_ring_size * sizeof(struct bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->tx_desc_dma, GFP_KERNEL);
	if (!p) {
		dev_err(kdev, "cannot allocate tx ring\n");
		ret = -ENOMEM;
		goto out_free_rx_ring;
	}

	memset(p, 0, size);
	priv->tx_desc_alloc_size = size;
	priv->tx_desc_cpu = p;

	priv->tx_skb = kzalloc(sizeof(struct sk_buff *) * priv->tx_ring_size,
			       GFP_KERNEL);
	if (!priv->tx_skb) {
		dev_err(kdev, "cannot allocate rx skb queue\n");
		ret = -ENOMEM;
		goto out_free_tx_ring;
	}

	priv->tx_desc_count = priv->tx_ring_size;
	priv->tx_dirty_desc = 0;
	priv->tx_curr_desc = 0;
	spin_lock_init(&priv->tx_lock);

	/* init & fill rx ring with skbs */
	priv->rx_skb = kzalloc(sizeof(struct sk_buff *) * priv->rx_ring_size,
			       GFP_KERNEL);
	if (!priv->rx_skb) {
		dev_err(kdev, "cannot allocate rx skb queue\n");
		ret = -ENOMEM;
		goto out_free_tx_skb;
	}

	priv->rx_desc_count = 0;
	priv->rx_dirty_desc = 0;
	priv->rx_curr_desc = 0;

	/* initialize flow control buffer allocation */
	enet_dma_writel(priv, ENETDMA_BUFALLOC_FORCE_MASK | 0,
			ENETDMA_BUFALLOC_REG(priv->rx_chan));

	if (bcm_enet_refill_rx(dev)) {
		dev_err(kdev, "cannot allocate rx skb queue\n");
		ret = -ENOMEM;
		goto out;
	}

	/* write rx & tx ring addresses */
	enet_dma_writel(priv, priv->rx_desc_dma,
			ENETDMA_RSTART_REG(priv->rx_chan));
	enet_dma_writel(priv, priv->tx_desc_dma,
			ENETDMA_RSTART_REG(priv->tx_chan));

	/* clear remaining state ram for rx & tx channel */
	enet_dma_writel(priv, 0, ENETDMA_SRAM2_REG(priv->rx_chan));
	enet_dma_writel(priv, 0, ENETDMA_SRAM2_REG(priv->tx_chan));
	enet_dma_writel(priv, 0, ENETDMA_SRAM3_REG(priv->rx_chan));
	enet_dma_writel(priv, 0, ENETDMA_SRAM3_REG(priv->tx_chan));
	enet_dma_writel(priv, 0, ENETDMA_SRAM4_REG(priv->rx_chan));
	enet_dma_writel(priv, 0, ENETDMA_SRAM4_REG(priv->tx_chan));

	/* set max rx/tx length */
	enet_writel(priv, priv->hw_mtu, ENET_RXMAXLEN_REG);
	enet_writel(priv, priv->hw_mtu, ENET_TXMAXLEN_REG);

	/* set dma maximum burst len */
	enet_dma_writel(priv, BCMENET_DMA_MAXBURST,
			ENETDMA_MAXBURST_REG(priv->rx_chan));
	enet_dma_writel(priv, BCMENET_DMA_MAXBURST,
			ENETDMA_MAXBURST_REG(priv->tx_chan));

	/* set correct transmit fifo watermark */
	enet_writel(priv, BCMENET_TX_FIFO_TRESH, ENET_TXWMARK_REG);

	/* set flow control low/high threshold to 1/3 / 2/3 */
	val = priv->rx_ring_size / 3;
	enet_dma_writel(priv, val, ENETDMA_FLOWCL_REG(priv->rx_chan));
	val = (priv->rx_ring_size * 2) / 3;
	enet_dma_writel(priv, val, ENETDMA_FLOWCH_REG(priv->rx_chan));

	/* all set, enable mac and interrupts, start dma engine and
	 * kick rx dma channel */
	wmb();
	enet_writel(priv, ENET_CTL_ENABLE_MASK, ENET_CTL_REG);
	enet_dma_writel(priv, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_REG);
	enet_dma_writel(priv, ENETDMA_CHANCFG_EN_MASK,
			ENETDMA_CHANCFG_REG(priv->rx_chan));

	/* watch "mib counters about to overflow" interrupt */
	enet_writel(priv, ENET_IR_MIB, ENET_IR_REG);
	enet_writel(priv, ENET_IR_MIB, ENET_IRMASK_REG);

	/* watch "packet transferred" interrupt in rx and tx */
	enet_dma_writel(priv, ENETDMA_IR_PKTDONE_MASK,
			ENETDMA_IR_REG(priv->rx_chan));
	enet_dma_writel(priv, ENETDMA_IR_PKTDONE_MASK,
			ENETDMA_IR_REG(priv->tx_chan));

	/* make sure we enable napi before rx interrupt  */
	napi_enable(&priv->napi);

	enet_dma_writel(priv, ENETDMA_IR_PKTDONE_MASK,
			ENETDMA_IRMASK_REG(priv->rx_chan));
	enet_dma_writel(priv, ENETDMA_IR_PKTDONE_MASK,
			ENETDMA_IRMASK_REG(priv->tx_chan));

	if (priv->has_phy)
		phy_start(priv->phydev);
	else
		bcm_enet_adjust_link(dev);

	netif_start_queue(dev);
	return 0;

out:
	for (i = 0; i < priv->rx_ring_size; i++) {
		struct bcm_enet_desc *desc;

		if (!priv->rx_skb[i])
			continue;

		desc = &priv->rx_desc_cpu[i];
		dma_unmap_single(kdev, desc->address, priv->rx_skb_size,
				 DMA_FROM_DEVICE);
		kfree_skb(priv->rx_skb[i]);
	}
	kfree(priv->rx_skb);

out_free_tx_skb:
	kfree(priv->tx_skb);

out_free_tx_ring:
	dma_free_coherent(kdev, priv->tx_desc_alloc_size,
			  priv->tx_desc_cpu, priv->tx_desc_dma);

out_free_rx_ring:
	dma_free_coherent(kdev, priv->rx_desc_alloc_size,
			  priv->rx_desc_cpu, priv->rx_desc_dma);

out_freeirq_tx:
	free_irq(priv->irq_tx, dev);

out_freeirq_rx:
	free_irq(priv->irq_rx, dev);

out_freeirq:
	free_irq(dev->irq, dev);

out_phy_disconnect:
	phy_disconnect(priv->phydev);

	return ret;
}