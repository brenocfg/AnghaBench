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
struct dmatest_thread {int type; int /*<<< orphan*/  node; int /*<<< orphan*/  task; struct dma_chan* chan; } ;
struct dmatest_chan {int /*<<< orphan*/  threads; struct dma_chan* chan; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transaction_type { ____Placeholder_dma_transaction_type } dma_transaction_type ;

/* Variables and functions */
 int DMA_MEMCPY ; 
 int DMA_PQ ; 
 int DMA_XOR ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_name (struct dma_chan*) ; 
 int /*<<< orphan*/  dmatest_func ; 
 int /*<<< orphan*/  kfree (struct dmatest_thread*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct dmatest_thread*,char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct dmatest_thread* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 unsigned int threads_per_chan ; 

__attribute__((used)) static int dmatest_add_threads(struct dmatest_chan *dtc, enum dma_transaction_type type)
{
	struct dmatest_thread *thread;
	struct dma_chan *chan = dtc->chan;
	char *op;
	unsigned int i;

	if (type == DMA_MEMCPY)
		op = "copy";
	else if (type == DMA_XOR)
		op = "xor";
	else if (type == DMA_PQ)
		op = "pq";
	else
		return -EINVAL;

	for (i = 0; i < threads_per_chan; i++) {
		thread = kzalloc(sizeof(struct dmatest_thread), GFP_KERNEL);
		if (!thread) {
			pr_warning("dmatest: No memory for %s-%s%u\n",
				   dma_chan_name(chan), op, i);

			break;
		}
		thread->chan = dtc->chan;
		thread->type = type;
		smp_wmb();
		thread->task = kthread_run(dmatest_func, thread, "%s-%s%u",
				dma_chan_name(chan), op, i);
		if (IS_ERR(thread->task)) {
			pr_warning("dmatest: Failed to run thread %s-%s%u\n",
					dma_chan_name(chan), op, i);
			kfree(thread);
			break;
		}

		/* srcbuf and dstbuf are allocated by the thread itself */

		list_add_tail(&thread->node, &dtc->threads);
	}

	return i;
}