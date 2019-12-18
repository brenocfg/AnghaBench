#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* page1; } ;
typedef  TYPE_2__ lithium_t ;
struct TYPE_9__ {TYPE_1__* desc; int /*<<< orphan*/  ctlval; TYPE_2__* lith; } ;
typedef  TYPE_3__ dma_chan_t ;
struct TYPE_7__ {scalar_t__ direction; int /*<<< orphan*/  ctlreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGEV (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  DBGPV (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LI_CCFG_DIR_OUT ; 
 int /*<<< orphan*/  LI_CCTL_DMA_ENABLE ; 
 int /*<<< orphan*/  li_writel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void li_shutdown_dma(dma_chan_t *chan)
{
	lithium_t *lith = chan->lith;
	void * lith1 = lith->page1;

	DBGEV("(chan=0x%p)\n", chan);
	
	chan->ctlval &= ~LI_CCTL_DMA_ENABLE;
	DBGPV("ctlreg 0x%x = 0x%lx\n", chan->desc->ctlreg, chan->ctlval);
	li_writel(lith, chan->desc->ctlreg, chan->ctlval);

	/*
	 * Offset 0x500 on Lithium page 1 is an undocumented,
	 * unsupported register that holds the zero sample value.
	 * Lithium is supposed to output zero samples when DMA is
	 * inactive, and repeat the last sample when DMA underflows.
	 * But it has a bug, where, after underflow occurs, the zero
	 * sample is not reset.
	 *
	 * I expect this to break in a future rev of Lithium.
	 */

	if (lith1 && chan->desc->direction == LI_CCFG_DIR_OUT)
		* (volatile unsigned long *) (lith1 + 0x500) = 0;
}