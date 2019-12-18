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
struct flexcop_pci {int /*<<< orphan*/  count; int /*<<< orphan*/  count_prev; scalar_t__ last_dma1_cur_pos; int /*<<< orphan*/ * dma; } ;
struct flexcop_device {struct flexcop_pci* bus_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_DMA_1 ; 
 int /*<<< orphan*/  FC_DMA_2 ; 
 int FC_DMA_SUBADDR_0 ; 
 int FC_DMA_SUBADDR_1 ; 
 int /*<<< orphan*/  deb_irq (char*) ; 
 int /*<<< orphan*/  flexcop_dma_config (struct flexcop_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_dma_config_timer (struct flexcop_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_dma_control_timer_irq (struct flexcop_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flexcop_dma_xfer_control (struct flexcop_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int flexcop_pci_stream_control(struct flexcop_device *fc, int onoff)
{
	struct flexcop_pci *fc_pci = fc->bus_specific;
	if (onoff) {
		flexcop_dma_config(fc, &fc_pci->dma[0], FC_DMA_1);
		flexcop_dma_config(fc, &fc_pci->dma[1], FC_DMA_2);
		flexcop_dma_config_timer(fc, FC_DMA_1, 0);
		flexcop_dma_xfer_control(fc, FC_DMA_1,
				FC_DMA_SUBADDR_0 | FC_DMA_SUBADDR_1, 1);
		deb_irq("DMA xfer enabled\n");

		fc_pci->last_dma1_cur_pos = 0;
		flexcop_dma_control_timer_irq(fc, FC_DMA_1, 1);
		deb_irq("IRQ enabled\n");
		fc_pci->count_prev = fc_pci->count;
	} else {
		flexcop_dma_control_timer_irq(fc, FC_DMA_1, 0);
		deb_irq("IRQ disabled\n");

		flexcop_dma_xfer_control(fc, FC_DMA_1,
			 FC_DMA_SUBADDR_0 | FC_DMA_SUBADDR_1, 0);
		deb_irq("DMA xfer disabled\n");
	}
	return 0;
}