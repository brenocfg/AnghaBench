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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct dscc4_dev_priv {unsigned int rx_dirty; TYPE_1__* pci_priv; struct sk_buff** rx_skbuff; struct RxFD* rx_fd; } ;
struct RxFD {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDLC_MAX_MRU ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_MAX (int /*<<< orphan*/ ) ; 
 unsigned int RX_RING_SIZE ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int const) ; 
 int /*<<< orphan*/  hdlc_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int try_get_rx_skb(struct dscc4_dev_priv *dpriv,
				 struct net_device *dev)
{
	unsigned int dirty = dpriv->rx_dirty%RX_RING_SIZE;
	struct RxFD *rx_fd = dpriv->rx_fd + dirty;
	const int len = RX_MAX(HDLC_MAX_MRU);
	struct sk_buff *skb;
	int ret = 0;

	skb = dev_alloc_skb(len);
	dpriv->rx_skbuff[dirty] = skb;
	if (skb) {
		skb->protocol = hdlc_type_trans(skb, dev);
		rx_fd->data = cpu_to_le32(pci_map_single(dpriv->pci_priv->pdev,
					  skb->data, len, PCI_DMA_FROMDEVICE));
	} else {
		rx_fd->data = 0;
		ret = -1;
	}
	return ret;
}