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
struct TYPE_5__ {int dma_chan; } ;
struct TYPE_4__ {int dma_chan; } ;
struct TYPE_6__ {TYPE_2__ fsib; TYPE_1__ fsia; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORTA_DMA ; 
 int /*<<< orphan*/  PORTB_DMA ; 
 int /*<<< orphan*/  dma_wait_for_completion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 TYPE_3__* master ; 

__attribute__((used)) static void fsi_free_dma_chan(void)
{
	dma_wait_for_completion(PORTA_DMA);
	dma_wait_for_completion(PORTB_DMA);
	free_dma(PORTA_DMA);
	free_dma(PORTB_DMA);

	master->fsia.dma_chan = -1;
	master->fsib.dma_chan = -1;
}