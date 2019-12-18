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
typedef  scalar_t__ u32 ;
struct typhoon {int /*<<< orphan*/  state_lock; int /*<<< orphan*/ * vlgrp; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; struct rxbuff_ent* rxbuffers; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct rxbuff_ent {int /*<<< orphan*/  dma_addr; struct sk_buff* skb; } ;
struct rx_desc {scalar_t__ addr; int flags; int rxStatus; int /*<<< orphan*/  vlanTag; int /*<<< orphan*/  frameLen; } ;
struct basic_ring {scalar_t__ ringBase; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 int TYPHOON_RX_ERROR ; 
 int TYPHOON_RX_IP_CHK_GOOD ; 
 int TYPHOON_RX_TCP_CHK_GOOD ; 
 int TYPHOON_RX_UDP_CHK_GOOD ; 
 int TYPHOON_RX_VLAN ; 
 int cpu_to_le32 (scalar_t__) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int volatile) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rx_copybreak ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typhoon_alloc_rx_skb (struct typhoon*,scalar_t__) ; 
 int /*<<< orphan*/  typhoon_inc_rx_index (scalar_t__*,int) ; 
 int /*<<< orphan*/  typhoon_recycle_rx_skb (struct typhoon*,scalar_t__) ; 
 int /*<<< orphan*/  vlan_hwaccel_receive_skb (struct sk_buff*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
typhoon_rx(struct typhoon *tp, struct basic_ring *rxRing, volatile __le32 * ready,
	   volatile __le32 * cleared, int budget)
{
	struct rx_desc *rx;
	struct sk_buff *skb, *new_skb;
	struct rxbuff_ent *rxb;
	dma_addr_t dma_addr;
	u32 local_ready;
	u32 rxaddr;
	int pkt_len;
	u32 idx;
	__le32 csum_bits;
	int received;

	received = 0;
	local_ready = le32_to_cpu(*ready);
	rxaddr = le32_to_cpu(*cleared);
	while(rxaddr != local_ready && budget > 0) {
		rx = (struct rx_desc *) (rxRing->ringBase + rxaddr);
		idx = rx->addr;
		rxb = &tp->rxbuffers[idx];
		skb = rxb->skb;
		dma_addr = rxb->dma_addr;

		typhoon_inc_rx_index(&rxaddr, 1);

		if(rx->flags & TYPHOON_RX_ERROR) {
			typhoon_recycle_rx_skb(tp, idx);
			continue;
		}

		pkt_len = le16_to_cpu(rx->frameLen);

		if(pkt_len < rx_copybreak &&
		   (new_skb = dev_alloc_skb(pkt_len + 2)) != NULL) {
			skb_reserve(new_skb, 2);
			pci_dma_sync_single_for_cpu(tp->pdev, dma_addr,
						    PKT_BUF_SZ,
						    PCI_DMA_FROMDEVICE);
			skb_copy_to_linear_data(new_skb, skb->data, pkt_len);
			pci_dma_sync_single_for_device(tp->pdev, dma_addr,
						       PKT_BUF_SZ,
						       PCI_DMA_FROMDEVICE);
			skb_put(new_skb, pkt_len);
			typhoon_recycle_rx_skb(tp, idx);
		} else {
			new_skb = skb;
			skb_put(new_skb, pkt_len);
			pci_unmap_single(tp->pdev, dma_addr, PKT_BUF_SZ,
				       PCI_DMA_FROMDEVICE);
			typhoon_alloc_rx_skb(tp, idx);
		}
		new_skb->protocol = eth_type_trans(new_skb, tp->dev);
		csum_bits = rx->rxStatus & (TYPHOON_RX_IP_CHK_GOOD |
			TYPHOON_RX_UDP_CHK_GOOD | TYPHOON_RX_TCP_CHK_GOOD);
		if(csum_bits ==
		   (TYPHOON_RX_IP_CHK_GOOD | TYPHOON_RX_TCP_CHK_GOOD)
		   || csum_bits ==
		   (TYPHOON_RX_IP_CHK_GOOD | TYPHOON_RX_UDP_CHK_GOOD)) {
			new_skb->ip_summed = CHECKSUM_UNNECESSARY;
		} else
			new_skb->ip_summed = CHECKSUM_NONE;

		spin_lock(&tp->state_lock);
		if(tp->vlgrp != NULL && rx->rxStatus & TYPHOON_RX_VLAN)
			vlan_hwaccel_receive_skb(new_skb, tp->vlgrp,
						 ntohl(rx->vlanTag) & 0xffff);
		else
			netif_receive_skb(new_skb);
		spin_unlock(&tp->state_lock);

		received++;
		budget--;
	}
	*cleared = cpu_to_le32(rxaddr);

	return received;
}