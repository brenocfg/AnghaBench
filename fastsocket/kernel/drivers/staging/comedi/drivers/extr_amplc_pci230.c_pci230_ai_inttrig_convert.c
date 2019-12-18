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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int adccon; scalar_t__ hwver; int /*<<< orphan*/  ai_stop_spinlock; scalar_t__ iobase1; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CMD_STARTED ; 
 int EINVAL ; 
 int /*<<< orphan*/  I8254_MODE0 ; 
 int /*<<< orphan*/  I8254_MODE1 ; 
 int PCI230_ADC_IM_DIF ; 
 int PCI230_ADC_IM_MASK ; 
 scalar_t__ PCI230_Z2_CT_BASE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8254_set_mode (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static int pci230_ai_inttrig_convert(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     unsigned int trig_num)
{
	unsigned long irqflags;

	if (trig_num != 0)
		return -EINVAL;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	if (test_bit(AI_CMD_STARTED, &devpriv->state)) {
		unsigned int delayus;

		/* Trigger conversion by toggling Z2-CT2 output.  Finish
		 * with output high. */
		i8254_set_mode(devpriv->iobase1 + PCI230_Z2_CT_BASE, 0, 2,
			       I8254_MODE0);
		i8254_set_mode(devpriv->iobase1 + PCI230_Z2_CT_BASE, 0, 2,
			       I8254_MODE1);
		/* Delay.  Should driver be responsible for this?  An
		 * alternative would be to wait until conversion is complete,
		 * but we can't tell when it's complete because the ADC busy
		 * bit has a different meaning when FIFO enabled (and when
		 * FIFO not enabled, it only works for software triggers). */
		if (((devpriv->adccon & PCI230_ADC_IM_MASK)
		     == PCI230_ADC_IM_DIF)
		    && (devpriv->hwver == 0)) {
			/* PCI230/260 in differential mode */
			delayus = 8;
		} else {
			/* single-ended or PCI230+/260+ */
			delayus = 4;
		}
		spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
		udelay(delayus);
	} else {
		spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
	}

	return 1;
}