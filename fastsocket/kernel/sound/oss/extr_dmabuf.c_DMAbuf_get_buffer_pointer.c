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
struct dma_buffparms {int flags; int dma; int bytes_in_use; int mapping_flags; scalar_t__ qhead; int fragment_size; scalar_t__ qtail; } ;

/* Variables and functions */
 int DMA_ACTIVE ; 
 int DMA_MAP_MAPPED ; 
 int DMODE_OUTPUT ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int) ; 
 int /*<<< orphan*/  disable_dma (int) ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int get_dma_residue (int) ; 
 int /*<<< orphan*/  isa_dma_bridge_buggy ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 

int DMAbuf_get_buffer_pointer(int dev, struct dma_buffparms *dmap, int direction)
{
	/*
	 *	Try to approximate the active byte position of the DMA pointer within the
	 *	buffer area as well as possible.
	 */

	int pos;
	unsigned long f;

	if (!(dmap->flags & DMA_ACTIVE))
		pos = 0;
	else {
		int chan = dmap->dma;
		
		f=claim_dma_lock();
		clear_dma_ff(chan);
		
		if(!isa_dma_bridge_buggy)
			disable_dma(dmap->dma);
		
		pos = get_dma_residue(chan);
		
		pos = dmap->bytes_in_use - pos;

		if (!(dmap->mapping_flags & DMA_MAP_MAPPED)) {
			if (direction == DMODE_OUTPUT) {
				if (dmap->qhead == 0)
					if (pos > dmap->fragment_size)
						pos = 0;
			} else {
				if (dmap->qtail == 0)
					if (pos > dmap->fragment_size)
						pos = 0;
			}
		}
		if (pos < 0)
			pos = 0;
		if (pos >= dmap->bytes_in_use)
			pos = 0;
		
		if(!isa_dma_bridge_buggy)
			enable_dma(dmap->dma);
			
		release_dma_lock(f);
	}
	/* printk( "%04x ",  pos); */

	return pos;
}