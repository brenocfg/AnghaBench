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
struct cx25821_dev {size_t _audio_upstream_channel_select; struct sram_channel* sram_channels; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_RETVAL (int) ; 
 int cx25821_audio_upstream_irq (struct cx25821_dev*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  cx25821_stop_upstream_audio (struct cx25821_dev*) ; 
 scalar_t__ cx_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cx25821_upstream_irq_audio(int irq, void *dev_id)
{
	struct cx25821_dev *dev = dev_id;
	u32 msk_stat, audio_status;
	int handled = 0;
	struct sram_channel *sram_ch;

	if (!dev)
		return -1;

	sram_ch = &dev->sram_channels[dev->_audio_upstream_channel_select];

	msk_stat = cx_read(sram_ch->int_mstat);
	audio_status = cx_read(sram_ch->int_stat);

	// Only deal with our interrupt
	if (audio_status) {
		handled =
		    cx25821_audio_upstream_irq(dev,
					       dev->
					       _audio_upstream_channel_select,
					       audio_status);
	}

	if (handled < 0) {
		cx25821_stop_upstream_audio(dev);
	} else {
		handled += handled;
	}

	return IRQ_RETVAL(handled);
}