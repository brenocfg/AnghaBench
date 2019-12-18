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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int control_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS16M1_CLEAR_INTR ; 
 scalar_t__ DAS16M1_CS ; 
 scalar_t__ DAS16M1_INTR_CONTROL ; 
 scalar_t__ DAS16M1_QUEUE_ADDR ; 
 scalar_t__ DAS16M1_QUEUE_DATA ; 
 int ETIME ; 
 int INTE ; 
 int IRQDATA ; 
 int PACER_MASK ; 
 int Q_CHAN (int /*<<< orphan*/ ) ; 
 int Q_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 unsigned int munge_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int das16m1_ai_rinsn(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	int i, n;
	int byte;
	const int timeout = 1000;

	/* disable interrupts and internal pacer */
	devpriv->control_state &= ~INTE & ~PACER_MASK;
	outb(devpriv->control_state, dev->iobase + DAS16M1_INTR_CONTROL);

	/* setup channel/gain queue */
	outb(0, dev->iobase + DAS16M1_QUEUE_ADDR);
	byte =
	    Q_CHAN(CR_CHAN(insn->chanspec)) | Q_RANGE(CR_RANGE(insn->chanspec));
	outb(byte, dev->iobase + DAS16M1_QUEUE_DATA);

	for (n = 0; n < insn->n; n++) {
		/* clear IRQDATA bit */
		outb(0, dev->iobase + DAS16M1_CLEAR_INTR);
		/* trigger conversion */
		outb(0, dev->iobase);

		for (i = 0; i < timeout; i++) {
			if (inb(dev->iobase + DAS16M1_CS) & IRQDATA)
				break;
		}
		if (i == timeout) {
			comedi_error(dev, "timeout");
			return -ETIME;
		}
		data[n] = munge_sample(inw(dev->iobase));
	}

	return n;
}