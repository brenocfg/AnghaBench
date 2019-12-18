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
typedef  scalar_t__ u64 ;
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct s2io_nic {int /*<<< orphan*/  pdev; } ;
struct fifo_info {int max_txds; scalar_t__ ufo_in_band_v; struct s2io_nic* nic; } ;
struct TxD {scalar_t__ Host_Control; scalar_t__ Buffer_Pointer; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {size_t nr_frags; TYPE_1__* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  memset (struct TxD*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *s2io_txdl_getskb(struct fifo_info *fifo_data,
					struct TxD *txdlp, int get_off)
{
	struct s2io_nic *nic = fifo_data->nic;
	struct sk_buff *skb;
	struct TxD *txds;
	u16 j, frg_cnt;

	txds = txdlp;
	if (txds->Host_Control == (u64)(long)fifo_data->ufo_in_band_v) {
		pci_unmap_single(nic->pdev, (dma_addr_t)txds->Buffer_Pointer,
				 sizeof(u64), PCI_DMA_TODEVICE);
		txds++;
	}

	skb = (struct sk_buff *)((unsigned long)txds->Host_Control);
	if (!skb) {
		memset(txdlp, 0, (sizeof(struct TxD) * fifo_data->max_txds));
		return NULL;
	}
	pci_unmap_single(nic->pdev, (dma_addr_t)txds->Buffer_Pointer,
			 skb_headlen(skb), PCI_DMA_TODEVICE);
	frg_cnt = skb_shinfo(skb)->nr_frags;
	if (frg_cnt) {
		txds++;
		for (j = 0; j < frg_cnt; j++, txds++) {
			skb_frag_t *frag = &skb_shinfo(skb)->frags[j];
			if (!txds->Buffer_Pointer)
				break;
			pci_unmap_page(nic->pdev,
				       (dma_addr_t)txds->Buffer_Pointer,
				       frag->size, PCI_DMA_TODEVICE);
		}
	}
	memset(txdlp, 0, (sizeof(struct TxD) * fifo_data->max_txds));
	return skb;
}