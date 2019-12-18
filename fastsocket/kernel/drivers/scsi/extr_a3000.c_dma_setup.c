#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  this_residual; int /*<<< orphan*/  ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct TYPE_6__ {unsigned short CNTR; unsigned long ACR; int ST_DMA; } ;
struct TYPE_5__ {int dma_bounce_len; int dma_dir; int /*<<< orphan*/  dma_bounce_buffer; } ;

/* Variables and functions */
 unsigned long A3000_XFER_MASK ; 
 unsigned short CNTR_DDIR ; 
 unsigned short CNTR_INTEN ; 
 unsigned short CNTR_PDMD ; 
 TYPE_3__* DMA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* HDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3000_host ; 
 int /*<<< orphan*/  cache_clear (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_push (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_setup(struct scsi_cmnd *cmd, int dir_in)
{
    unsigned short cntr = CNTR_PDMD | CNTR_INTEN;
    unsigned long addr = virt_to_bus(cmd->SCp.ptr);

    /*
     * if the physical address has the wrong alignment, or if
     * physical address is bad, or if it is a write and at the
     * end of a physical memory chunk, then allocate a bounce
     * buffer
     */
    if (addr & A3000_XFER_MASK)
    {
	HDATA(a3000_host)->dma_bounce_len = (cmd->SCp.this_residual + 511)
	    & ~0x1ff;
	HDATA(a3000_host)->dma_bounce_buffer =
	    kmalloc (HDATA(a3000_host)->dma_bounce_len, GFP_KERNEL);
	
	/* can't allocate memory; use PIO */
	if (!HDATA(a3000_host)->dma_bounce_buffer) {
	    HDATA(a3000_host)->dma_bounce_len = 0;
	    return 1;
	}

	if (!dir_in) {
	    /* copy to bounce buffer for a write */
	    memcpy (HDATA(a3000_host)->dma_bounce_buffer,
		cmd->SCp.ptr, cmd->SCp.this_residual);
	}

	addr = virt_to_bus(HDATA(a3000_host)->dma_bounce_buffer);
    }

    /* setup dma direction */
    if (!dir_in)
	cntr |= CNTR_DDIR;

    /* remember direction */
    HDATA(a3000_host)->dma_dir = dir_in;

    DMA(a3000_host)->CNTR = cntr;

    /* setup DMA *physical* address */
    DMA(a3000_host)->ACR = addr;

    if (dir_in)
  	/* invalidate any cache */
	cache_clear (addr, cmd->SCp.this_residual);
    else
	/* push any dirty cache */
	cache_push (addr, cmd->SCp.this_residual);

    /* start DMA */
    mb();			/* make sure setup is completed */
    DMA(a3000_host)->ST_DMA = 1;
    mb();			/* make sure DMA has started before next IO */

    /* return success */
    return 0;
}