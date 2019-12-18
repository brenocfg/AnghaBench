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
struct dma_buffparms {int* counts; size_t qhead; int mapping_flags; scalar_t__ qlen; int fragment_size; int nbufs; } ;
struct audio_operations {struct dma_buffparms* dmap_in; } ;

/* Variables and functions */
 int DMA_MAP_MAPPED ; 
 int EINVAL ; 
 int EIO ; 
 struct audio_operations** audio_devs ; 

int DMAbuf_rmchars(int dev, int buff_no, int c)
{
	struct audio_operations *adev = audio_devs[dev];
	struct dma_buffparms *dmap = adev->dmap_in;
	int p = dmap->counts[dmap->qhead] + c;

	if (dmap->mapping_flags & DMA_MAP_MAPPED)
	{
/*		  printk("Sound: Can't read from mmapped device (2)\n");*/
		return -EINVAL;
	}
	else if (dmap->qlen <= 0)
		return -EIO;
	else if (p >= dmap->fragment_size) {  /* This buffer is completely empty */
		dmap->counts[dmap->qhead] = 0;
		dmap->qlen--;
		dmap->qhead = (dmap->qhead + 1) % dmap->nbufs;
	}
	else dmap->counts[dmap->qhead] = p;

	return 0;
}