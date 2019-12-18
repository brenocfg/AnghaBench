#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct c2_tx_desc {scalar_t__ len; } ;
struct c2_element {int /*<<< orphan*/ * skb; int /*<<< orphan*/  maplen; int /*<<< orphan*/  mapaddr; struct c2_tx_desc* ht_desc; } ;
struct c2_dev {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int c2_tx_free(struct c2_dev *c2dev, struct c2_element *elem)
{
	struct c2_tx_desc *tx_desc = elem->ht_desc;

	tx_desc->len = 0;

	pci_unmap_single(c2dev->pcidev, elem->mapaddr, elem->maplen,
			 PCI_DMA_TODEVICE);

	if (elem->skb) {
		dev_kfree_skb_any(elem->skb);
		elem->skb = NULL;
	}

	return 0;
}