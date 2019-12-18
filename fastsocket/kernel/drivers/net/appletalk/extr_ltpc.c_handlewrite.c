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
struct net_device {int dma; int base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int) ; 
 int /*<<< orphan*/  disable_dma (int) ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int /*<<< orphan*/  get_dma_residue (int) ; 
 int /*<<< orphan*/  inb_p (int) ; 
 int /*<<< orphan*/  ltdmabuf ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int,int) ; 
 int /*<<< orphan*/  set_dma_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_bus (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_timeout (struct net_device*,int) ; 

__attribute__((used)) static void handlewrite(struct net_device *dev)
{
	/* called *only* from idle, non-reentrant */
	/* on entry, 0xfb and ltdmabuf holds data */
	int dma = dev->dma;
	int base = dev->base_addr;
	unsigned long flags;
	
	flags=claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma,DMA_MODE_WRITE);
	set_dma_addr(dma,virt_to_bus(ltdmabuf));
	set_dma_count(dma,800);
	enable_dma(dma);
	release_dma_lock(flags);
	
	inb_p(base+3);
	inb_p(base+2);

	if ( wait_timeout(dev,0xfb) ) {
		flags=claim_dma_lock();
		printk("timed out in handlewrite, dma res %d\n",
			get_dma_residue(dev->dma) );
		release_dma_lock(flags);
	}
}