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
struct TYPE_4__ {int /*<<< orphan*/  mmio; TYPE_2__* dma_wt; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_5__ {int period_virt; int period_bytes; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 scalar_t__ VORTEX_WTDMA_STAT ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int inline vortex_wtdma_getlinearpos(vortex_t * vortex, int wtdma)
{
	stream_t *dma = &vortex->dma_wt[wtdma];
	int temp;

	temp = hwread(vortex->mmio, VORTEX_WTDMA_STAT + (wtdma << 2));
	temp = (dma->period_virt * dma->period_bytes) + (temp & (dma->period_bytes - 1));
	return temp;
}