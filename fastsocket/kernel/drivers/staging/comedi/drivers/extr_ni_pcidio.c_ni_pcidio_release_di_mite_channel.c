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
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mite_channel_lock; TYPE_1__* mite; int /*<<< orphan*/ * di_mite_chan; } ;
struct TYPE_3__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 scalar_t__ DMA_Line_Control_Group1 ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  mite_dma_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mite_dma_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mite_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int primary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int secondary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void ni_pcidio_release_di_mite_channel(struct comedi_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->di_mite_chan) {
		mite_dma_disarm(devpriv->di_mite_chan);
		mite_dma_reset(devpriv->di_mite_chan);
		mite_release_channel(devpriv->di_mite_chan);
		devpriv->di_mite_chan = NULL;
		writeb(primary_DMAChannel_bits(0) |
		       secondary_DMAChannel_bits(0),
		       devpriv->mite->daq_io_addr + DMA_Line_Control_Group1);
		mmiowb();
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
}