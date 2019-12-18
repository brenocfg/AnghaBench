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
struct dma_buffparms {int subdivision; int fragment_size; int max_fragments; int buffsize; } ;
struct TYPE_2__ {int min_fragment; int max_fragment; int flags; } ;

/* Variables and functions */
 int DMA_AUTOMODE ; 
 int EINVAL ; 
 int EIO ; 
 int MAX_SUB_BUFFERS ; 
 int OS_DMA_MINBITS ; 
 TYPE_1__** audio_devs ; 

__attribute__((used)) static int dma_set_fragment(int dev, struct dma_buffparms *dmap, int fact)
{
	int bytes, count;

	if (fact == 0)
		return -EIO;

	if (dmap->subdivision != 0 ||
	    dmap->fragment_size)	/* Too late to change */
		return -EINVAL;

	bytes = fact & 0xffff;
	count = (fact >> 16) & 0x7fff;

	if (count == 0)
		count = MAX_SUB_BUFFERS;
	else if (count < MAX_SUB_BUFFERS)
		count++;

	if (bytes < 4 || bytes > 17)	/* <16 || > 512k */
		return -EINVAL;

	if (count < 2)
		return -EINVAL;

	if (audio_devs[dev]->min_fragment > 0)
		if (bytes < audio_devs[dev]->min_fragment)
			bytes = audio_devs[dev]->min_fragment;

	if (audio_devs[dev]->max_fragment > 0)
		if (bytes > audio_devs[dev]->max_fragment)
			bytes = audio_devs[dev]->max_fragment;

#ifdef OS_DMA_MINBITS
	if (bytes < OS_DMA_MINBITS)
		bytes = OS_DMA_MINBITS;
#endif

	dmap->fragment_size = (1 << bytes);
	dmap->max_fragments = count;

	if (dmap->fragment_size > dmap->buffsize)
		dmap->fragment_size = dmap->buffsize;

	if (dmap->fragment_size == dmap->buffsize &&
	    audio_devs[dev]->flags & DMA_AUTOMODE)
		dmap->fragment_size /= 2;	/* Needs at least 2 buffers */

	dmap->subdivision = 1;	/* Disable SNDCTL_DSP_SUBDIVIDE */
	return bytes | ((count - 1) << 16);
}