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
struct dma_buffparms {unsigned int data_rate; unsigned int fragment_size; unsigned int buffsize; int subdivision; unsigned int max_fragments; unsigned int nbufs; unsigned int bytes_in_use; int max_byte_counter; int flags; scalar_t__* counts; int /*<<< orphan*/  neutral_byte; scalar_t__ raw_buf; scalar_t__ needs_reorg; } ;
struct audio_operations {int min_fragment; int max_fragment; TYPE_1__* d; } ;
struct TYPE_2__ {unsigned int (* set_speed ) (int,int /*<<< orphan*/ ) ;unsigned int (* set_channels ) (int,int /*<<< orphan*/ ) ;unsigned int (* set_bits ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DMA_ALLOC_DONE ; 
 int DMA_EMPTY ; 
 unsigned int DSP_DEFAULT_SPEED ; 
 unsigned int MAX_SUB_BUFFERS ; 
 int /*<<< orphan*/  NEUTRAL16 ; 
 int /*<<< orphan*/  NEUTRAL8 ; 
 int /*<<< orphan*/  OS_DMA_ALIGN_CHECK (unsigned int) ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 unsigned int stub1 (int,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (int,int /*<<< orphan*/ ) ; 
 unsigned int stub3 (int,int /*<<< orphan*/ ) ; 

void reorganize_buffers(int dev, struct dma_buffparms *dmap, int recording)
{
	/*
	 * This routine breaks the physical device buffers to logical ones.
	 */

	struct audio_operations *dsp_dev = audio_devs[dev];

	unsigned i, n;
	unsigned sr, nc, sz, bsz;

	sr = dsp_dev->d->set_speed(dev, 0);
	nc = dsp_dev->d->set_channels(dev, 0);
	sz = dsp_dev->d->set_bits(dev, 0);

	if (sz == 8)
		dmap->neutral_byte = NEUTRAL8;
	else
		dmap->neutral_byte = NEUTRAL16;

	if (sr < 1 || nc < 1 || sz < 1)
	{
/*		printk(KERN_DEBUG "Warning: Invalid PCM parameters[%d] sr=%d, nc=%d, sz=%d\n", dev, sr, nc, sz);*/
		sr = DSP_DEFAULT_SPEED;
		nc = 1;
		sz = 8;
	}
	
	sz = sr * nc * sz;

	sz /= 8;		/* #bits -> #bytes */
	dmap->data_rate = sz;

	if (!dmap->needs_reorg)
		return;
	dmap->needs_reorg = 0;

	if (dmap->fragment_size == 0)
	{	
		/* Compute the fragment size using the default algorithm */

		/*
		 * Compute a buffer size for time not exceeding 1 second.
		 * Usually this algorithm gives a buffer size for 0.5 to 1.0 seconds
		 * of sound (using the current speed, sample size and #channels).
		 */

		bsz = dmap->buffsize;
		while (bsz > sz)
			bsz /= 2;

		if (bsz == dmap->buffsize)
			bsz /= 2;	/* Needs at least 2 buffers */

		/*
		 *    Split the computed fragment to smaller parts. After 3.5a9
		 *      the default subdivision is 4 which should give better
		 *      results when recording.
		 */

		if (dmap->subdivision == 0)	/* Not already set */
		{
			dmap->subdivision = 4;	/* Init to the default value */

			if ((bsz / dmap->subdivision) > 4096)
				dmap->subdivision *= 2;
			if ((bsz / dmap->subdivision) < 4096)
				dmap->subdivision = 1;
		}
		bsz /= dmap->subdivision;

		if (bsz < 16)
			bsz = 16;	/* Just a sanity check */

		dmap->fragment_size = bsz;
	}
	else
	{
		/*
		 * The process has specified the buffer size with SNDCTL_DSP_SETFRAGMENT or
		 * the buffer size computation has already been done.
		 */
		if (dmap->fragment_size > (dmap->buffsize / 2))
			dmap->fragment_size = (dmap->buffsize / 2);
		bsz = dmap->fragment_size;
	}

	if (audio_devs[dev]->min_fragment)
		if (bsz < (1 << audio_devs[dev]->min_fragment))
			bsz = 1 << audio_devs[dev]->min_fragment;
	if (audio_devs[dev]->max_fragment)
		if (bsz > (1 << audio_devs[dev]->max_fragment))
			bsz = 1 << audio_devs[dev]->max_fragment;
	bsz &= ~0x07;		/* Force size which is multiple of 8 bytes */
#ifdef OS_DMA_ALIGN_CHECK
	OS_DMA_ALIGN_CHECK(bsz);
#endif

	n = dmap->buffsize / bsz;
	if (n > MAX_SUB_BUFFERS)
		n = MAX_SUB_BUFFERS;
	if (n > dmap->max_fragments)
		n = dmap->max_fragments;

	if (n < 2)
	{
		n = 2;
		bsz /= 2;
	}
	dmap->nbufs = n;
	dmap->bytes_in_use = n * bsz;
	dmap->fragment_size = bsz;
	dmap->max_byte_counter = (dmap->data_rate * 60 * 60) +
			dmap->bytes_in_use;	/* Approximately one hour */

	if (dmap->raw_buf)
	{
		memset(dmap->raw_buf, dmap->neutral_byte, dmap->bytes_in_use);
	}
	
	for (i = 0; i < dmap->nbufs; i++)
	{
		dmap->counts[i] = 0;
	}

	dmap->flags |= DMA_ALLOC_DONE | DMA_EMPTY;
}