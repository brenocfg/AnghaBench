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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int* data; scalar_t__ len; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int rx_bytes; unsigned int rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct e1000_rx_ring {unsigned int next_to_clean; unsigned int count; struct sk_buff* rx_skb_top; struct e1000_buffer* buffer_info; } ;
struct e1000_rx_desc {int status; int errors; int /*<<< orphan*/  special; int /*<<< orphan*/  csum; int /*<<< orphan*/  length; } ;
struct e1000_hw {int dummy; } ;
struct e1000_buffer {int /*<<< orphan*/  page; struct sk_buff* skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct e1000_adapter {unsigned int total_rx_packets; unsigned int total_rx_bytes; int /*<<< orphan*/  (* alloc_rx_buf ) (struct e1000_adapter*,struct e1000_rx_ring*,int) ;int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  stats; struct pci_dev* pdev; struct net_device* netdev; struct e1000_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int E1000_DESC_UNUSED (struct e1000_rx_ring*) ; 
 int E1000_RXD_ERR_FRAME_ERR_MASK ; 
 int E1000_RXD_STAT_DD ; 
 int E1000_RXD_STAT_EOP ; 
 int E1000_RX_BUFFER_WRITE ; 
 struct e1000_rx_desc* E1000_RX_DESC (struct e1000_rx_ring,unsigned int) ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  KM_SKB_DATA_SOFTIRQ ; 
 scalar_t__ TBI_ACCEPT (struct e1000_hw*,int,int,int,int) ; 
 int copybreak ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e1000_consume_page (struct e1000_buffer*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  e1000_receive_skb (struct e1000_adapter*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  e1000_rx_checksum (struct e1000_adapter*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  e1000_tbi_adjust_stats (struct e1000_hw*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 int* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  prefetch (struct e1000_rx_desc*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 
 struct sk_buff* rxtop ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct e1000_adapter*,struct e1000_rx_ring*,int) ; 
 int /*<<< orphan*/  stub2 (struct e1000_adapter*,struct e1000_rx_ring*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool e1000_clean_jumbo_rx_irq(struct e1000_adapter *adapter,
				     struct e1000_rx_ring *rx_ring,
				     int *work_done, int work_to_do)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_rx_desc *rx_desc, *next_rxd;
	struct e1000_buffer *buffer_info, *next_buffer;
	unsigned long irq_flags;
	u32 length;
	unsigned int i;
	int cleaned_count = 0;
	bool cleaned = false;
	unsigned int total_rx_bytes=0, total_rx_packets=0;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC(*rx_ring, i);
	buffer_info = &rx_ring->buffer_info[i];

	while (rx_desc->status & E1000_RXD_STAT_DD) {
		struct sk_buff *skb;
		u8 status;

		if (*work_done >= work_to_do)
			break;
		(*work_done)++;
		rmb(); /* read descriptor and rx_buffer_info after status DD */

		status = rx_desc->status;
		skb = buffer_info->skb;
		buffer_info->skb = NULL;

		if (++i == rx_ring->count) i = 0;
		next_rxd = E1000_RX_DESC(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;
		dma_unmap_page(&pdev->dev, buffer_info->dma,
			       buffer_info->length, DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		length = le16_to_cpu(rx_desc->length);

		/* errors is only valid for DD + EOP descriptors */
		if (unlikely((status & E1000_RXD_STAT_EOP) &&
		    (rx_desc->errors & E1000_RXD_ERR_FRAME_ERR_MASK))) {
			u8 last_byte = *(skb->data + length - 1);
			if (TBI_ACCEPT(hw, status, rx_desc->errors, length,
				       last_byte)) {
				spin_lock_irqsave(&adapter->stats_lock,
				                  irq_flags);
				e1000_tbi_adjust_stats(hw, &adapter->stats,
				                       length, skb->data);
				spin_unlock_irqrestore(&adapter->stats_lock,
				                       irq_flags);
				length--;
			} else {
				/* recycle both page and skb */
				buffer_info->skb = skb;
				/* an error means any chain goes out the window
				 * too */
				if (rx_ring->rx_skb_top)
					dev_kfree_skb(rx_ring->rx_skb_top);
				rx_ring->rx_skb_top = NULL;
				goto next_desc;
			}
		}

#define rxtop rx_ring->rx_skb_top
		if (!(status & E1000_RXD_STAT_EOP)) {
			/* this descriptor is only the beginning (or middle) */
			if (!rxtop) {
				/* this is the beginning of a chain */
				rxtop = skb;
				skb_fill_page_desc(rxtop, 0, buffer_info->page,
				                   0, length);
			} else {
				/* this is the middle of a chain */
				skb_fill_page_desc(rxtop,
				    skb_shinfo(rxtop)->nr_frags,
				    buffer_info->page, 0, length);
				/* re-use the skb, only consumed the page */
				buffer_info->skb = skb;
			}
			e1000_consume_page(buffer_info, rxtop, length);
			goto next_desc;
		} else {
			if (rxtop) {
				/* end of the chain */
				skb_fill_page_desc(rxtop,
				    skb_shinfo(rxtop)->nr_frags,
				    buffer_info->page, 0, length);
				/* re-use the current skb, we only consumed the
				 * page */
				buffer_info->skb = skb;
				skb = rxtop;
				rxtop = NULL;
				e1000_consume_page(buffer_info, skb, length);
			} else {
				/* no chain, got EOP, this buf is the packet
				 * copybreak to save the put_page/alloc_page */
				if (length <= copybreak &&
				    skb_tailroom(skb) >= length) {
					u8 *vaddr;
					vaddr = kmap_atomic(buffer_info->page,
					                    KM_SKB_DATA_SOFTIRQ);
					memcpy(skb_tail_pointer(skb), vaddr, length);
					kunmap_atomic(vaddr,
					              KM_SKB_DATA_SOFTIRQ);
					/* re-use the page, so don't erase
					 * buffer_info->page */
					skb_put(skb, length);
				} else {
					skb_fill_page_desc(skb, 0,
					                   buffer_info->page, 0,
				                           length);
					e1000_consume_page(buffer_info, skb,
					                   length);
				}
			}
		}

		/* Receive Checksum Offload XXX recompute due to CRC strip? */
		e1000_rx_checksum(adapter,
		                  (u32)(status) |
		                  ((u32)(rx_desc->errors) << 24),
		                  le16_to_cpu(rx_desc->csum), skb);

		pskb_trim(skb, skb->len - 4);

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;
		total_rx_packets++;

		/* eth type trans needs skb->data to point to something */
		if (!pskb_may_pull(skb, ETH_HLEN)) {
			e_err(drv, "pskb_may_pull failed.\n");
			dev_kfree_skb(skb);
			goto next_desc;
		}

		e1000_receive_skb(adapter, status, rx_desc->special, skb);

next_desc:
		rx_desc->status = 0;

		/* return some buffers to hardware, one at a time is too slow */
		if (unlikely(cleaned_count >= E1000_RX_BUFFER_WRITE)) {
			adapter->alloc_rx_buf(adapter, rx_ring, cleaned_count);
			cleaned_count = 0;
		}

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;
	}
	rx_ring->next_to_clean = i;

	cleaned_count = E1000_DESC_UNUSED(rx_ring);
	if (cleaned_count)
		adapter->alloc_rx_buf(adapter, rx_ring, cleaned_count);

	adapter->total_rx_packets += total_rx_packets;
	adapter->total_rx_bytes += total_rx_bytes;
	netdev->stats.rx_bytes += total_rx_bytes;
	netdev->stats.rx_packets += total_rx_packets;
	return cleaned;
}