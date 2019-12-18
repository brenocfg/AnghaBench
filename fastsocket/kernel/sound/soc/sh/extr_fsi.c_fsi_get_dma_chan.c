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
struct TYPE_5__ {void* dma_chan; } ;
struct TYPE_4__ {void* dma_chan; } ;
struct TYPE_6__ {TYPE_2__ fsib; TYPE_1__ fsia; } ;

/* Variables and functions */
 int EIO ; 
 void* PORTA_DMA ; 
 void* PORTB_DMA ; 
 int /*<<< orphan*/  free_dma (void*) ; 
 TYPE_3__* master ; 
 scalar_t__ request_dma (void*,char*) ; 

__attribute__((used)) static int fsi_get_dma_chan(void)
{
	if (0 != request_dma(PORTA_DMA, "fsia"))
		return -EIO;

	if (0 != request_dma(PORTB_DMA, "fsib")) {
		free_dma(PORTA_DMA);
		return -EIO;
	}

	master->fsia.dma_chan = PORTA_DMA;
	master->fsib.dma_chan = PORTB_DMA;

	return 0;
}