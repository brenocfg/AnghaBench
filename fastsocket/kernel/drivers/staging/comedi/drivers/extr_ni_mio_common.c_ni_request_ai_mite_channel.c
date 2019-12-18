#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mite_channel_lock; TYPE_1__* ai_mite_chan; int /*<<< orphan*/  ai_mite_ring; int /*<<< orphan*/  mite; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (TYPE_1__*) ; 
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int EBUSY ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 TYPE_1__* mite_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_ai_dma_channel (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_request_ai_mite_channel(struct comedi_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	BUG_ON(devpriv->ai_mite_chan);
	devpriv->ai_mite_chan =
	    mite_request_channel(devpriv->mite, devpriv->ai_mite_ring);
	if (devpriv->ai_mite_chan == NULL) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		comedi_error(dev,
			     "failed to reserve mite dma channel for analog input.");
		return -EBUSY;
	}
	devpriv->ai_mite_chan->dir = COMEDI_INPUT;
	ni_set_ai_dma_channel(dev, devpriv->ai_mite_chan->channel);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}