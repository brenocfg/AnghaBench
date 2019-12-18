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
struct dma_buffparms {int flags; unsigned long user_counter; unsigned long fragment_size; int cfrag; long byte_counter; long max_byte_counter; int bytes_in_use; unsigned long* counts; size_t qtail; int nbufs; int qlen; int /*<<< orphan*/  lock; int /*<<< orphan*/ * raw_buf; int /*<<< orphan*/  neutral_byte; } ;
struct audio_operations {TYPE_1__* d; struct dma_buffparms* dmap_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* postprocess_write ) (int) ;} ;

/* Variables and functions */
 int DMA_ACTIVE ; 
 int DMA_DIRTY ; 
 int DMA_POST ; 
 int /*<<< orphan*/  DMAbuf_launch_output (int,struct dma_buffparms*) ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int) ; 

int DMAbuf_move_wrpointer(int dev, int l)
{
	struct audio_operations *adev = audio_devs[dev];
	struct dma_buffparms *dmap = adev->dmap_out;
	unsigned long ptr;
	unsigned long end_ptr, p;
	int post;
	unsigned long flags;

	spin_lock_irqsave(&dmap->lock,flags);
	post= (dmap->flags & DMA_POST);
	ptr = (dmap->user_counter / dmap->fragment_size) * dmap->fragment_size;

	dmap->flags &= ~DMA_POST;
	dmap->cfrag = -1;
	dmap->user_counter += l;
	dmap->flags |= DMA_DIRTY;

	if (dmap->byte_counter >= dmap->max_byte_counter) {
		/* Wrap the byte counters */
		long decr = dmap->byte_counter;
		dmap->byte_counter = (dmap->byte_counter % dmap->bytes_in_use);
		decr -= dmap->byte_counter;
		dmap->user_counter -= decr;
	}
	end_ptr = (dmap->user_counter / dmap->fragment_size) * dmap->fragment_size;

	p = (dmap->user_counter - 1) % dmap->bytes_in_use;
	dmap->neutral_byte = dmap->raw_buf[p];

	/* Update the fragment based bookkeeping too */
	while (ptr < end_ptr) {
		dmap->counts[dmap->qtail] = dmap->fragment_size;
		dmap->qtail = (dmap->qtail + 1) % dmap->nbufs;
		dmap->qlen++;
		ptr += dmap->fragment_size;
	}

	dmap->counts[dmap->qtail] = dmap->user_counter - ptr;

	/*
	 *	Let the low level driver perform some postprocessing to
	 *	the written data.
	 */
	if (adev->d->postprocess_write)
		adev->d->postprocess_write(dev);

	if (!(dmap->flags & DMA_ACTIVE))
		if (dmap->qlen > 1 || (dmap->qlen > 0 && (post || dmap->qlen >= dmap->nbufs - 1)))
			DMAbuf_launch_output(dev, dmap);

	spin_unlock_irqrestore(&dmap->lock,flags);
	return 0;
}