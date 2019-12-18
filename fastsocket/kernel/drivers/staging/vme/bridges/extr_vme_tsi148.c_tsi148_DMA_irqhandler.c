#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  TSI148_LCSR_INTC_DMA0C ; 
 int /*<<< orphan*/  TSI148_LCSR_INTC_DMA1C ; 
 int TSI148_LCSR_INTS_DMA0S ; 
 int TSI148_LCSR_INTS_DMA1S ; 
 int /*<<< orphan*/ * dma_queue ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 tsi148_DMA_irqhandler(int channel_mask)
{
	u32 serviced = 0;

	if (channel_mask & TSI148_LCSR_INTS_DMA0S) {
		wake_up(&dma_queue[0]);
		serviced |= TSI148_LCSR_INTC_DMA0C;
	}
	if (channel_mask & TSI148_LCSR_INTS_DMA1S) {
		wake_up(&dma_queue[1]);
		serviced |= TSI148_LCSR_INTC_DMA1C;
	}

	return serviced;
}