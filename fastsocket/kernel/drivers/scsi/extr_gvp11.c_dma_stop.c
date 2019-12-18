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
struct Scsi_Host {int dummy; } ;
struct TYPE_6__ {int SP_DMA; int /*<<< orphan*/  CNTR; } ;
struct TYPE_5__ {scalar_t__ dma_buffer_pool; scalar_t__ dma_bounce_len; int /*<<< orphan*/ * dma_bounce_buffer; scalar_t__ dma_dir; } ;

/* Variables and functions */
 scalar_t__ BUF_SCSI_ALLOCED ; 
 TYPE_3__* DMA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  GVP11_DMAC_INT_ENABLE ; 
 TYPE_2__* HDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  amiga_chip_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_stop(struct Scsi_Host *instance, struct scsi_cmnd *SCpnt,
		     int status)
{
    /* stop DMA */
    DMA(instance)->SP_DMA = 1;
    /* remove write bit from CONTROL bits */
    DMA(instance)->CNTR = GVP11_DMAC_INT_ENABLE;

    /* copy from a bounce buffer, if necessary */
    if (status && HDATA(instance)->dma_bounce_buffer) {
	if (HDATA(instance)->dma_dir && SCpnt)
	    memcpy (SCpnt->SCp.ptr, 
		    HDATA(instance)->dma_bounce_buffer,
		    SCpnt->SCp.this_residual);
	
	if (HDATA(instance)->dma_buffer_pool == BUF_SCSI_ALLOCED)
	    kfree (HDATA(instance)->dma_bounce_buffer);
	else
	    amiga_chip_free(HDATA(instance)->dma_bounce_buffer);
	
	HDATA(instance)->dma_bounce_buffer = NULL;
	HDATA(instance)->dma_bounce_len = 0;
    }
}