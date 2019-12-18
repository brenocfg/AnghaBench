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
struct mite_channel {int dir; int /*<<< orphan*/  channel; } ;
struct comedi_device {int dummy; } ;
typedef  enum comedi_io_direction { ____Placeholder_comedi_io_direction } comedi_io_direction ;
struct TYPE_6__ {int /*<<< orphan*/  mite_channel_lock; TYPE_1__* counter_dev; int /*<<< orphan*/ * gpct_mite_ring; int /*<<< orphan*/  mite; } ;
struct TYPE_5__ {int mite_chan; } ;
struct TYPE_4__ {TYPE_2__* counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 unsigned int NUM_GPCT ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_3__* devpriv ; 
 struct mite_channel* mite_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_gpct_dma_channel (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_set_mite_channel (TYPE_2__*,struct mite_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_request_gpct_mite_channel(struct comedi_device *dev,
					unsigned gpct_index,
					enum comedi_io_direction direction)
{
	unsigned long flags;
	struct mite_channel *mite_chan;

	BUG_ON(gpct_index >= NUM_GPCT);
	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	BUG_ON(devpriv->counter_dev->counters[gpct_index].mite_chan);
	mite_chan =
	    mite_request_channel(devpriv->mite,
				 devpriv->gpct_mite_ring[gpct_index]);
	if (mite_chan == NULL) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		comedi_error(dev,
			     "failed to reserve mite dma channel for counter.");
		return -EBUSY;
	}
	mite_chan->dir = direction;
	ni_tio_set_mite_channel(&devpriv->counter_dev->counters[gpct_index],
				mite_chan);
	ni_set_gpct_dma_channel(dev, gpct_index, mite_chan->channel);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}