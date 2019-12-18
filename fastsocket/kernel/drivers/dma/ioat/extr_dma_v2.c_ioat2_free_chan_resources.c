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
typedef  int u16 ;
struct ioatdma_device {int /*<<< orphan*/  completion_pool; int /*<<< orphan*/  (* reset_hw ) (struct ioat_chan_common*) ;int /*<<< orphan*/  (* cleanup_tasklet ) (unsigned long) ;} ;
struct ioat_ring_ent {int dummy; } ;
struct ioat_chan_common {scalar_t__ completion_dma; scalar_t__ last_completion; int /*<<< orphan*/  completion; int /*<<< orphan*/  state; int /*<<< orphan*/  timer; int /*<<< orphan*/  cleanup_task; struct ioatdma_device* device; } ;
struct ioat2_dma_chan {int alloc_order; scalar_t__ dmacount; int /*<<< orphan*/  ring_lock; int /*<<< orphan*/ * ring; scalar_t__ tail; scalar_t__ head; struct ioat_chan_common base; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_RUN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  dump_desc_dbg (struct ioat2_dma_chan*,struct ioat_ring_ent*) ; 
 int /*<<< orphan*/  ioat2_free_ring_ent (struct ioat_ring_ent*,struct dma_chan*) ; 
 struct ioat_ring_ent* ioat2_get_ring_ent (struct ioat2_dma_chan*,scalar_t__) ; 
 int ioat2_ring_space (struct ioat2_dma_chan*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct ioat_chan_common*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_dev (struct ioat_chan_common*) ; 
 struct ioat2_dma_chan* to_ioat2_chan (struct dma_chan*) ; 

void ioat2_free_chan_resources(struct dma_chan *c)
{
	struct ioat2_dma_chan *ioat = to_ioat2_chan(c);
	struct ioat_chan_common *chan = &ioat->base;
	struct ioatdma_device *device = chan->device;
	struct ioat_ring_ent *desc;
	const u16 total_descs = 1 << ioat->alloc_order;
	int descs;
	int i;

	/* Before freeing channel resources first check
	 * if they have been previously allocated for this channel.
	 */
	if (!ioat->ring)
		return;

	tasklet_disable(&chan->cleanup_task);
	del_timer_sync(&chan->timer);
	device->cleanup_tasklet((unsigned long) ioat);
	device->reset_hw(chan);
	clear_bit(IOAT_RUN, &chan->state);

	spin_lock_bh(&ioat->ring_lock);
	descs = ioat2_ring_space(ioat);
	dev_dbg(to_dev(chan), "freeing %d idle descriptors\n", descs);
	for (i = 0; i < descs; i++) {
		desc = ioat2_get_ring_ent(ioat, ioat->head + i);
		ioat2_free_ring_ent(desc, c);
	}

	if (descs < total_descs)
		dev_err(to_dev(chan), "Freeing %d in use descriptors!\n",
			total_descs - descs);

	for (i = 0; i < total_descs - descs; i++) {
		desc = ioat2_get_ring_ent(ioat, ioat->tail + i);
		dump_desc_dbg(ioat, desc);
		ioat2_free_ring_ent(desc, c);
	}

	kfree(ioat->ring);
	ioat->ring = NULL;
	ioat->alloc_order = 0;
	pci_pool_free(device->completion_pool, chan->completion,
		      chan->completion_dma);
	spin_unlock_bh(&ioat->ring_lock);

	chan->last_completion = 0;
	chan->completion_dma = 0;
	ioat->dmacount = 0;
}