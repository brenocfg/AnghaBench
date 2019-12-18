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
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;
struct TYPE_2__ {int resolution; } ;

/* Variables and functions */
 int ADC ; 
 int AREF_COMMON ; 
 int AREF_DIFF ; 
 int CMEN ; 
 int CR_AREF (int /*<<< orphan*/ ) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int CVEN ; 
 scalar_t__ DAS1800_CONTROL_A ; 
 scalar_t__ DAS1800_CONTROL_C ; 
 scalar_t__ DAS1800_FIFO ; 
 scalar_t__ DAS1800_QRAM ; 
 scalar_t__ DAS1800_QRAM_ADDRESS ; 
 scalar_t__ DAS1800_SELECT ; 
 scalar_t__ DAS1800_STATUS ; 
 int ETIME ; 
 int FFEN ; 
 int FNE ; 
 int QRAM ; 
 int SD ; 
 int UB ; 
 int UNIPOLAR ; 
 int UQEN ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int inb (scalar_t__) ; 
 short inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int das1800_ai_rinsn(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	int i, n;
	int chan, range, aref, chan_range;
	int timeout = 1000;
	short dpnt;
	int conv_flags = 0;
	unsigned long irq_flags;

	/* set up analog reference and unipolar / bipolar mode */
	aref = CR_AREF(insn->chanspec);
	conv_flags |= UQEN;
	if (aref != AREF_DIFF)
		conv_flags |= SD;
	if (aref == AREF_COMMON)
		conv_flags |= CMEN;
	/* if a unipolar range was selected */
	if (CR_RANGE(insn->chanspec) & UNIPOLAR)
		conv_flags |= UB;

	outb(conv_flags, dev->iobase + DAS1800_CONTROL_C);	/* software conversion enabled */
	outb(CVEN, dev->iobase + DAS1800_STATUS);	/* enable conversions */
	outb(0x0, dev->iobase + DAS1800_CONTROL_A);	/* reset fifo */
	outb(FFEN, dev->iobase + DAS1800_CONTROL_A);

	chan = CR_CHAN(insn->chanspec);
	/* mask of unipolar/bipolar bit from range */
	range = CR_RANGE(insn->chanspec) & 0x3;
	chan_range = chan | (range << 8);
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	outb(QRAM, dev->iobase + DAS1800_SELECT);	/* select QRAM for baseAddress + 0x0 */
	outb(0x0, dev->iobase + DAS1800_QRAM_ADDRESS);	/* set QRAM address start */
	outw(chan_range, dev->iobase + DAS1800_QRAM);
	outb(0x0, dev->iobase + DAS1800_QRAM_ADDRESS);	/*finish write to QRAM */
	outb(ADC, dev->iobase + DAS1800_SELECT);	/* select ADC for baseAddress + 0x0 */

	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		outb(0, dev->iobase + DAS1800_FIFO);
		for (i = 0; i < timeout; i++) {
			if (inb(dev->iobase + DAS1800_STATUS) & FNE)
				break;
		}
		if (i == timeout) {
			comedi_error(dev, "timeout");
			return -ETIME;
		}
		dpnt = inw(dev->iobase + DAS1800_FIFO);
		/* shift data to offset binary for bipolar ranges */
		if ((conv_flags & UB) == 0)
			dpnt += 1 << (thisboard->resolution - 1);
		data[n] = dpnt;
	}
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	return n;
}