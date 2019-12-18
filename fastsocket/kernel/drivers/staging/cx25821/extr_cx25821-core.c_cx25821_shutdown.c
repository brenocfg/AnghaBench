#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cx25821_dev {TYPE_1__* sram_channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_msk; int /*<<< orphan*/  dma_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_A_INT_MSK ; 
 int /*<<< orphan*/  AUD_INT_DMA_CTL ; 
 int /*<<< orphan*/  DEV_CNTRL2 ; 
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int /*<<< orphan*/  UART_CTL ; 
 int VID_CHANNEL_NUM ; 
 int VID_UPSTREAM_SRAM_CHANNEL_I ; 
 int VID_UPSTREAM_SRAM_CHANNEL_J ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx25821_shutdown(struct cx25821_dev *dev)
{
	int i;

	/* disable RISC controller */
	cx_write(DEV_CNTRL2, 0);

	/* Disable Video A/B activity */
	for (i = 0; i < VID_CHANNEL_NUM; i++) {
		cx_write(dev->sram_channels[i].dma_ctl, 0);
		cx_write(dev->sram_channels[i].int_msk, 0);
	}

	for (i = VID_UPSTREAM_SRAM_CHANNEL_I; i <= VID_UPSTREAM_SRAM_CHANNEL_J;
	     i++) {
		cx_write(dev->sram_channels[i].dma_ctl, 0);
		cx_write(dev->sram_channels[i].int_msk, 0);
	}

	/* Disable Audio activity */
	cx_write(AUD_INT_DMA_CTL, 0);

	/* Disable Serial port */
	cx_write(UART_CTL, 0);

	/* Disable Interrupts */
	cx_write(PCI_INT_MSK, 0);
	cx_write(AUD_A_INT_MSK, 0);
}