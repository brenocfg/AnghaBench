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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct sge {unsigned int rx_pkt_pad; TYPE_1__* adapter; } ;
struct pci_dev {int dummy; } ;
struct freelQ_e {int addr_hi; int len_gen; int /*<<< orphan*/  gen2; scalar_t__ addr_lo; } ;
struct freelQ_ce {struct sk_buff* skb; } ;
struct freelQ {size_t pidx; unsigned int rx_buffer_size; unsigned int dma_offset; size_t credits; size_t size; int genbit; struct freelQ_e* entries; struct freelQ_ce* centries; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int V_CMD_GEN1 (int) ; 
 int /*<<< orphan*/  V_CMD_GEN2 (int) ; 
 int V_CMD_LEN (unsigned int) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_addr ; 
 scalar_t__ pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_addr_set (struct freelQ_ce*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_len_set (struct freelQ_ce*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void refill_free_list(struct sge *sge, struct freelQ *q)
{
	struct pci_dev *pdev = sge->adapter->pdev;
	struct freelQ_ce *ce = &q->centries[q->pidx];
	struct freelQ_e *e = &q->entries[q->pidx];
	unsigned int dma_len = q->rx_buffer_size - q->dma_offset;

	while (q->credits < q->size) {
		struct sk_buff *skb;
		dma_addr_t mapping;

		skb = alloc_skb(q->rx_buffer_size, GFP_ATOMIC);
		if (!skb)
			break;

		skb_reserve(skb, q->dma_offset);
		mapping = pci_map_single(pdev, skb->data, dma_len,
					 PCI_DMA_FROMDEVICE);
		skb_reserve(skb, sge->rx_pkt_pad);

		ce->skb = skb;
		pci_unmap_addr_set(ce, dma_addr, mapping);
		pci_unmap_len_set(ce, dma_len, dma_len);
		e->addr_lo = (u32)mapping;
		e->addr_hi = (u64)mapping >> 32;
		e->len_gen = V_CMD_LEN(dma_len) | V_CMD_GEN1(q->genbit);
		wmb();
		e->gen2 = V_CMD_GEN2(q->genbit);

		e++;
		ce++;
		if (++q->pidx == q->size) {
			q->pidx = 0;
			q->genbit ^= 1;
			ce = q->centries;
			e = q->entries;
		}
		q->credits++;
	}
}