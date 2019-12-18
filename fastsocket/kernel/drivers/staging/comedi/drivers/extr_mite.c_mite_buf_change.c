#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mite_dma_descriptor_ring {int n_links; int /*<<< orphan*/  descriptors_dma_addr; TYPE_2__* descriptors; int /*<<< orphan*/  hw_dev; } ;
struct mite_dma_descriptor {int dummy; } ;
struct comedi_async {unsigned int prealloc_bufsz; TYPE_1__* buf_page_list; } ;
struct TYPE_5__ {void* next; void* addr; void* count; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MDPRINTK (char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* dma_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

int mite_buf_change(struct mite_dma_descriptor_ring *ring,
		    struct comedi_async *async)
{
	unsigned int n_links;
	int i;

	if (ring->descriptors) {
		dma_free_coherent(ring->hw_dev,
				  ring->n_links *
				  sizeof(struct mite_dma_descriptor),
				  ring->descriptors,
				  ring->descriptors_dma_addr);
	}
	ring->descriptors = NULL;
	ring->descriptors_dma_addr = 0;
	ring->n_links = 0;

	if (async->prealloc_bufsz == 0)
		return 0;

	n_links = async->prealloc_bufsz >> PAGE_SHIFT;

	MDPRINTK("ring->hw_dev=%p, n_links=0x%04x\n", ring->hw_dev, n_links);

	ring->descriptors =
	    dma_alloc_coherent(ring->hw_dev,
			       n_links * sizeof(struct mite_dma_descriptor),
			       &ring->descriptors_dma_addr, GFP_KERNEL);
	if (!ring->descriptors) {
		printk("mite: ring buffer allocation failed\n");
		return -ENOMEM;
	}
	ring->n_links = n_links;

	for (i = 0; i < n_links; i++) {
		ring->descriptors[i].count = cpu_to_le32(PAGE_SIZE);
		ring->descriptors[i].addr =
		    cpu_to_le32(async->buf_page_list[i].dma_addr);
		ring->descriptors[i].next =
		    cpu_to_le32(ring->descriptors_dma_addr + (i +
							      1) *
				sizeof(struct mite_dma_descriptor));
	}
	ring->descriptors[n_links - 1].next =
	    cpu_to_le32(ring->descriptors_dma_addr);
	/* barrier is meant to insure that all the writes to the dma descriptors
	   have completed before the dma controller is commanded to read them */
	smp_wmb();
	return 0;
}