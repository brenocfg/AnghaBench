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
struct dma_buffparms {scalar_t__ dma; int flags; int /*<<< orphan*/  dma_mode; } ;
struct audio_operations {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMAP_FREE_ON_CLOSE ; 
 int DMA_BUSY ; 
 int /*<<< orphan*/  DMODE_NONE ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  sound_close_dma (scalar_t__) ; 
 scalar_t__ sound_dmap_flag ; 
 int /*<<< orphan*/  sound_free_dmap (struct dma_buffparms*) ; 

__attribute__((used)) static void close_dmap(struct audio_operations *adev, struct dma_buffparms *dmap)
{
	unsigned long flags;
	
	if (dmap->dma >= 0) {
		sound_close_dma(dmap->dma);
		flags=claim_dma_lock();
		disable_dma(dmap->dma);
		release_dma_lock(flags);
	}
	if (dmap->flags & DMA_BUSY)
		dmap->dma_mode = DMODE_NONE;
	dmap->flags &= ~DMA_BUSY;
	
	if (sound_dmap_flag == DMAP_FREE_ON_CLOSE)
		sound_free_dmap(dmap);
}