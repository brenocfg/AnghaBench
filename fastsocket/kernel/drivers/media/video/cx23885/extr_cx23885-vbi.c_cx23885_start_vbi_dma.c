#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cx23885_dmaqueue {int count; } ;
struct cx23885_dev {int /*<<< orphan*/ * sram_channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  width; } ;
struct cx23885_buffer {TYPE_2__ risc; TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_CNTRL2 ; 
 size_t SRAM_CH02 ; 
 int /*<<< orphan*/  VID_A_DMA_CTL ; 
 int /*<<< orphan*/  VID_A_INT_MSK ; 
 int /*<<< orphan*/  cx23885_irq_add_enable (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  cx23885_sram_channel_setup (struct cx23885_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cx23885_start_vbi_dma(struct cx23885_dev    *dev,
			 struct cx23885_dmaqueue *q,
			 struct cx23885_buffer   *buf)
{
	/* setup fifo + format */
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH02],
				buf->vb.width, buf->risc.dma);

	/* reset counter */
	q->count = 1;

	/* enable irqs */
	cx23885_irq_add_enable(dev, 0x01);
	cx_set(VID_A_INT_MSK, 0x000022);

	/* start dma */
	cx_set(DEV_CNTRL2, (1<<5));
	cx_set(VID_A_DMA_CTL, 0x00000022);

	return 0;
}