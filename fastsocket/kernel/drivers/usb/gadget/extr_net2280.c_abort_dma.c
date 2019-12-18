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
struct net2280_ep {TYPE_1__* dma; int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmastat; } ;

/* Variables and functions */
 int DMA_ABORT ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_dma_completions (struct net2280_ep*) ; 
 int /*<<< orphan*/  spin_stop_dma (TYPE_1__*) ; 
 int /*<<< orphan*/  stop_dma (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void abort_dma (struct net2280_ep *ep)
{
	/* abort the current transfer */
	if (likely (!list_empty (&ep->queue))) {
		/* FIXME work around errata 0121, 0122, 0124 */
		writel ((1 << DMA_ABORT), &ep->dma->dmastat);
		spin_stop_dma (ep->dma);
	} else
		stop_dma (ep->dma);
	scan_dma_completions (ep);
}