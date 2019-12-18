#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* page2; } ;
typedef  TYPE_2__ lithium_t ;
struct TYPE_8__ {int ctlval; TYPE_1__* desc; TYPE_2__* lith; } ;
typedef  TYPE_3__ dma_chan_t ;
struct TYPE_6__ {scalar_t__ direction; int /*<<< orphan*/  ctlreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPV (char*,int,...) ; 
 scalar_t__ LI_CCFG_DIR_OUT ; 
 int LI_CCTL_DMA_ENABLE ; 
 int LI_CCTL_RPTR ; 
 int LI_CCTL_WPTR ; 
 int /*<<< orphan*/  li_writel (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void li_deactivate_dma(dma_chan_t *chan)
{
	lithium_t *lith = chan->lith;
	void * lith2 = lith->page2;

	chan->ctlval &= ~(LI_CCTL_DMA_ENABLE | LI_CCTL_RPTR | LI_CCTL_WPTR);
	DBGPV("ctlval = 0x%lx\n", chan->ctlval);
	DBGPV("ctlreg 0x%x = 0x%lx\n", chan->desc->ctlreg, chan->ctlval);
	li_writel(lith, chan->desc->ctlreg, chan->ctlval);

	/*
	 * Offsets 0x98 and 0x9C on Lithium page 2 are undocumented,
	 * unsupported registers that are internal copies of the DMA
	 * read and write pointers.  Because of a Lithium bug, these
	 * registers aren't zeroed correctly when DMA is shut off.  So
	 * we whack them directly.
	 *
	 * I expect this to break in a future rev of Lithium.
	 */

	if (lith2 && chan->desc->direction == LI_CCFG_DIR_OUT) {
		* (volatile unsigned long *) (lith2 + 0x98) = 0;
		* (volatile unsigned long *) (lith2 + 0x9C) = 0;
	}
}