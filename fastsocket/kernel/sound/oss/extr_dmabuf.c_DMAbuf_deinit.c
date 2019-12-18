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
struct audio_operations {int flags; int /*<<< orphan*/  dmap_in; int /*<<< orphan*/  dmap_out; } ;

/* Variables and functions */
 scalar_t__ DMAP_KEEP_ON_CLOSE ; 
 int DMA_DUPLEX ; 
 struct audio_operations** audio_devs ; 
 scalar_t__ sound_dmap_flag ; 
 int /*<<< orphan*/  sound_free_dmap (int /*<<< orphan*/ ) ; 

void DMAbuf_deinit(int dev)
{
	struct audio_operations *adev = audio_devs[dev];
	/* This routine is called when driver is being unloaded */
	if (!adev)
		return;

	/* Persistent DMA buffers deallocated here */
	if (sound_dmap_flag == DMAP_KEEP_ON_CLOSE) {
		sound_free_dmap(adev->dmap_out);
		if (adev->flags & DMA_DUPLEX)
			sound_free_dmap(adev->dmap_in);
	}
}