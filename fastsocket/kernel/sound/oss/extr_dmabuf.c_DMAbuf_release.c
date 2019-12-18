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
struct dma_buffparms {int closing; int mapping_flags; scalar_t__ dma_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  bytes_in_use; int /*<<< orphan*/  neutral_byte; int /*<<< orphan*/  raw_buf; } ;
struct audio_operations {int open_mode; int flags; struct dma_buffparms* dmap_in; struct dma_buffparms* dmap_out; TYPE_1__* d; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (int) ;} ;

/* Variables and functions */
 int DMA_DUPLEX ; 
 int DMA_MAP_MAPPED ; 
 int /*<<< orphan*/  DMAbuf_reset (int) ; 
 int /*<<< orphan*/  DMAbuf_sync (int) ; 
 scalar_t__ DMODE_OUTPUT ; 
 int OPEN_READ ; 
 int OPEN_WRITE ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  close_dmap (struct audio_operations*,struct dma_buffparms*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int) ; 

int DMAbuf_release(int dev, int mode)
{
	struct audio_operations *adev = audio_devs[dev];
	struct dma_buffparms *dmap;
	unsigned long flags;

	dmap = adev->dmap_out;
	if (adev->open_mode & OPEN_WRITE)
		adev->dmap_out->closing = 1;

	if (adev->open_mode & OPEN_READ){
		adev->dmap_in->closing = 1;
		dmap = adev->dmap_in;
	}
	if (adev->open_mode & OPEN_WRITE)
		if (!(adev->dmap_out->mapping_flags & DMA_MAP_MAPPED))
			if (!signal_pending(current) && (adev->dmap_out->dma_mode == DMODE_OUTPUT))
				DMAbuf_sync(dev);
	if (adev->dmap_out->dma_mode == DMODE_OUTPUT)
		memset(adev->dmap_out->raw_buf, adev->dmap_out->neutral_byte, adev->dmap_out->bytes_in_use);

	DMAbuf_reset(dev);
	spin_lock_irqsave(&dmap->lock,flags);
	adev->d->close(dev);

	if (adev->open_mode & OPEN_WRITE)
		close_dmap(adev, adev->dmap_out);

	if (adev->open_mode == OPEN_READ ||
	    (adev->open_mode != OPEN_WRITE &&
	     (adev->flags & DMA_DUPLEX)))
		close_dmap(adev, adev->dmap_in);
	adev->open_mode = 0;
	spin_unlock_irqrestore(&dmap->lock,flags);
	return 0;
}