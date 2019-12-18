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
struct imx_dma_channel {int hw_chaining; } ;

/* Variables and functions */
 scalar_t__ cpu_is_mx27 () ; 

__attribute__((used)) static int imx_dma_hw_chain(struct imx_dma_channel *imxdma)
{
	if (cpu_is_mx27())
		return imxdma->hw_chaining;
	else
		return 0;
}