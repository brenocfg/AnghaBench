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
struct temac_local {int tx_bd_p; int rx_bd_p; TYPE_1__* rx_bd_v; struct sk_buff** rx_skb; TYPE_1__* tx_bd_v; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int next; int /*<<< orphan*/  app0; scalar_t__ len; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_ALIGN (int /*<<< orphan*/ ) ; 
 int CHNL_CTRL_IRQ_COAL_EN ; 
 int CHNL_CTRL_IRQ_DLY_EN ; 
 int CHNL_CTRL_IRQ_EN ; 
 int CHNL_CTRL_IRQ_IOE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_BD_NUM ; 
 int /*<<< orphan*/  RX_CHNL_CTRL ; 
 int /*<<< orphan*/  RX_CURDESC_PTR ; 
 int /*<<< orphan*/  RX_TAILDESC_PTR ; 
 int /*<<< orphan*/  STS_CTRL_APP0_IRQONEND ; 
 int TX_BD_NUM ; 
 int /*<<< orphan*/  TX_CHNL_CTRL ; 
 int /*<<< orphan*/  TX_CURDESC_PTR ; 
 scalar_t__ XTE_ALIGN ; 
 scalar_t__ XTE_MAX_JUMBO_FRAME_SIZE ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sk_buff** kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_dma_out32 (struct temac_local*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int temac_dma_bd_init(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct sk_buff *skb;
	int i;

	lp->rx_skb = kzalloc(sizeof(struct sk_buff)*RX_BD_NUM, GFP_KERNEL);
	/* allocate the tx and rx ring buffer descriptors. */
	/* returns a virtual addres and a physical address. */
	lp->tx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 sizeof(*lp->tx_bd_v) * TX_BD_NUM,
					 &lp->tx_bd_p, GFP_KERNEL);
	lp->rx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 sizeof(*lp->rx_bd_v) * RX_BD_NUM,
					 &lp->rx_bd_p, GFP_KERNEL);

	memset(lp->tx_bd_v, 0, sizeof(*lp->tx_bd_v) * TX_BD_NUM);
	for (i = 0; i < TX_BD_NUM; i++) {
		lp->tx_bd_v[i].next = lp->tx_bd_p +
				sizeof(*lp->tx_bd_v) * ((i + 1) % TX_BD_NUM);
	}

	memset(lp->rx_bd_v, 0, sizeof(*lp->rx_bd_v) * RX_BD_NUM);
	for (i = 0; i < RX_BD_NUM; i++) {
		lp->rx_bd_v[i].next = lp->rx_bd_p +
				sizeof(*lp->rx_bd_v) * ((i + 1) % RX_BD_NUM);

		skb = alloc_skb(XTE_MAX_JUMBO_FRAME_SIZE
				+ XTE_ALIGN, GFP_ATOMIC);
		if (skb == 0) {
			dev_err(&ndev->dev, "alloc_skb error %d\n", i);
			return -1;
		}
		lp->rx_skb[i] = skb;
		skb_reserve(skb,  BUFFER_ALIGN(skb->data));
		/* returns physical address of skb->data */
		lp->rx_bd_v[i].phys = dma_map_single(ndev->dev.parent,
						     skb->data,
						     XTE_MAX_JUMBO_FRAME_SIZE,
						     DMA_FROM_DEVICE);
		lp->rx_bd_v[i].len = XTE_MAX_JUMBO_FRAME_SIZE;
		lp->rx_bd_v[i].app0 = STS_CTRL_APP0_IRQONEND;
	}

	temac_dma_out32(lp, TX_CHNL_CTRL, 0x10220400 |
					  CHNL_CTRL_IRQ_EN |
					  CHNL_CTRL_IRQ_DLY_EN |
					  CHNL_CTRL_IRQ_COAL_EN);
	/* 0x10220483 */
	/* 0x00100483 */
	temac_dma_out32(lp, RX_CHNL_CTRL, 0xff010000 |
					  CHNL_CTRL_IRQ_EN |
					  CHNL_CTRL_IRQ_DLY_EN |
					  CHNL_CTRL_IRQ_COAL_EN |
					  CHNL_CTRL_IRQ_IOE);
	/* 0xff010283 */

	temac_dma_out32(lp, RX_CURDESC_PTR,  lp->rx_bd_p);
	temac_dma_out32(lp, RX_TAILDESC_PTR,
		       lp->rx_bd_p + (sizeof(*lp->rx_bd_v) * (RX_BD_NUM - 1)));
	temac_dma_out32(lp, TX_CURDESC_PTR, lp->tx_bd_p);

	return 0;
}