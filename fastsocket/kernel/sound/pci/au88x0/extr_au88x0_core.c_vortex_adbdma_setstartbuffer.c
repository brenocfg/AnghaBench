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
struct TYPE_4__ {int /*<<< orphan*/  mmio; TYPE_2__* dma_adb; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_5__ {int period_real; int period_virt; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 scalar_t__ VORTEX_ADBDMA_START ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void vortex_adbdma_setstartbuffer(vortex_t * vortex, int adbdma, int sb)
{
	stream_t *dma = &vortex->dma_adb[adbdma];
	//hwwrite(vortex->mmio, VORTEX_ADBDMA_START + (adbdma << 2), sb << (((NR_ADB-1)-((adbdma&0xf)*2))));
	hwwrite(vortex->mmio, VORTEX_ADBDMA_START + (adbdma << 2),
		sb << ((0xf - (adbdma & 0xf)) * 2));
	dma->period_real = dma->period_virt = sb;
}