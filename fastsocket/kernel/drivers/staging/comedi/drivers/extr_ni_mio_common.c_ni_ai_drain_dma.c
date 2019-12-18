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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mite_channel_lock; scalar_t__ ai_mite_chan; } ;

/* Variables and functions */
 int AI_FIFO_Empty_St ; 
 int /*<<< orphan*/  AI_Status_1_Register ; 
 TYPE_1__* devpriv ; 
 scalar_t__ mite_bytes_in_transit (scalar_t__) ; 
 int /*<<< orphan*/  ni_sync_ai_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ni_ai_drain_dma(struct comedi_device *dev)
{
	int i;
	static const int timeout = 10000;
	unsigned long flags;
	int retval = 0;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->ai_mite_chan) {
		for (i = 0; i < timeout; i++) {
			if ((devpriv->stc_readw(dev,
						AI_Status_1_Register) &
			     AI_FIFO_Empty_St)
			    && mite_bytes_in_transit(devpriv->ai_mite_chan) ==
			    0)
				break;
			udelay(5);
		}
		if (i == timeout) {
			printk("ni_mio_common: wait for dma drain timed out\n");
			printk
			    ("mite_bytes_in_transit=%i, AI_Status1_Register=0x%x\n",
			     mite_bytes_in_transit(devpriv->ai_mite_chan),
			     devpriv->stc_readw(dev, AI_Status_1_Register));
			retval = -1;
		}
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	ni_sync_ai_dma(dev);

	return retval;
}