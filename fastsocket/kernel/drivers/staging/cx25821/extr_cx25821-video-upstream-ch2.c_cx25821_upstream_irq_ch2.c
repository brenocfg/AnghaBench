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
typedef  scalar_t__ u32 ;
struct sram_channel {int /*<<< orphan*/  int_stat; int /*<<< orphan*/  int_mstat; } ;
struct cx25821_dev {struct sram_channel* sram_channels; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_RETVAL (int) ; 
 int VID_UPSTREAM_SRAM_CHANNEL_J ; 
 int /*<<< orphan*/  cx25821_stop_upstream_video_ch2 (struct cx25821_dev*) ; 
 int cx25821_video_upstream_irq_ch2 (struct cx25821_dev*,int,scalar_t__) ; 
 scalar_t__ cx_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cx25821_upstream_irq_ch2(int irq, void *dev_id)
{
	struct cx25821_dev *dev = dev_id;
	u32 msk_stat, vid_status;
	int handled = 0;
	int channel_num = 0;
	struct sram_channel *sram_ch;

	if (!dev)
		return -1;

	channel_num = VID_UPSTREAM_SRAM_CHANNEL_J;

	sram_ch = &dev->sram_channels[channel_num];

	msk_stat = cx_read(sram_ch->int_mstat);
	vid_status = cx_read(sram_ch->int_stat);

	// Only deal with our interrupt
	if (vid_status) {
		handled =
		    cx25821_video_upstream_irq_ch2(dev, channel_num,
						   vid_status);
	}

	if (handled < 0) {
		cx25821_stop_upstream_video_ch2(dev);
	} else {
		handled += handled;
	}

	return IRQ_RETVAL(handled);
}