#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ni_gpct {int /*<<< orphan*/  mite_chan; } ;
struct mite_channel {int dir; int /*<<< orphan*/  channel; } ;
struct comedi_device {int dummy; } ;
typedef  enum comedi_io_direction { ____Placeholder_comedi_io_direction } comedi_io_direction ;
struct TYPE_3__ {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/  mite; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 struct mite_channel* mite_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_ring (TYPE_1__*,struct ni_gpct*) ; 
 int /*<<< orphan*/  ni_660x_set_dma_channel (struct comedi_device*,int /*<<< orphan*/ ,struct ni_gpct*) ; 
 int /*<<< orphan*/  ni_tio_set_mite_channel (struct ni_gpct*,struct mite_channel*) ; 
 TYPE_1__* private (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_660x_request_mite_channel(struct comedi_device *dev,
					struct ni_gpct *counter,
					enum comedi_io_direction direction)
{
	unsigned long flags;
	struct mite_channel *mite_chan;

	spin_lock_irqsave(&private(dev)->mite_channel_lock, flags);
	BUG_ON(counter->mite_chan);
	mite_chan =
	    mite_request_channel(private(dev)->mite, mite_ring(private(dev),
							       counter));
	if (mite_chan == NULL) {
		spin_unlock_irqrestore(&private(dev)->mite_channel_lock, flags);
		comedi_error(dev,
			     "failed to reserve mite dma channel for counter.");
		return -EBUSY;
	}
	mite_chan->dir = direction;
	ni_tio_set_mite_channel(counter, mite_chan);
	ni_660x_set_dma_channel(dev, mite_chan->channel, counter);
	spin_unlock_irqrestore(&private(dev)->mite_channel_lock, flags);
	return 0;
}