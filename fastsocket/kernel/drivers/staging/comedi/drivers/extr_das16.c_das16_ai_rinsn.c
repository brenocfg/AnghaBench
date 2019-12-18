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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_4__ {int control_state; } ;
struct TYPE_3__ {size_t ai_pg; int ai_nbits; } ;

/* Variables and functions */
 int BUSY ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS16_AI_LSB ; 
 scalar_t__ DAS16_AI_MSB ; 
 scalar_t__ DAS16_CONTROL ; 
 scalar_t__ DAS16_GAIN ; 
 int DAS16_INTE ; 
 scalar_t__ DAS16_MUX ; 
 scalar_t__ DAS16_STATUS ; 
 int DAS16_TIMEOUT ; 
 scalar_t__ DAS16_TRIG ; 
 int DMA_ENABLE ; 
 int ETIME ; 
 int PACING_MASK ; 
 int** das16_gainlists ; 
 size_t das16_pg_none ; 
 TYPE_2__* devpriv ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int das16_ai_rinsn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int i, n;
	int range;
	int chan;
	int msb, lsb;

	/*  disable interrupts and pacing */
	devpriv->control_state &= ~DAS16_INTE & ~DMA_ENABLE & ~PACING_MASK;
	outb(devpriv->control_state, dev->iobase + DAS16_CONTROL);

	/* set multiplexer */
	chan = CR_CHAN(insn->chanspec);
	chan |= CR_CHAN(insn->chanspec) << 4;
	outb(chan, dev->iobase + DAS16_MUX);

	/* set gain */
	if (thisboard->ai_pg != das16_pg_none) {
		range = CR_RANGE(insn->chanspec);
		outb((das16_gainlists[thisboard->ai_pg])[range],
		     dev->iobase + DAS16_GAIN);
	}

	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		outb_p(0, dev->iobase + DAS16_TRIG);

		for (i = 0; i < DAS16_TIMEOUT; i++) {
			if (!(inb(dev->iobase + DAS16_STATUS) & BUSY))
				break;
		}
		if (i == DAS16_TIMEOUT) {
			printk("das16: timeout\n");
			return -ETIME;
		}
		msb = inb(dev->iobase + DAS16_AI_MSB);
		lsb = inb(dev->iobase + DAS16_AI_LSB);
		if (thisboard->ai_nbits == 12) {
			data[n] = ((lsb >> 4) & 0xf) | (msb << 4);
		} else {
			data[n] = lsb | (msb << 8);
		}
	}

	return n;
}