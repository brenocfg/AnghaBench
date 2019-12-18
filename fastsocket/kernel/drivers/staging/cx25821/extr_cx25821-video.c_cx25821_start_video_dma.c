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
struct sram_channel {int i; int /*<<< orphan*/  dma_ctl; int /*<<< orphan*/  int_msk; int /*<<< orphan*/  gpcnt_ctl; } ;
struct cx25821_dmaqueue {int count; } ;
struct cx25821_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;
struct cx25821_buffer {TYPE_1__ risc; int /*<<< orphan*/  bpl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int /*<<< orphan*/  VID_CH_MODE_SEL ; 
 int /*<<< orphan*/  cx25821_sram_channel_setup (struct cx25821_dev*,struct sram_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

int cx25821_start_video_dma(struct cx25821_dev *dev,
			    struct cx25821_dmaqueue *q,
			    struct cx25821_buffer *buf,
			    struct sram_channel *channel)
{
	int tmp = 0;

	/* setup fifo + format */
	cx25821_sram_channel_setup(dev, channel, buf->bpl, buf->risc.dma);

	/* reset counter */
	cx_write(channel->gpcnt_ctl, 3);
	q->count = 1;

	/* enable irq */
	cx_set(PCI_INT_MSK, cx_read(PCI_INT_MSK) | (1 << channel->i));
	cx_set(channel->int_msk, 0x11);

	/* start dma */
	cx_write(channel->dma_ctl, 0x11);	/* FIFO and RISC enable */

	/* make sure upstream setting if any is reversed */
	tmp = cx_read(VID_CH_MODE_SEL);
	cx_write(VID_CH_MODE_SEL, tmp & 0xFFFFFE00);

	return 0;
}