#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mmio; TYPE_2__* dma_adb; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_7__ {int fifo_status; int /*<<< orphan*/  fifo_enabled; int /*<<< orphan*/  dma_unknown; int /*<<< orphan*/  dma_ctrl; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
#define  FIFO_PAUSE 130 
#define  FIFO_START 129 
#define  FIFO_STOP 128 
 int /*<<< orphan*/  VORTEX_ADBDMA_CTRL ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_fifo_setadbctrl (TYPE_1__*,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_fifo_setadbvalid (TYPE_1__*,int,int) ; 

__attribute__((used)) static void vortex_adbdma_startfifo(vortex_t * vortex, int adbdma)
{
	int this_8 = 0 /*empty */ , this_4 = 0 /*priority */ ;
	stream_t *dma = &vortex->dma_adb[adbdma];

	switch (dma->fifo_status) {
	case FIFO_START:
		vortex_fifo_setadbvalid(vortex, adbdma,
					dma->fifo_enabled ? 1 : 0);
		break;
	case FIFO_STOP:
		this_8 = 1;
		hwwrite(vortex->mmio, VORTEX_ADBDMA_CTRL + (adbdma << 2),
			dma->dma_ctrl);
		vortex_fifo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fifo_enabled ? 1 : 0, 0);
		break;
	case FIFO_PAUSE:
		vortex_fifo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fifo_enabled ? 1 : 0, 0);
		break;
	}
	dma->fifo_status = FIFO_START;
}