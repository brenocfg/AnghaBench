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
struct ni_gpct {int /*<<< orphan*/  lock; scalar_t__ mite_chan; } ;
struct comedi_subdevice {TYPE_1__* async; struct ni_gpct* private; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NI_GPCT_ARM_IMMEDIATE ; 
 int /*<<< orphan*/  mite_dma_arm (scalar_t__) ; 
 int ni_tio_arm (struct ni_gpct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_tio_input_inttrig(struct comedi_device *dev,
				struct comedi_subdevice *s,
				unsigned int trignum)
{
	unsigned long flags;
	int retval = 0;
	struct ni_gpct *counter = s->private;

	BUG_ON(counter == NULL);
	if (trignum != 0)
		return -EINVAL;

	spin_lock_irqsave(&counter->lock, flags);
	if (counter->mite_chan)
		mite_dma_arm(counter->mite_chan);
	else
		retval = -EIO;
	spin_unlock_irqrestore(&counter->lock, flags);
	if (retval < 0)
		return retval;
	retval = ni_tio_arm(counter, 1, NI_GPCT_ARM_IMMEDIATE);
	s->async->inttrig = NULL;

	return retval;
}