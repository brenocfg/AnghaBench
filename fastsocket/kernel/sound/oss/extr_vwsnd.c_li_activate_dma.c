#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctlval; TYPE_1__* desc; int /*<<< orphan*/  lith; } ;
typedef  TYPE_2__ dma_chan_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctlreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPV (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LI_CCTL_DMA_ENABLE ; 
 int /*<<< orphan*/  li_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void li_activate_dma(dma_chan_t *chan)
{
	chan->ctlval |= LI_CCTL_DMA_ENABLE;
	DBGPV("ctlval = 0x%lx\n", chan->ctlval);
	li_writel(chan->lith, chan->desc->ctlreg, chan->ctlval);
}