#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct p54p_ring_control {int /*<<< orphan*/ * device_idx; } ;
struct TYPE_5__ {scalar_t__ rx_mtu; } ;
struct p54p_priv {TYPE_1__ common; TYPE_2__* pdev; struct p54p_ring_control* ring_control; } ;
struct p54p_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  host_addr; } ;
struct ieee80211_hw {struct p54p_priv* priv; } ;
typedef  void* dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ p54_rx (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  p54p_refill_rx_ring (struct ieee80211_hw*,int,struct p54p_desc*,size_t,struct sk_buff**,size_t) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (TYPE_2__*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (TYPE_2__*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (TYPE_2__*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void p54p_check_rx_ring(struct ieee80211_hw *dev, u32 *index,
	int ring_index, struct p54p_desc *ring, u32 ring_limit,
	struct sk_buff **rx_buf)
{
	struct p54p_priv *priv = dev->priv;
	struct p54p_ring_control *ring_control = priv->ring_control;
	struct p54p_desc *desc;
	u32 idx, i;

	i = (*index) % ring_limit;
	(*index) = idx = le32_to_cpu(ring_control->device_idx[ring_index]);
	idx %= ring_limit;
	while (i != idx) {
		u16 len;
		struct sk_buff *skb;
		dma_addr_t dma_addr;
		desc = &ring[i];
		len = le16_to_cpu(desc->len);
		skb = rx_buf[i];

		if (!skb) {
			i++;
			i %= ring_limit;
			continue;
		}

		if (unlikely(len > priv->common.rx_mtu)) {
			if (net_ratelimit())
				dev_err(&priv->pdev->dev, "rx'd frame size "
					"exceeds length threshold.\n");

			len = priv->common.rx_mtu;
		}
		dma_addr = le32_to_cpu(desc->host_addr);
		pci_dma_sync_single_for_cpu(priv->pdev, dma_addr,
			priv->common.rx_mtu + 32, PCI_DMA_FROMDEVICE);
		skb_put(skb, len);

		if (p54_rx(dev, skb)) {
			pci_unmap_single(priv->pdev, dma_addr,
				priv->common.rx_mtu + 32, PCI_DMA_FROMDEVICE);
			rx_buf[i] = NULL;
			desc->host_addr = cpu_to_le32(0);
		} else {
			skb_trim(skb, 0);
			pci_dma_sync_single_for_device(priv->pdev, dma_addr,
				priv->common.rx_mtu + 32, PCI_DMA_FROMDEVICE);
			desc->len = cpu_to_le16(priv->common.rx_mtu + 32);
		}

		i++;
		i %= ring_limit;
	}

	p54p_refill_rx_ring(dev, ring_index, ring, ring_limit, rx_buf, *index);
}