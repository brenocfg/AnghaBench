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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int chanlist_len; int stop_src; int stop_arg; scalar_t__ start_src; int convert_src; int flags; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {scalar_t__ events; TYPE_1__ cmd; } ;
struct TYPE_6__ {int count; int forever; int /*<<< orphan*/  divisor2; int /*<<< orphan*/  divisor1; } ;
struct TYPE_5__ {int resolution; } ;

/* Variables and functions */
 int CASC ; 
 int CONV_CONTROL ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS800_CONV_CONTROL ; 
 scalar_t__ DAS800_GAIN ; 
 scalar_t__ DAS800_SCAN_LIMITS ; 
 int DTEN ; 
 int EACS ; 
 int IEOC ; 
 int ITE ; 
 int SCAN_LIMITS ; 
 int /*<<< orphan*/  TIMER_BASE ; 
#define  TRIG_COUNT 131 
#define  TRIG_EXT 130 
#define  TRIG_NONE 129 
 int TRIG_ROUND_MASK ; 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  das800_set_frequency (struct comedi_device*) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  disable_das800 (struct comedi_device*) ; 
 int /*<<< orphan*/  enable_das800 (struct comedi_device*) ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer_2div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__* thisboard ; 

__attribute__((used)) static int das800_ai_do_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	int startChan, endChan, scan, gain;
	int conv_bits;
	unsigned long irq_flags;
	struct comedi_async *async = s->async;

	if (!dev->irq) {
		comedi_error(dev,
			     "no irq assigned for das-800, cannot do hardware conversions");
		return -1;
	}

	disable_das800(dev);

	/* set channel scan limits */
	startChan = CR_CHAN(async->cmd.chanlist[0]);
	endChan = (startChan + async->cmd.chanlist_len - 1) % 8;
	scan = (endChan << 3) | startChan;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	outb(SCAN_LIMITS, dev->iobase + DAS800_GAIN);	/* select base address + 2 to be scan limits register */
	outb(scan, dev->iobase + DAS800_SCAN_LIMITS);	/* set scan limits */
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	/* set gain */
	gain = CR_RANGE(async->cmd.chanlist[0]);
	if (thisboard->resolution == 12 && gain > 0)
		gain += 0x7;
	gain &= 0xf;
	outb(gain, dev->iobase + DAS800_GAIN);

	switch (async->cmd.stop_src) {
	case TRIG_COUNT:
		devpriv->count = async->cmd.stop_arg * async->cmd.chanlist_len;
		devpriv->forever = 0;
		break;
	case TRIG_NONE:
		devpriv->forever = 1;
		devpriv->count = 0;
		break;
	default:
		break;
	}

	/* enable auto channel scan, send interrupts on end of conversion
	 * and set clock source to internal or external
	 */
	conv_bits = 0;
	conv_bits |= EACS | IEOC;
	if (async->cmd.start_src == TRIG_EXT)
		conv_bits |= DTEN;
	switch (async->cmd.convert_src) {
	case TRIG_TIMER:
		conv_bits |= CASC | ITE;
		/* set conversion frequency */
		i8253_cascade_ns_to_timer_2div(TIMER_BASE, &(devpriv->divisor1),
					       &(devpriv->divisor2),
					       &(async->cmd.convert_arg),
					       async->cmd.
					       flags & TRIG_ROUND_MASK);
		if (das800_set_frequency(dev) < 0) {
			comedi_error(dev, "Error setting up counters");
			return -1;
		}
		break;
	case TRIG_EXT:
		break;
	default:
		break;
	}

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	outb(CONV_CONTROL, dev->iobase + DAS800_GAIN);	/* select dev->iobase + 2 to be conversion control register */
	outb(conv_bits, dev->iobase + DAS800_CONV_CONTROL);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);
	async->events = 0;
	enable_das800(dev);
	return 0;
}