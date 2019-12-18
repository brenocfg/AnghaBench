#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
struct TYPE_6__ {int size; void* dmaend; void* dmairq; void* dmastart; scalar_t__ start; } ;
struct TYPE_5__ {int size; void* dmaend; void* dmairq; void* dmastart; scalar_t__ start; } ;
struct tiger_hw {scalar_t__ base; TYPE_3__ recv; int /*<<< orphan*/  name; scalar_t__ dma; scalar_t__ dma_p; TYPE_2__ send; TYPE_1__* bc; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {void* hrbuf; void* hsbuf; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NJ_DMA_READ_END ; 
 scalar_t__ NJ_DMA_READ_IRQ ; 
 scalar_t__ NJ_DMA_READ_START ; 
 int NJ_DMA_RXSIZE ; 
 int NJ_DMA_SIZE ; 
 int NJ_DMA_TXSIZE ; 
 scalar_t__ NJ_DMA_WRITE_END ; 
 scalar_t__ NJ_DMA_WRITE_IRQ ; 
 scalar_t__ NJ_DMA_WRITE_START ; 
 int debug ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  outl (void*,scalar_t__) ; 
 scalar_t__ pci_alloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,void*,void*,void*,scalar_t__,int) ; 

__attribute__((used)) static int
inittiger(struct tiger_hw *card)
{
	int i;

	card->dma_p = pci_alloc_consistent(card->pdev, NJ_DMA_SIZE,
			&card->dma);
	if (!card->dma_p) {
		pr_info("%s: No DMA memory\n", card->name);
		return -ENOMEM;
	}
	if ((u64)card->dma > 0xffffffff) {
		pr_info("%s: DMA outside 32 bit\n", card->name);
		return -ENOMEM;
	}
	for (i = 0; i < 2; i++) {
		card->bc[i].hsbuf = kmalloc(NJ_DMA_TXSIZE, GFP_KERNEL);
		if (!card->bc[i].hsbuf) {
			pr_info("%s: no B%d send buffer\n", card->name, i + 1);
			return -ENOMEM;
		}
		card->bc[i].hrbuf = kmalloc(NJ_DMA_RXSIZE, GFP_KERNEL);
		if (!card->bc[i].hrbuf) {
			pr_info("%s: no B%d recv buffer\n", card->name, i + 1);
			return -ENOMEM;
		}
	}
	memset(card->dma_p, 0xff, NJ_DMA_SIZE);

	card->send.start = card->dma_p;
	card->send.dmastart = (u32)card->dma;
	card->send.dmaend = card->send.dmastart +
		(4 * (NJ_DMA_TXSIZE - 1));
	card->send.dmairq = card->send.dmastart +
		(4 * ((NJ_DMA_TXSIZE / 2) - 1));
	card->send.size = NJ_DMA_TXSIZE;

	if (debug & DEBUG_HW)
		pr_notice("%s: send buffer phy %#x - %#x - %#x  virt %p"
			" size %zu u32\n", card->name,
			card->send.dmastart, card->send.dmairq,
			card->send.dmaend, card->send.start, card->send.size);

	outl(card->send.dmastart, card->base + NJ_DMA_READ_START);
	outl(card->send.dmairq, card->base + NJ_DMA_READ_IRQ);
	outl(card->send.dmaend, card->base + NJ_DMA_READ_END);

	card->recv.start = card->dma_p + (NJ_DMA_SIZE / 2);
	card->recv.dmastart = (u32)card->dma  + (NJ_DMA_SIZE / 2);
	card->recv.dmaend = card->recv.dmastart +
		(4 * (NJ_DMA_RXSIZE - 1));
	card->recv.dmairq = card->recv.dmastart +
		(4 * ((NJ_DMA_RXSIZE / 2) - 1));
	card->recv.size = NJ_DMA_RXSIZE;

	if (debug & DEBUG_HW)
		pr_notice("%s: recv buffer phy %#x - %#x - %#x  virt %p"
			" size %zu u32\n", card->name,
			card->recv.dmastart, card->recv.dmairq,
			card->recv.dmaend, card->recv.start, card->recv.size);

	outl(card->recv.dmastart, card->base + NJ_DMA_WRITE_START);
	outl(card->recv.dmairq, card->base + NJ_DMA_WRITE_IRQ);
	outl(card->recv.dmaend, card->base + NJ_DMA_WRITE_END);
	return 0;
}