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
struct ni_gpct {struct mite_channel* mite_chan; } ;
struct mite_channel {int /*<<< orphan*/  channel; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mite_channel_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mite_release_channel (struct mite_channel*) ; 
 int /*<<< orphan*/  ni_660x_unset_dma_channel (struct comedi_device*,int /*<<< orphan*/ ,struct ni_gpct*) ; 
 int /*<<< orphan*/  ni_tio_set_mite_channel (struct ni_gpct*,int /*<<< orphan*/ *) ; 
 TYPE_1__* private (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ni_660x_release_mite_channel(struct comedi_device *dev,
				  struct ni_gpct *counter)
{
	unsigned long flags;

	spin_lock_irqsave(&private(dev)->mite_channel_lock, flags);
	if (counter->mite_chan) {
		struct mite_channel *mite_chan = counter->mite_chan;

		ni_660x_unset_dma_channel(dev, mite_chan->channel, counter);
		ni_tio_set_mite_channel(counter, NULL);
		mite_release_channel(mite_chan);
	}
	spin_unlock_irqrestore(&private(dev)->mite_channel_lock, flags);
}