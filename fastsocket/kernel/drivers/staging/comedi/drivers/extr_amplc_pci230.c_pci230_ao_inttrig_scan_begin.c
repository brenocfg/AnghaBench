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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int hwver; int /*<<< orphan*/  ao_stop_spinlock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_CMD_STARTED ; 
 int EINVAL ; 
 scalar_t__ PCI230P2_DACSWTRIG ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  pci230_handle_ao_nofifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pci230_ao_inttrig_scan_begin(struct comedi_device *dev,
					struct comedi_subdevice *s,
					unsigned int trig_num)
{
	unsigned long irqflags;

	if (trig_num != 0)
		return -EINVAL;

	spin_lock_irqsave(&devpriv->ao_stop_spinlock, irqflags);
	if (test_bit(AO_CMD_STARTED, &devpriv->state)) {
		/* Perform scan. */
		if (devpriv->hwver < 2) {
			/* Not using DAC FIFO. */
			spin_unlock_irqrestore(&devpriv->ao_stop_spinlock,
					       irqflags);
			pci230_handle_ao_nofifo(dev, s);
			comedi_event(dev, s);
		} else {
			/* Using DAC FIFO. */
			/* Read DACSWTRIG register to trigger conversion. */
			inw(dev->iobase + PCI230P2_DACSWTRIG);
			spin_unlock_irqrestore(&devpriv->ao_stop_spinlock,
					       irqflags);
		}
		/* Delay.  Should driver be responsible for this? */
		/* XXX TODO: See if DAC busy bit can be used. */
		udelay(8);
	}

	return 1;
}