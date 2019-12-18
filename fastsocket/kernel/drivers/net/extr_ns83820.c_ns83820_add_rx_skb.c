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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {unsigned int next_empty; unsigned int next_rx; scalar_t__ phy_descs; int /*<<< orphan*/ * descs; struct sk_buff** skbs; int /*<<< orphan*/  nr_used; } ;
struct ns83820 {TYPE_1__ rx_info; int /*<<< orphan*/  pci_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CMDSTS_INTR ; 
 unsigned int DESC_SIZE ; 
 unsigned int NR_RX_DESC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int REAL_RX_BUF_SIZE ; 
 int /*<<< orphan*/  build_rx_desc (struct ns83820*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int nr_rx_empty (struct ns83820*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ns83820_add_rx_skb(struct ns83820 *dev, struct sk_buff *skb)
{
	unsigned next_empty;
	u32 cmdsts;
	__le32 *sg;
	dma_addr_t buf;

	next_empty = dev->rx_info.next_empty;

	/* don't overrun last rx marker */
	if (unlikely(nr_rx_empty(dev) <= 2)) {
		kfree_skb(skb);
		return 1;
	}

#if 0
	dprintk("next_empty[%d] nr_used[%d] next_rx[%d]\n",
		dev->rx_info.next_empty,
		dev->rx_info.nr_used,
		dev->rx_info.next_rx
		);
#endif

	sg = dev->rx_info.descs + (next_empty * DESC_SIZE);
	BUG_ON(NULL != dev->rx_info.skbs[next_empty]);
	dev->rx_info.skbs[next_empty] = skb;

	dev->rx_info.next_empty = (next_empty + 1) % NR_RX_DESC;
	cmdsts = REAL_RX_BUF_SIZE | CMDSTS_INTR;
	buf = pci_map_single(dev->pci_dev, skb->data,
			     REAL_RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
	build_rx_desc(dev, sg, 0, buf, cmdsts, 0);
	/* update link of previous rx */
	if (likely(next_empty != dev->rx_info.next_rx))
		dev->rx_info.descs[((NR_RX_DESC + next_empty - 1) % NR_RX_DESC) * DESC_SIZE] = cpu_to_le32(dev->rx_info.phy_descs + (next_empty * DESC_SIZE * 4));

	return 0;
}