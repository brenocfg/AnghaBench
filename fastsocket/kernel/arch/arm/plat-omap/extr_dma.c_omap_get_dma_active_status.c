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

/* Variables and functions */
 int /*<<< orphan*/  CCR (int) ; 
 int OMAP_DMA_CCR_EN ; 
 int dma_read (int /*<<< orphan*/ ) ; 

int omap_get_dma_active_status(int lch)
{
	return (dma_read(CCR(lch)) & OMAP_DMA_CCR_EN) != 0;
}