#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  this_residual; int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {TYPE_2__* device; TYPE_1__ SCp; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_8__ {unsigned short CNTR; unsigned long ACR; int ST_DMA; } ;
struct TYPE_7__ {int dma_bounce_len; int dma_dir; int /*<<< orphan*/ * dma_bounce_buffer; } ;
struct TYPE_6__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 unsigned long A2091_XFER_MASK ; 
 unsigned short CNTR_DDIR ; 
 unsigned short CNTR_INTEN ; 
 unsigned short CNTR_PDMD ; 
 TYPE_4__* DMA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__* HDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  cache_clear (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_push (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long virt_to_bus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dma_setup(struct scsi_cmnd *cmd, int dir_in)
{
    unsigned short cntr = CNTR_PDMD | CNTR_INTEN;
    unsigned long addr = virt_to_bus(cmd->SCp.ptr);
    struct Scsi_Host *instance = cmd->device->host;

    /* don't allow DMA if the physical address is bad */
    if (addr & A2091_XFER_MASK)
    {
	HDATA(instance)->dma_bounce_len = (cmd->SCp.this_residual + 511)
	    & ~0x1ff;
	HDATA(instance)->dma_bounce_buffer =
	    kmalloc (HDATA(instance)->dma_bounce_len, GFP_KERNEL);
	
	/* can't allocate memory; use PIO */
	if (!HDATA(instance)->dma_bounce_buffer) {
	    HDATA(instance)->dma_bounce_len = 0;
	    return 1;
	}

	/* get the physical address of the bounce buffer */
	addr = virt_to_bus(HDATA(instance)->dma_bounce_buffer);

	/* the bounce buffer may not be in the first 16M of physmem */
	if (addr & A2091_XFER_MASK) {
	    /* we could use chipmem... maybe later */
	    kfree (HDATA(instance)->dma_bounce_buffer);
	    HDATA(instance)->dma_bounce_buffer = NULL;
	    HDATA(instance)->dma_bounce_len = 0;
	    return 1;
	}

	if (!dir_in) {
		/* copy to bounce buffer for a write */
		memcpy (HDATA(instance)->dma_bounce_buffer,
			cmd->SCp.ptr, cmd->SCp.this_residual);
	}
    }

    /* setup dma direction */
    if (!dir_in)
	cntr |= CNTR_DDIR;

    /* remember direction */
    HDATA(cmd->device->host)->dma_dir = dir_in;

    DMA(cmd->device->host)->CNTR = cntr;

    /* setup DMA *physical* address */
    DMA(cmd->device->host)->ACR = addr;

    if (dir_in){
	/* invalidate any cache */
	cache_clear (addr, cmd->SCp.this_residual);
    }else{
	/* push any dirty cache */
	cache_push (addr, cmd->SCp.this_residual);
      }
    /* start DMA */
    DMA(cmd->device->host)->ST_DMA = 1;

    /* return success */
    return 0;
}