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
struct dma_buffparms {scalar_t__ dma_mode; int fragment_size; int flags; int qtail; scalar_t__ raw_buf_phys; int /*<<< orphan*/  bytes_in_use; scalar_t__ needs_reorg; int /*<<< orphan*/  nbufs; int /*<<< orphan*/  lock; } ;
struct audio_operations {int open_mode; int enable_bits; int go; TYPE_1__* d; } ;
struct TYPE_2__ {int (* prepare_for_input ) (int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* trigger ) (int,int) ;int /*<<< orphan*/  (* start_input ) (int,scalar_t__,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DMA_ACTIVE ; 
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  DMAbuf_reset (int) ; 
 int /*<<< orphan*/  DMAbuf_sync (int) ; 
 scalar_t__ DMODE_INPUT ; 
 scalar_t__ DMODE_NONE ; 
 scalar_t__ DMODE_OUTPUT ; 
 int OPEN_READ ; 
 int PCM_ENABLE_INPUT ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  local_start_dma (struct audio_operations*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reorganize_buffers (int,struct dma_buffparms*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int) ; 

int DMAbuf_activate_recording(int dev, struct dma_buffparms *dmap)
{
	struct audio_operations *adev = audio_devs[dev];
	int  err;

	if (!(adev->open_mode & OPEN_READ))
		return 0;
	if (!(adev->enable_bits & PCM_ENABLE_INPUT))
		return 0;
	if (dmap->dma_mode == DMODE_OUTPUT) {	/* Direction change */
		/* release lock - it's not recursive */
		spin_unlock_irq(&dmap->lock);
		DMAbuf_sync(dev);
		DMAbuf_reset(dev);
		spin_lock_irq(&dmap->lock);
		dmap->dma_mode = DMODE_NONE;
	}
	if (!dmap->dma_mode) {
		reorganize_buffers(dev, dmap, 1);
		if ((err = adev->d->prepare_for_input(dev,
				dmap->fragment_size, dmap->nbufs)) < 0)
			return err;
		dmap->dma_mode = DMODE_INPUT;
	}
	if (!(dmap->flags & DMA_ACTIVE)) {
		if (dmap->needs_reorg)
			reorganize_buffers(dev, dmap, 0);
		local_start_dma(adev, dmap->raw_buf_phys, dmap->bytes_in_use, DMA_MODE_READ);
		adev->d->start_input(dev, dmap->raw_buf_phys + dmap->qtail * dmap->fragment_size,
				     dmap->fragment_size, 0);
		dmap->flags |= DMA_ACTIVE;
		if (adev->d->trigger)
			adev->d->trigger(dev, adev->enable_bits * adev->go);
	}
	return 0;
}