#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int read_ptr; } ;
struct il_tx_queue {TYPE_2__ q; struct sk_buff** skbs; int /*<<< orphan*/ * meta; scalar_t__ tfds; } ;
struct il_priv {struct pci_dev* pci_dev; } ;
struct il3945_tfd {TYPE_1__* tbs; int /*<<< orphan*/  control_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int NUM_TFD_CHUNKS ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TFD_CTL_COUNT_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
il3945_hw_txq_free_tfd(struct il_priv *il, struct il_tx_queue *txq)
{
	struct il3945_tfd *tfd_tmp = (struct il3945_tfd *)txq->tfds;
	int idx = txq->q.read_ptr;
	struct il3945_tfd *tfd = &tfd_tmp[idx];
	struct pci_dev *dev = il->pci_dev;
	int i;
	int counter;

	/* sanity check */
	counter = TFD_CTL_COUNT_GET(le32_to_cpu(tfd->control_flags));
	if (counter > NUM_TFD_CHUNKS) {
		IL_ERR("Too many chunks: %i\n", counter);
		/* @todo issue fatal error, it is quite serious situation */
		return;
	}

	/* Unmap tx_cmd */
	if (counter)
		pci_unmap_single(dev, dma_unmap_addr(&txq->meta[idx], mapping),
				 dma_unmap_len(&txq->meta[idx], len),
				 PCI_DMA_TODEVICE);

	/* unmap chunks if any */

	for (i = 1; i < counter; i++)
		pci_unmap_single(dev, le32_to_cpu(tfd->tbs[i].addr),
				 le32_to_cpu(tfd->tbs[i].len),
				 PCI_DMA_TODEVICE);

	/* free SKB */
	if (txq->skbs) {
		struct sk_buff *skb = txq->skbs[txq->q.read_ptr];

		/* can be called from irqs-disabled context */
		if (skb) {
			dev_kfree_skb_any(skb);
			txq->skbs[txq->q.read_ptr] = NULL;
		}
	}
}