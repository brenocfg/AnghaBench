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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct scq_info {int /*<<< orphan*/  pending; int /*<<< orphan*/  transmit; int /*<<< orphan*/  paddr; int /*<<< orphan*/  base; } ;
struct idt77252_dev {int /*<<< orphan*/  pcidev; } ;
struct atm_vcc {int /*<<< orphan*/  (* pop ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct TYPE_2__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 TYPE_1__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  IDT77252_PRV_PADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  SCQ_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct scq_info*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static void
free_scq(struct idt77252_dev *card, struct scq_info *scq)
{
	struct sk_buff *skb;
	struct atm_vcc *vcc;

	pci_free_consistent(card->pcidev, SCQ_SIZE,
			    scq->base, scq->paddr);

	while ((skb = skb_dequeue(&scq->transmit))) {
		pci_unmap_single(card->pcidev, IDT77252_PRV_PADDR(skb),
				 skb->len, PCI_DMA_TODEVICE);

		vcc = ATM_SKB(skb)->vcc;
		if (vcc->pop)
			vcc->pop(vcc, skb);
		else
			dev_kfree_skb(skb);
	}

	while ((skb = skb_dequeue(&scq->pending))) {
		pci_unmap_single(card->pcidev, IDT77252_PRV_PADDR(skb),
				 skb->len, PCI_DMA_TODEVICE);

		vcc = ATM_SKB(skb)->vcc;
		if (vcc->pop)
			vcc->pop(vcc, skb);
		else
			dev_kfree_skb(skb);
	}

	kfree(scq);
}