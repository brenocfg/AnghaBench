#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  mite_channel_lock; TYPE_2__* mite; TYPE_1__* di_mite_chan; int /*<<< orphan*/  di_mite_ring; } ;
struct TYPE_6__ {scalar_t__ daq_io_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (TYPE_1__*) ; 
 scalar_t__ DMA_Line_Control_Group1 ; 
 int EBUSY ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_3__* devpriv ; 
 TYPE_1__* mite_request_channel_in_range (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int primary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int secondary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int ni_pcidio_request_di_mite_channel(struct comedi_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	BUG_ON(devpriv->di_mite_chan);
	devpriv->di_mite_chan =
	    mite_request_channel_in_range(devpriv->mite,
					  devpriv->di_mite_ring, 1, 2);
	if (devpriv->di_mite_chan == NULL) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		comedi_error(dev, "failed to reserve mite dma channel.");
		return -EBUSY;
	}
	writeb(primary_DMAChannel_bits(devpriv->di_mite_chan->channel) |
	       secondary_DMAChannel_bits(devpriv->di_mite_chan->channel),
	       devpriv->mite->daq_io_addr + DMA_Line_Control_Group1);
	mmiowb();
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}