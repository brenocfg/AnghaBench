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
struct dma_buffparms {int flags; scalar_t__ underrun_count; int /*<<< orphan*/  lock; scalar_t__ user_counter; scalar_t__ qtail; scalar_t__ qhead; scalar_t__ qlen; scalar_t__ byte_counter; int /*<<< orphan*/  dma; } ;
struct audio_operations {int flags; struct dma_buffparms* dmap_out; TYPE_1__* d; int /*<<< orphan*/  out_sleeper; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* halt_output ) (int) ;int /*<<< orphan*/  (* halt_io ) (int) ;} ;

/* Variables and functions */
 int DMA_ACTIVE ; 
 int DMA_DUPLEX ; 
 int DMA_STARTED ; 
 int DMA_SYNCING ; 
 struct audio_operations** audio_devs ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmabuf_timeout (struct dma_buffparms*) ; 
 int /*<<< orphan*/  interruptible_sleep_on_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  reorganize_buffers (int,struct dma_buffparms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static void dma_reset_output(int dev)
{
	struct audio_operations *adev = audio_devs[dev];
	unsigned long flags,f ;
	struct dma_buffparms *dmap = adev->dmap_out;

	if (!(dmap->flags & DMA_STARTED))	/* DMA is not active */
		return;

	/*
	 *	First wait until the current fragment has been played completely
	 */
	spin_lock_irqsave(&dmap->lock,flags);
	adev->dmap_out->flags |= DMA_SYNCING;

	adev->dmap_out->underrun_count = 0;
	if (!signal_pending(current) && adev->dmap_out->qlen && 
	    adev->dmap_out->underrun_count == 0){
		spin_unlock_irqrestore(&dmap->lock,flags);
		interruptible_sleep_on_timeout(&adev->out_sleeper,
					       dmabuf_timeout(dmap));
		spin_lock_irqsave(&dmap->lock,flags);
	}
	adev->dmap_out->flags &= ~(DMA_SYNCING | DMA_ACTIVE);

	/*
	 *	Finally shut the device off
	 */
	if (!(adev->flags & DMA_DUPLEX) || !adev->d->halt_output)
		adev->d->halt_io(dev);
	else
		adev->d->halt_output(dev);
	adev->dmap_out->flags &= ~DMA_STARTED;
	
	f=claim_dma_lock();
	clear_dma_ff(dmap->dma);
	disable_dma(dmap->dma);
	release_dma_lock(f);
	
	dmap->byte_counter = 0;
	reorganize_buffers(dev, adev->dmap_out, 0);
	dmap->qlen = dmap->qhead = dmap->qtail = dmap->user_counter = 0;
	spin_unlock_irqrestore(&dmap->lock,flags);
}