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
struct dma_buffparms {int flags; int dma; int bytes_in_use; int fragment_size; int nbufs; int qhead; int /*<<< orphan*/  lock; } ;
struct audio_operations {struct dma_buffparms* dmap_out; } ;

/* Variables and functions */
 int DMA_NODMA ; 
 struct audio_operations** audio_devs ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int) ; 
 int /*<<< orphan*/  disable_dma (int) ; 
 int /*<<< orphan*/  do_outputintr (int,int) ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int get_dma_residue (int) ; 
 int /*<<< orphan*/  isa_dma_bridge_buggy ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void DMAbuf_outputintr(int dev, int notify_only)
{
	struct audio_operations *adev = audio_devs[dev];
	unsigned long flags;
	struct dma_buffparms *dmap = adev->dmap_out;

	spin_lock_irqsave(&dmap->lock,flags);
	if (!(dmap->flags & DMA_NODMA)) {
		int chan = dmap->dma, pos, n;
		unsigned long f;
		
		f=claim_dma_lock();
		
		if(!isa_dma_bridge_buggy)
			disable_dma(dmap->dma);
		clear_dma_ff(chan);
		pos = dmap->bytes_in_use - get_dma_residue(chan);
		if(!isa_dma_bridge_buggy)
			enable_dma(dmap->dma);
		release_dma_lock(f);
		
		pos = pos / dmap->fragment_size;	/* Actual qhead */
		if (pos < 0 || pos >= dmap->nbufs)
			pos = 0;
		n = 0;
		while (dmap->qhead != pos && n++ < dmap->nbufs)
			do_outputintr(dev, notify_only);
	}
	else
		do_outputintr(dev, notify_only);
	spin_unlock_irqrestore(&dmap->lock,flags);
}