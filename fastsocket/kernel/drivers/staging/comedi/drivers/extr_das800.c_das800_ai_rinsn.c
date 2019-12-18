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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  spinlock; } ;
struct TYPE_4__ {int do_bits; } ;
struct TYPE_3__ {int resolution; } ;

/* Variables and functions */
 int BUSY ; 
 int CONTROL1 ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS800_CONTROL1 ; 
 scalar_t__ DAS800_GAIN ; 
 scalar_t__ DAS800_LSB ; 
 scalar_t__ DAS800_MSB ; 
 scalar_t__ DAS800_STATUS ; 
 int ETIME ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  disable_das800 (struct comedi_device*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* thisboard ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int das800_ai_rinsn(struct comedi_device *dev,
			   struct comedi_subdevice *s, struct comedi_insn *insn,
			   unsigned int *data)
{
	int i, n;
	int chan;
	int range;
	int lsb, msb;
	int timeout = 1000;
	unsigned long irq_flags;

	disable_das800(dev);	/* disable hardware conversions (enables software conversions) */

	/* set multiplexer */
	chan = CR_CHAN(insn->chanspec);

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	outb(CONTROL1, dev->iobase + DAS800_GAIN);	/* select dev->iobase + 2 to be control register 1 */
	outb(chan | devpriv->do_bits, dev->iobase + DAS800_CONTROL1);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	/* set gain / range */
	range = CR_RANGE(insn->chanspec);
	if (thisboard->resolution == 12 && range)
		range += 0x7;
	range &= 0xf;
	outb(range, dev->iobase + DAS800_GAIN);

	udelay(5);

	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		outb_p(0, dev->iobase + DAS800_MSB);

		for (i = 0; i < timeout; i++) {
			if (!(inb(dev->iobase + DAS800_STATUS) & BUSY))
				break;
		}
		if (i == timeout) {
			comedi_error(dev, "timeout");
			return -ETIME;
		}
		lsb = inb(dev->iobase + DAS800_LSB);
		msb = inb(dev->iobase + DAS800_MSB);
		if (thisboard->resolution == 12) {
			data[n] = (lsb >> 4) & 0xff;
			data[n] |= (msb << 4);
		} else {
			data[n] = (msb << 8) | lsb;
		}
	}

	return n;
}