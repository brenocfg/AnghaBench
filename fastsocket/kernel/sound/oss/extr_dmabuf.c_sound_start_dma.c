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
struct dma_buffparms {int dma; } ;

/* Variables and functions */
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int) ; 
 int /*<<< orphan*/  disable_dma (int) ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int,unsigned long) ; 
 int /*<<< orphan*/  set_dma_count (int,int) ; 
 int /*<<< orphan*/  set_dma_mode (int,int) ; 

__attribute__((used)) static int sound_start_dma(struct dma_buffparms *dmap, unsigned long physaddr, int count, int dma_mode)
{
	unsigned long flags;
	int chan = dmap->dma;

	/* printk( "Start DMA%d %d, %d\n",  chan,  (int)(physaddr-dmap->raw_buf_phys),  count); */

	flags = claim_dma_lock();
	disable_dma(chan);
	clear_dma_ff(chan);
	set_dma_mode(chan, dma_mode);
	set_dma_addr(chan, physaddr);
	set_dma_count(chan, count);
	enable_dma(chan);
	release_dma_lock(flags);

	return 0;
}