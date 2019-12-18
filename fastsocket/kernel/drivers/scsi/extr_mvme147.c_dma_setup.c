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
struct TYPE_4__ {int this_residual; int /*<<< orphan*/  ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct TYPE_6__ {int dma_dir; } ;
struct TYPE_5__ {int dma_bcr; unsigned long dma_dadr; unsigned char dma_cntrl; } ;

/* Variables and functions */
 TYPE_3__* HDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_clear (unsigned long,int) ; 
 int /*<<< orphan*/  cache_push (unsigned long,int) ; 
 TYPE_2__* m147_pcc ; 
 int /*<<< orphan*/  mvme147_host ; 
 unsigned long virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_setup(struct scsi_cmnd *cmd, int dir_in)
{
    unsigned char flags = 0x01;
    unsigned long addr = virt_to_bus(cmd->SCp.ptr);

    /* setup dma direction */
    if (!dir_in)
	flags |= 0x04;

    /* remember direction */
    HDATA(mvme147_host)->dma_dir = dir_in;

    if (dir_in)
  	/* invalidate any cache */
	cache_clear (addr, cmd->SCp.this_residual);
    else
	/* push any dirty cache */
	cache_push (addr, cmd->SCp.this_residual);

    /* start DMA */
    m147_pcc->dma_bcr   = cmd->SCp.this_residual | (1<<24);
    m147_pcc->dma_dadr  = addr;
    m147_pcc->dma_cntrl = flags;

    /* return success */
    return 0;
}