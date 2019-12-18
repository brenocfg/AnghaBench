#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ fasdmatype_t ;
struct TYPE_10__ {unsigned long phase; unsigned long this_residual; } ;
struct TYPE_11__ {scalar_t__ phase; TYPE_1__ SCp; } ;
struct TYPE_12__ {scalar_t__ transfer_type; } ;
struct TYPE_13__ {TYPE_2__ scsi; TYPE_3__ dma; } ;
typedef  TYPE_4__ FAS216_Info ;

/* Variables and functions */
 unsigned long CFIS_CF ; 
 int /*<<< orphan*/  LOG_BUFFER ; 
 scalar_t__ PHASE_DATAOUT ; 
 int /*<<< orphan*/  REG_CFIS ; 
 unsigned long fas216_get_ctc (TYPE_4__*) ; 
 int /*<<< orphan*/  fas216_log (TYPE_4__*,int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long fas216_readb (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_updateptrs (TYPE_4__*,unsigned long) ; 
 scalar_t__ fasdma_none ; 
 scalar_t__ fasdma_pio ; 
 scalar_t__ fasdma_real_all ; 

__attribute__((used)) static void fas216_cleanuptransfer(FAS216_Info *info)
{
	unsigned long total, residual, fifo;
	fasdmatype_t dmatype = info->dma.transfer_type;

	info->dma.transfer_type = fasdma_none;

	/*
	 * PIO transfers do not need to be cleaned up.
	 */
	if (dmatype == fasdma_pio || dmatype == fasdma_none)
		return;

	if (dmatype == fasdma_real_all)
		total = info->scsi.SCp.phase;
	else
		total = info->scsi.SCp.this_residual;

	residual = fas216_get_ctc(info);

	fifo = fas216_readb(info, REG_CFIS) & CFIS_CF;

	fas216_log(info, LOG_BUFFER, "cleaning up from previous "
		   "transfer: length 0x%06x, residual 0x%x, fifo %d",
		   total, residual, fifo);

	/*
	 * If we were performing Data-Out, the transfer counter
	 * counts down each time a byte is transferred by the
	 * host to the FIFO.  This means we must include the
	 * bytes left in the FIFO from the transfer counter.
	 */
	if (info->scsi.phase == PHASE_DATAOUT)
		residual += fifo;

	fas216_updateptrs(info, total - residual);
}