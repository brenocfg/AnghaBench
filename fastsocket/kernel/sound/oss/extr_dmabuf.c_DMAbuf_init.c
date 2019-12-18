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
struct audio_operations {int parent_dev; int flags; TYPE_1__* dmap_out; TYPE_1__* dmap_in; TYPE_1__* dmaps; int /*<<< orphan*/ * d; } ;
struct TYPE_2__ {int dma; int /*<<< orphan*/ * raw_buf; } ;

/* Variables and functions */
 scalar_t__ DMAP_KEEP_ON_CLOSE ; 
 int DMA_DUPLEX ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  sound_alloc_dmap (TYPE_1__*) ; 
 scalar_t__ sound_dmap_flag ; 

void DMAbuf_init(int dev, int dma1, int dma2)
{
	struct audio_operations *adev = audio_devs[dev];
	/*
	 * NOTE! This routine could be called several times.
	 */

	if (adev && adev->dmap_out == NULL) {
		if (adev->d == NULL)
			panic("OSS: audio_devs[%d]->d == NULL\n", dev);

		if (adev->parent_dev) {	 /* Use DMA map of the parent dev */
			int parent = adev->parent_dev - 1;
			adev->dmap_out = audio_devs[parent]->dmap_out;
			adev->dmap_in = audio_devs[parent]->dmap_in;
		} else {
			adev->dmap_out = adev->dmap_in = &adev->dmaps[0];
			adev->dmap_out->dma = dma1;
			if (adev->flags & DMA_DUPLEX) {
				adev->dmap_in = &adev->dmaps[1];
				adev->dmap_in->dma = dma2;
			}
		}
		/* Persistent DMA buffers allocated here */
		if (sound_dmap_flag == DMAP_KEEP_ON_CLOSE) {
			if (adev->dmap_in->raw_buf == NULL)
				sound_alloc_dmap(adev->dmap_in);
			if (adev->dmap_out->raw_buf == NULL)
				sound_alloc_dmap(adev->dmap_out);
		}
	}
}