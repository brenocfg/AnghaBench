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
struct TYPE_2__ {int /*<<< orphan*/  pkt_addr; } ;
union ixgbe_adv_rx_desc {TYPE_1__ read; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ixgbevf_rx_buffer {int /*<<< orphan*/  dma; struct sk_buff* skb; } ;
struct ixgbevf_ring {unsigned int next_to_use; unsigned int count; struct ixgbevf_rx_buffer* rx_buffer_info; int /*<<< orphan*/  rx_buf_len; int /*<<< orphan*/  netdev; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  hw; int /*<<< orphan*/  alloc_rx_buff_failed; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 union ixgbe_adv_rx_desc* IXGBEVF_RX_DESC (struct ixgbevf_ring*,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_release_rx_desc (int /*<<< orphan*/ *,struct ixgbevf_ring*,unsigned int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbevf_alloc_rx_buffers(struct ixgbevf_adapter *adapter,
				     struct ixgbevf_ring *rx_ring,
				     int cleaned_count)
{
	struct pci_dev *pdev = adapter->pdev;
	union ixgbe_adv_rx_desc *rx_desc;
	struct ixgbevf_rx_buffer *bi;
	unsigned int i = rx_ring->next_to_use;

	bi = &rx_ring->rx_buffer_info[i];

	while (cleaned_count--) {
		rx_desc = IXGBEVF_RX_DESC(rx_ring, i);

		if (!bi->skb) {
			struct sk_buff *skb;

			skb = netdev_alloc_skb_ip_align(rx_ring->netdev,
							rx_ring->rx_buf_len);
			if (!skb) {
				adapter->alloc_rx_buff_failed++;
				goto no_buffers;
			}
			bi->skb = skb;

			bi->dma = dma_map_single(&pdev->dev, skb->data,
						 rx_ring->rx_buf_len,
						 DMA_FROM_DEVICE);
			if (dma_mapping_error(&pdev->dev, bi->dma)) {
				dev_kfree_skb(skb);
				bi->skb = NULL;
				dev_err(&pdev->dev, "RX DMA map failed\n");
				break;
			}
		}
		rx_desc->read.pkt_addr = cpu_to_le64(bi->dma);

		i++;
		if (i == rx_ring->count)
			i = 0;
		bi = &rx_ring->rx_buffer_info[i];
	}

no_buffers:
	if (rx_ring->next_to_use != i) {
		rx_ring->next_to_use = i;
		ixgbevf_release_rx_desc(&adapter->hw, rx_ring, i);
	}
}