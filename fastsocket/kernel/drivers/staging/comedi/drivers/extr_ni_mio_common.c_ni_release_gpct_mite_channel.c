#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mite_channel {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mite_channel_lock; TYPE_1__* counter_dev; } ;
struct TYPE_5__ {struct mite_channel* mite_chan; } ;
struct TYPE_4__ {TYPE_2__* counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int NUM_GPCT ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  mite_release_channel (struct mite_channel*) ; 
 int /*<<< orphan*/  ni_set_gpct_dma_channel (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  ni_tio_set_mite_channel (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ni_release_gpct_mite_channel(struct comedi_device *dev,
				  unsigned gpct_index)
{
#ifdef PCIDMA
	unsigned long flags;

	BUG_ON(gpct_index >= NUM_GPCT);
	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->counter_dev->counters[gpct_index].mite_chan) {
		struct mite_channel *mite_chan =
		    devpriv->counter_dev->counters[gpct_index].mite_chan;

		ni_set_gpct_dma_channel(dev, gpct_index, -1);
		ni_tio_set_mite_channel(&devpriv->
					counter_dev->counters[gpct_index],
					NULL);
		mite_release_channel(mite_chan);
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
#endif /*  PCIDMA */
}