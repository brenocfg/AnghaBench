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
struct sk_buff {int /*<<< orphan*/  data; struct net_device* dev; } ;
struct net_device {scalar_t__ mtu; } ;
struct gem_txd {scalar_t__ buffer; scalar_t__ control_word; } ;
struct gem_rxd {void* status_word; void* buffer; } ;
struct gem_init_block {struct gem_txd* txd; struct gem_rxd* rxd; } ;
struct gem {int /*<<< orphan*/  pdev; scalar_t__ rx_buf_sz; struct sk_buff** rx_skbs; scalar_t__ tx_old; scalar_t__ tx_new; scalar_t__ rx_old; scalar_t__ rx_new; struct net_device* dev; struct gem_init_block* init_block; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RXDCTRL_FRESH (struct gem*) ; 
 int /*<<< orphan*/  RX_BUF_ALLOC_SIZE (struct gem*) ; 
 scalar_t__ RX_OFFSET ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 scalar_t__ VLAN_ETH_FRAME_LEN ; 
 scalar_t__ VLAN_HLEN ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct sk_buff* gem_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_clean_rings (struct gem*) ; 
 scalar_t__ max (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void gem_init_rings(struct gem *gp)
{
	struct gem_init_block *gb = gp->init_block;
	struct net_device *dev = gp->dev;
	int i;
	dma_addr_t dma_addr;

	gp->rx_new = gp->rx_old = gp->tx_new = gp->tx_old = 0;

	gem_clean_rings(gp);

	gp->rx_buf_sz = max(dev->mtu + ETH_HLEN + VLAN_HLEN,
			    (unsigned)VLAN_ETH_FRAME_LEN);

	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb;
		struct gem_rxd *rxd = &gb->rxd[i];

		skb = gem_alloc_skb(RX_BUF_ALLOC_SIZE(gp), GFP_ATOMIC);
		if (!skb) {
			rxd->buffer = 0;
			rxd->status_word = 0;
			continue;
		}

		gp->rx_skbs[i] = skb;
		skb->dev = dev;
		skb_put(skb, (gp->rx_buf_sz + RX_OFFSET));
		dma_addr = pci_map_page(gp->pdev,
					virt_to_page(skb->data),
					offset_in_page(skb->data),
					RX_BUF_ALLOC_SIZE(gp),
					PCI_DMA_FROMDEVICE);
		rxd->buffer = cpu_to_le64(dma_addr);
		wmb();
		rxd->status_word = cpu_to_le64(RXDCTRL_FRESH(gp));
		skb_reserve(skb, RX_OFFSET);
	}

	for (i = 0; i < TX_RING_SIZE; i++) {
		struct gem_txd *txd = &gb->txd[i];

		txd->control_word = 0;
		wmb();
		txd->buffer = 0;
	}
	wmb();
}