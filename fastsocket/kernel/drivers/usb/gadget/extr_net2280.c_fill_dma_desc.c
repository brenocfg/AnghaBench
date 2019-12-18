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
typedef  int u32 ;
struct TYPE_8__ {int length; int dma; int /*<<< orphan*/  no_interrupt; } ;
struct net2280_request {int valid; TYPE_4__ req; struct net2280_dma* td; } ;
struct TYPE_5__ {int maxpacket; } ;
struct net2280_ep {TYPE_3__* dev; TYPE_1__ ep; scalar_t__ is_in; } ;
struct net2280_dma {void* dmacount; void* dmaaddr; } ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct TYPE_6__ {int device; } ;

/* Variables and functions */
 int DMA_DIRECTION ; 
 int DMA_DONE_INTERRUPT_ENABLE ; 
 int END_OF_CHAIN ; 
 int VALID_BIT ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  use_dma_chaining ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
fill_dma_desc (struct net2280_ep *ep, struct net2280_request *req, int valid)
{
	struct net2280_dma	*td = req->td;
	u32			dmacount = req->req.length;

	/* don't let DMA continue after a short OUT packet,
	 * so overruns can't affect the next transfer.
	 * in case of overruns on max-size packets, we can't
	 * stop the fifo from filling but we can flush it.
	 */
	if (ep->is_in)
		dmacount |= (1 << DMA_DIRECTION);
	if ((!ep->is_in && (dmacount % ep->ep.maxpacket) != 0)
			|| ep->dev->pdev->device != 0x2280)
		dmacount |= (1 << END_OF_CHAIN);

	req->valid = valid;
	if (valid)
		dmacount |= (1 << VALID_BIT);
	if (likely(!req->req.no_interrupt || !use_dma_chaining))
		dmacount |= (1 << DMA_DONE_INTERRUPT_ENABLE);

	/* td->dmadesc = previously set by caller */
	td->dmaaddr = cpu_to_le32 (req->req.dma);

	/* 2280 may be polling VALID_BIT through ep->dma->dmadesc */
	wmb ();
	td->dmacount = cpu_to_le32(dmacount);
}