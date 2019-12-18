#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ status_error; int /*<<< orphan*/  length; } ;
struct TYPE_8__ {TYPE_1__ upper; } ;
union ixgbe_adv_rx_desc {TYPE_2__ wb; } ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ len; struct sk_buff* next; union ixgbe_adv_rx_desc* data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ixgbevf_rx_buffer {struct sk_buff* skb; scalar_t__ dma; } ;
struct ixgbevf_ring {unsigned int next_to_clean; unsigned int count; unsigned int total_packets; unsigned int total_bytes; struct ixgbevf_rx_buffer* rx_buffer_info; int /*<<< orphan*/  netdev; int /*<<< orphan*/  rx_buf_len; } ;
struct TYPE_11__ {unsigned int total_packets; unsigned int total_bytes; } ;
struct ixgbevf_q_vector {TYPE_5__ rx; struct ixgbevf_adapter* adapter; } ;
struct ixgbevf_adapter {TYPE_4__* netdev; int /*<<< orphan*/  non_eop_descs; struct pci_dev* pdev; } ;
struct TYPE_12__ {struct sk_buff* prev; } ;
struct TYPE_9__ {unsigned int rx_bytes; unsigned int rx_packets; } ;
struct TYPE_10__ {TYPE_3__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int IXGBEVF_RX_BUFFER_WRITE ; 
 union ixgbe_adv_rx_desc* IXGBEVF_RX_DESC (struct ixgbevf_ring*,unsigned int) ; 
 TYPE_6__* IXGBE_CB (struct sk_buff*) ; 
 int IXGBE_DESC_UNUSED (struct ixgbevf_ring*) ; 
 int IXGBE_RXDADV_ERR_FRAME_ERR_MASK ; 
 int IXGBE_RXD_STAT_DD ; 
 int IXGBE_RXD_STAT_EOP ; 
 int IXGBE_RXD_STAT_LB ; 
 union ixgbe_adv_rx_desc* NET_IP_ALIGN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_alloc_rx_buffers (struct ixgbevf_adapter*,struct ixgbevf_ring*,int) ; 
 int /*<<< orphan*/  ixgbevf_receive_skb (struct ixgbevf_q_vector*,struct sk_buff*,int,union ixgbe_adv_rx_desc*) ; 
 int /*<<< orphan*/  ixgbevf_rx_checksum (struct ixgbevf_adapter*,struct ixgbevf_ring*,int,struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  prefetch (union ixgbe_adv_rx_desc*) ; 
 int /*<<< orphan*/  rmb () ; 
 int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ixgbevf_clean_rx_irq(struct ixgbevf_q_vector *q_vector,
				 struct ixgbevf_ring *rx_ring,
				 int budget)
{
	struct ixgbevf_adapter *adapter = q_vector->adapter;
	struct pci_dev *pdev = adapter->pdev;
	union ixgbe_adv_rx_desc *rx_desc, *next_rxd;
	struct ixgbevf_rx_buffer *rx_buffer_info, *next_buffer;
	struct sk_buff *skb;
	unsigned int i;
	u32 len, staterr;
	int cleaned_count = 0;
	unsigned int total_rx_bytes = 0, total_rx_packets = 0;

	i = rx_ring->next_to_clean;
	rx_desc = IXGBEVF_RX_DESC(rx_ring, i);
	staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	rx_buffer_info = &rx_ring->rx_buffer_info[i];

	while (staterr & IXGBE_RXD_STAT_DD) {
		if (!budget)
			break;
		budget--;

		rmb(); /* read descriptor and rx_buffer_info after status DD */
		len = le16_to_cpu(rx_desc->wb.upper.length);
		skb = rx_buffer_info->skb;
		prefetch(skb->data - NET_IP_ALIGN);
		rx_buffer_info->skb = NULL;

		if (rx_buffer_info->dma) {
			dma_unmap_single(&pdev->dev, rx_buffer_info->dma,
					 rx_ring->rx_buf_len,
					 DMA_FROM_DEVICE);
			rx_buffer_info->dma = 0;
			skb_put(skb, len);
		}

		i++;
		if (i == rx_ring->count)
			i = 0;

		next_rxd = IXGBEVF_RX_DESC(rx_ring, i);
		prefetch(next_rxd);
		cleaned_count++;

		next_buffer = &rx_ring->rx_buffer_info[i];

		if (!(staterr & IXGBE_RXD_STAT_EOP)) {
			skb->next = next_buffer->skb;
			IXGBE_CB(skb->next)->prev = skb;
			adapter->non_eop_descs++;
			goto next_desc;
		}

		/* we should not be chaining buffers, if we did drop the skb */
		if (IXGBE_CB(skb)->prev) {
			do {
				struct sk_buff *this = skb;
				skb = IXGBE_CB(skb)->prev;
				dev_kfree_skb(this);
			} while (skb);
			goto next_desc;
		}

		/* ERR_MASK will only have valid bits if EOP set */
		if (unlikely(staterr & IXGBE_RXDADV_ERR_FRAME_ERR_MASK)) {
			dev_kfree_skb_irq(skb);
			goto next_desc;
		}

		ixgbevf_rx_checksum(adapter, rx_ring, staterr, skb);

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;
		total_rx_packets++;

		/*
		 * Work around issue of some types of VM to VM loop back
		 * packets not getting split correctly
		 */
		if (staterr & IXGBE_RXD_STAT_LB) {
			u32 header_fixup_len = skb_headlen(skb);
			if (header_fixup_len < 14)
				skb_push(skb, header_fixup_len);
		}
		skb->protocol = eth_type_trans(skb, rx_ring->netdev);

		ixgbevf_receive_skb(q_vector, skb, staterr, rx_desc);

next_desc:
		rx_desc->wb.upper.status_error = 0;

		/* return some buffers to hardware, one at a time is too slow */
		if (cleaned_count >= IXGBEVF_RX_BUFFER_WRITE) {
			ixgbevf_alloc_rx_buffers(adapter, rx_ring,
						 cleaned_count);
			cleaned_count = 0;
		}

		/* use prefetched values */
		rx_desc = next_rxd;
		rx_buffer_info = &rx_ring->rx_buffer_info[i];

		staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	}

	rx_ring->next_to_clean = i;
	cleaned_count = IXGBE_DESC_UNUSED(rx_ring);

	if (cleaned_count)
		ixgbevf_alloc_rx_buffers(adapter, rx_ring, cleaned_count);

	rx_ring->total_packets += total_rx_packets;
	rx_ring->total_bytes += total_rx_bytes;
	adapter->netdev->stats.rx_bytes += total_rx_bytes;
	adapter->netdev->stats.rx_packets += total_rx_packets;
	q_vector->rx.total_packets += total_rx_packets;
	q_vector->rx.total_bytes += total_rx_bytes;

	return !!budget;
}