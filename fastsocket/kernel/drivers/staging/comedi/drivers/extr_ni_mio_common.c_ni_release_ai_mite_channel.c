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
struct TYPE_2__ {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/ * ai_mite_chan; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  mite_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ni_set_ai_dma_channel (struct comedi_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ni_release_ai_mite_channel(struct comedi_device *dev)
{
#ifdef PCIDMA
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->ai_mite_chan) {
		ni_set_ai_dma_channel(dev, -1);
		mite_release_channel(devpriv->ai_mite_chan);
		devpriv->ai_mite_chan = NULL;
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
#endif /*  PCIDMA */
}