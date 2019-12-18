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
struct dma_buffparms {int /*<<< orphan*/  lock; scalar_t__ byte_counter; scalar_t__ user_counter; scalar_t__ qtail; scalar_t__ qhead; scalar_t__ qlen; int /*<<< orphan*/  flags; } ;
struct audio_operations {int flags; struct dma_buffparms* dmap_in; TYPE_1__* d; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* halt_input ) (int) ;int /*<<< orphan*/  (* halt_io ) (int) ;} ;

/* Variables and functions */
 int DMA_DUPLEX ; 
 int /*<<< orphan*/  DMA_STARTED ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  reorganize_buffers (int,struct dma_buffparms*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static void dma_reset_input(int dev)
{
        struct audio_operations *adev = audio_devs[dev];
	unsigned long flags;
	struct dma_buffparms *dmap = adev->dmap_in;

	spin_lock_irqsave(&dmap->lock,flags);
	if (!(adev->flags & DMA_DUPLEX) || !adev->d->halt_input)
		adev->d->halt_io(dev);
	else
		adev->d->halt_input(dev);
	adev->dmap_in->flags &= ~DMA_STARTED;

	dmap->qlen = dmap->qhead = dmap->qtail = dmap->user_counter = 0;
	dmap->byte_counter = 0;
	reorganize_buffers(dev, adev->dmap_in, 1);
	spin_unlock_irqrestore(&dmap->lock,flags);
}