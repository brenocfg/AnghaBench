#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct p54p_ring_control {void** host_idx; } ;
struct TYPE_4__ {scalar_t__ rx_mtu; } ;
struct p54p_priv {TYPE_1__ common; TYPE_2__* pdev; struct p54p_ring_control* ring_control; } ;
struct p54p_desc {scalar_t__ flags; int /*<<< orphan*/  len; scalar_t__ device_addr; void* host_addr; } ;
struct ieee80211_hw {struct p54p_priv* priv; } ;
typedef  size_t dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (size_t) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 size_t le32_to_cpu (void*) ; 
 scalar_t__ pci_dma_mapping_error (TYPE_2__*,size_t) ; 
 size_t pci_map_single (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void p54p_refill_rx_ring(struct ieee80211_hw *dev,
	int ring_index, struct p54p_desc *ring, u32 ring_limit,
	struct sk_buff **rx_buf, u32 index)
{
	struct p54p_priv *priv = dev->priv;
	struct p54p_ring_control *ring_control = priv->ring_control;
	u32 limit, idx, i;

	idx = le32_to_cpu(ring_control->host_idx[ring_index]);
	limit = idx;
	limit -= index;
	limit = ring_limit - limit;

	i = idx % ring_limit;
	while (limit-- > 1) {
		struct p54p_desc *desc = &ring[i];

		if (!desc->host_addr) {
			struct sk_buff *skb;
			dma_addr_t mapping;
			skb = dev_alloc_skb(priv->common.rx_mtu + 32);
			if (!skb)
				break;

			mapping = pci_map_single(priv->pdev,
						 skb_tail_pointer(skb),
						 priv->common.rx_mtu + 32,
						 PCI_DMA_FROMDEVICE);

			if (pci_dma_mapping_error(priv->pdev, mapping)) {
				dev_kfree_skb_any(skb);
				dev_err(&priv->pdev->dev,
					"RX DMA Mapping error\n");
				break;
			}

			desc->host_addr = cpu_to_le32(mapping);
			desc->device_addr = 0;	// FIXME: necessary?
			desc->len = cpu_to_le16(priv->common.rx_mtu + 32);
			desc->flags = 0;
			rx_buf[i] = skb;
		}

		i++;
		idx++;
		i %= ring_limit;
	}

	wmb();
	ring_control->host_idx[ring_index] = cpu_to_le32(idx);
}