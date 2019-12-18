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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int read_ptr; } ;
struct il_tx_queue {TYPE_1__ q; struct sk_buff** skbs; int /*<<< orphan*/ * meta; scalar_t__ tfds; } ;
struct il_tfd {int dummy; } ;
struct il_priv {struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int IL_NUM_OF_TBS ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int il4965_tfd_get_num_tbs (struct il_tfd*) ; 
 int /*<<< orphan*/  il4965_tfd_tb_get_addr (struct il_tfd*,int) ; 
 int /*<<< orphan*/  il4965_tfd_tb_get_len (struct il_tfd*,int) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
il4965_hw_txq_free_tfd(struct il_priv *il, struct il_tx_queue *txq)
{
	struct il_tfd *tfd_tmp = (struct il_tfd *)txq->tfds;
	struct il_tfd *tfd;
	struct pci_dev *dev = il->pci_dev;
	int idx = txq->q.read_ptr;
	int i;
	int num_tbs;

	tfd = &tfd_tmp[idx];

	/* Sanity check on number of chunks */
	num_tbs = il4965_tfd_get_num_tbs(tfd);

	if (num_tbs >= IL_NUM_OF_TBS) {
		IL_ERR("Too many chunks: %i\n", num_tbs);
		/* @todo issue fatal error, it is quite serious situation */
		return;
	}

	/* Unmap tx_cmd */
	if (num_tbs)
		pci_unmap_single(dev, dma_unmap_addr(&txq->meta[idx], mapping),
				 dma_unmap_len(&txq->meta[idx], len),
				 PCI_DMA_BIDIRECTIONAL);

	/* Unmap chunks, if any. */
	for (i = 1; i < num_tbs; i++)
		pci_unmap_single(dev, il4965_tfd_tb_get_addr(tfd, i),
				 il4965_tfd_tb_get_len(tfd, i),
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