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
struct temac_local {int rx_bd_ci; int /*<<< orphan*/  rx_lock; struct cdmac_bd* rx_bd_v; struct sk_buff** rx_skb; scalar_t__ rx_bd_p; } ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ dev; TYPE_1__ stats; } ;
struct cdmac_bd {unsigned int app0; int app4; scalar_t__ len; int /*<<< orphan*/  phys; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t RX_BD_NUM ; 
 int /*<<< orphan*/  RX_TAILDESC_PTR ; 
 unsigned int STS_CTRL_APP0_CMPLT ; 
 unsigned int STS_CTRL_APP0_IRQONEND ; 
 scalar_t__ XTE_ALIGN ; 
 scalar_t__ XTE_MAX_JUMBO_FRAME_SIZE ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  temac_dma_out32 (struct temac_local*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ll_temac_recv(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct sk_buff *skb, *new_skb;
	unsigned int bdstat;
	struct cdmac_bd *cur_p;
	dma_addr_t tail_p;
	int length;
	unsigned long skb_vaddr;
	unsigned long flags;

	spin_lock_irqsave(&lp->rx_lock, flags);

	tail_p = lp->rx_bd_p + sizeof(*lp->rx_bd_v) * lp->rx_bd_ci;
	cur_p = &lp->rx_bd_v[lp->rx_bd_ci];

	bdstat = cur_p->app0;
	while ((bdstat & STS_CTRL_APP0_CMPLT)) {

		skb = lp->rx_skb[lp->rx_bd_ci];
		length = cur_p->app4;

		skb_vaddr = virt_to_bus(skb->data);
		dma_unmap_single(ndev->dev.parent, skb_vaddr, length,
				 DMA_FROM_DEVICE);

		skb_put(skb, length);
		skb->dev = ndev;
		skb->protocol = eth_type_trans(skb, ndev);
		skb->ip_summed = CHECKSUM_NONE;

		netif_rx(skb);

		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += length;

		new_skb = alloc_skb(XTE_MAX_JUMBO_FRAME_SIZE + XTE_ALIGN,
				GFP_ATOMIC);
		if (new_skb == 0) {
			dev_err(&ndev->dev, "no memory for new sk_buff\n");
			spin_unlock_irqrestore(&lp->rx_lock, flags);
			return;
		}

		skb_reserve(new_skb, BUFFER_ALIGN(new_skb->data));

		cur_p->app0 = STS_CTRL_APP0_IRQONEND;
		cur_p->phys = dma_map_single(ndev->dev.parent, new_skb->data,
					     XTE_MAX_JUMBO_FRAME_SIZE,
					     DMA_FROM_DEVICE);
		cur_p->len = XTE_MAX_JUMBO_FRAME_SIZE;
		lp->rx_skb[lp->rx_bd_ci] = new_skb;

		lp->rx_bd_ci++;
		if (lp->rx_bd_ci >= RX_BD_NUM)
			lp->rx_bd_ci = 0;

		cur_p = &lp->rx_bd_v[lp->rx_bd_ci];
		bdstat = cur_p->app0;
	}
	temac_dma_out32(lp, RX_TAILDESC_PTR, tail_p);

	spin_unlock_irqrestore(&lp->rx_lock, flags);
}