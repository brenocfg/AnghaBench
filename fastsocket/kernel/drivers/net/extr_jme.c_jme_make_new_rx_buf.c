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
struct jme_ring {struct jme_buffer_info* bufinf; } ;
struct jme_buffer_info {int /*<<< orphan*/  len; int /*<<< orphan*/  mapping; struct sk_buff* skb; } ;
struct jme_adapter {int /*<<< orphan*/  pdev; TYPE_1__* dev; struct jme_ring* rxring; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ RX_EXTRA_LEN ; 
 struct sk_buff* netdev_alloc_skb (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jme_make_new_rx_buf(struct jme_adapter *jme, int i)
{
	struct jme_ring *rxring = &(jme->rxring[0]);
	struct jme_buffer_info *rxbi = rxring->bufinf + i;
	struct sk_buff *skb;

	skb = netdev_alloc_skb(jme->dev,
		jme->dev->mtu + RX_EXTRA_LEN);
	if (unlikely(!skb))
		return -ENOMEM;

	rxbi->skb = skb;
	rxbi->len = skb_tailroom(skb);
	rxbi->mapping = pci_map_page(jme->pdev,
					virt_to_page(skb->data),
					offset_in_page(skb->data),
					rxbi->len,
					PCI_DMA_FROMDEVICE);

	return 0;
}