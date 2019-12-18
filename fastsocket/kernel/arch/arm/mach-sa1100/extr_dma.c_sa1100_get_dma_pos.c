#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int RdDCSR; int /*<<< orphan*/  DBSB; int /*<<< orphan*/  DBSA; } ;
typedef  TYPE_1__ dma_regs_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DCSR_BIU ; 
 int DCSR_STRTA ; 
 int DCSR_STRTB ; 

dma_addr_t sa1100_get_dma_pos(dma_regs_t *regs)
{
	int status;

	/*
	 * We must determine whether buffer A or B is active.
	 * Two possibilities: either we are in the middle of
	 * a buffer, or the DMA controller just switched to the
	 * next toggle but the interrupt hasn't been serviced yet.
	 * The former case is straight forward.  In the later case,
	 * we'll do like if DMA is just at the end of the previous
	 * toggle since all registers haven't been reset yet.
	 * This goes around the edge case and since we're always
	 * a little behind anyways it shouldn't make a big difference.
	 * If DMA has been stopped prior calling this then the
	 * position is exact.
	 */
	status = regs->RdDCSR;
	if ((!(status & DCSR_BIU) &&  (status & DCSR_STRTA)) ||
	    ( (status & DCSR_BIU) && !(status & DCSR_STRTB)))
		return regs->DBSA;
	else
		return regs->DBSB;
}