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
struct comedi_subdevice {TYPE_2__* async; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct TYPE_6__ {int reg_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  prealloc_bufsz; } ;
struct TYPE_4__ {int /*<<< orphan*/  mite_channel_lock; scalar_t__ ao_mite_chan; } ;

/* Variables and functions */
 int EIO ; 
 int NI_AO_SUBDEV ; 
 TYPE_3__ boardtype ; 
 int /*<<< orphan*/  comedi_buf_read_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  mite_dma_arm (scalar_t__) ; 
 int /*<<< orphan*/  mite_prep_dma (scalar_t__,int,int) ; 
 int ni_reg_611x ; 
 int ni_reg_6713 ; 
 int ni_request_ao_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_ao_setup_MITE_dma(struct comedi_device *dev)
{
	struct comedi_subdevice *s = dev->subdevices + NI_AO_SUBDEV;
	int retval;
	unsigned long flags;

	retval = ni_request_ao_mite_channel(dev);
	if (retval)
		return retval;

	/* read alloc the entire buffer */
	comedi_buf_read_alloc(s->async, s->async->prealloc_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->ao_mite_chan) {
		if (boardtype.reg_type & (ni_reg_611x | ni_reg_6713)) {
			mite_prep_dma(devpriv->ao_mite_chan, 32, 32);
		} else {
			/* doing 32 instead of 16 bit wide transfers from memory
			   makes the mite do 32 bit pci transfers, doubling pci bandwidth. */
			mite_prep_dma(devpriv->ao_mite_chan, 16, 32);
		}
		mite_dma_arm(devpriv->ao_mite_chan);
	} else
		retval = -EIO;
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	return retval;
}