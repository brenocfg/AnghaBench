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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct e1000_rx_ring {unsigned int next_to_use; unsigned int count; scalar_t__ rdt; struct e1000_buffer* buffer_info; } ;
struct e1000_rx_desc {int /*<<< orphan*/  buffer_addr; } ;
struct e1000_buffer {scalar_t__ dma; struct sk_buff* skb; int /*<<< orphan*/ * page; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {scalar_t__ hw_addr; } ;
struct e1000_adapter {TYPE_1__ hw; int /*<<< orphan*/  alloc_rx_buff_failed; int /*<<< orphan*/  rx_buffer_len; struct pci_dev* pdev; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct e1000_rx_desc* E1000_RX_DESC (struct e1000_rx_ring,unsigned int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dma_map_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  e1000_check_64k_bound (struct e1000_adapter*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void
e1000_alloc_jumbo_rx_buffers(struct e1000_adapter *adapter,
                             struct e1000_rx_ring *rx_ring, int cleaned_count)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_rx_desc *rx_desc;
	struct e1000_buffer *buffer_info;
	struct sk_buff *skb;
	unsigned int i;
	unsigned int bufsz = 256 - 16 /*for skb_reserve */ ;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	while (cleaned_count--) {
		skb = buffer_info->skb;
		if (skb) {
			skb_trim(skb, 0);
			goto check_page;
		}

		skb = netdev_alloc_skb_ip_align(netdev, bufsz);
		if (unlikely(!skb)) {
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			break;
		}

		/* Fix for errata 23, can't cross 64kB boundary */
		if (!e1000_check_64k_bound(adapter, skb->data, bufsz)) {
			struct sk_buff *oldskb = skb;
			e_err(rx_err, "skb align check failed: %u bytes at "
			      "%p\n", bufsz, skb->data);
			/* Try again, without freeing the previous */
			skb = netdev_alloc_skb_ip_align(netdev, bufsz);
			/* Failed allocation, critical failure */
			if (!skb) {
				dev_kfree_skb(oldskb);
				adapter->alloc_rx_buff_failed++;
				break;
			}

			if (!e1000_check_64k_bound(adapter, skb->data, bufsz)) {
				/* give up */
				dev_kfree_skb(skb);
				dev_kfree_skb(oldskb);
				break; /* while (cleaned_count--) */
			}

			/* Use new allocation */
			dev_kfree_skb(oldskb);
		}
		buffer_info->skb = skb;
		buffer_info->length = adapter->rx_buffer_len;
check_page:
		/* allocate a new page if necessary */
		if (!buffer_info->page) {
			buffer_info->page = alloc_page(GFP_ATOMIC);
			if (unlikely(!buffer_info->page)) {
				adapter->alloc_rx_buff_failed++;
				break;
			}
		}

		if (!buffer_info->dma) {
			buffer_info->dma = dma_map_page(&pdev->dev,
			                                buffer_info->page, 0,
							buffer_info->length,
							DMA_FROM_DEVICE);
			if (dma_mapping_error(&pdev->dev, buffer_info->dma)) {
				put_page(buffer_info->page);
				dev_kfree_skb(skb);
				buffer_info->page = NULL;
				buffer_info->skb = NULL;
				buffer_info->dma = 0;
				adapter->alloc_rx_buff_failed++;
				break; /* while !buffer_info->skb */
			}
		}

		rx_desc = E1000_RX_DESC(*rx_ring, i);
		rx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);

		if (unlikely(++i == rx_ring->count))
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	}

	if (likely(rx_ring->next_to_use != i)) {
		rx_ring->next_to_use = i;
		if (unlikely(i-- == 0))
			i = (rx_ring->count - 1);

		/* Force memory writes to complete before letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable for weak-ordered memory model archs,
		 * such as IA-64). */
		wmb();
		writel(i, adapter->hw.hw_addr + rx_ring->rdt);
	}
}