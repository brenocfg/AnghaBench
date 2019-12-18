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
struct sk_buff {int dummy; } ;
struct qlcnic_skb_frag {int /*<<< orphan*/  dma; int /*<<< orphan*/  length; } ;
struct qlcnic_cmd_buffer {int /*<<< orphan*/ * skb; struct qlcnic_skb_frag* frag_array; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void qlcnic_unmap_buffers(struct pci_dev *pdev, struct sk_buff *skb,
				 struct qlcnic_cmd_buffer *pbuf)
{
	struct qlcnic_skb_frag *nf = &pbuf->frag_array[0];
	int i, nr_frags = skb_shinfo(skb)->nr_frags;

	for (i = 0; i < nr_frags; i++) {
		nf = &pbuf->frag_array[i+1];
		pci_unmap_page(pdev, nf->dma, nf->length, PCI_DMA_TODEVICE);
	}

	nf = &pbuf->frag_array[0];
	pci_unmap_single(pdev, nf->dma, skb_headlen(skb), PCI_DMA_TODEVICE);
	pbuf->skb = NULL;
}