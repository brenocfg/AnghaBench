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
struct dmatest_chan {int /*<<< orphan*/  node; int /*<<< orphan*/  threads; struct dma_chan* chan; } ;
struct dma_device {int /*<<< orphan*/  cap_mask; } ;
struct dma_chan {struct dma_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_PQ ; 
 int /*<<< orphan*/  DMA_XOR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_chan_name (struct dma_chan*) ; 
 scalar_t__ dma_has_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int dmatest_add_threads (struct dmatest_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmatest_channels ; 
 struct dmatest_chan* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_channels ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmatest_add_channel(struct dma_chan *chan)
{
	struct dmatest_chan	*dtc;
	struct dma_device	*dma_dev = chan->device;
	unsigned int		thread_count = 0;
	unsigned int		cnt;

	dtc = kmalloc(sizeof(struct dmatest_chan), GFP_KERNEL);
	if (!dtc) {
		pr_warning("dmatest: No memory for %s\n", dma_chan_name(chan));
		return -ENOMEM;
	}

	dtc->chan = chan;
	INIT_LIST_HEAD(&dtc->threads);

	if (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask)) {
		cnt = dmatest_add_threads(dtc, DMA_MEMCPY);
		thread_count += cnt > 0 ? cnt : 0;
	}
	if (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) {
		cnt = dmatest_add_threads(dtc, DMA_XOR);
		thread_count += cnt > 0 ? cnt : 0;
	}
	if (dma_has_cap(DMA_PQ, dma_dev->cap_mask)) {
		cnt = dmatest_add_threads(dtc, DMA_PQ);
		thread_count += cnt > 0 ?: 0;
	}

	pr_info("dmatest: Started %u threads using %s\n",
		thread_count, dma_chan_name(chan));

	list_add_tail(&dtc->node, &dmatest_channels);
	nr_channels++;

	return 0;
}