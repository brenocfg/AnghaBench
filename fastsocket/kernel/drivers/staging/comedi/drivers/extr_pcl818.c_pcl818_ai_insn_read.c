#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_RANGE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ PCL818_AD_HI ; 
 scalar_t__ PCL818_AD_LO ; 
 scalar_t__ PCL818_CLRINT ; 
 scalar_t__ PCL818_CONTROL ; 
 scalar_t__ PCL818_MUX ; 
 scalar_t__ PCL818_RANGE ; 
 scalar_t__ PCL818_STATUS ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/ * muxonechan ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pcl818_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int n;
	int timeout;

	/* software trigger, DMA and INT off */
	outb(0, dev->iobase + PCL818_CONTROL);

	/* select channel */
	outb(muxonechan[CR_CHAN(insn->chanspec)], dev->iobase + PCL818_MUX);

	/* select gain */
	outb(CR_RANGE(insn->chanspec), dev->iobase + PCL818_RANGE);

	for (n = 0; n < insn->n; n++) {

		/* clear INT (conversion end) flag */
		outb(0, dev->iobase + PCL818_CLRINT);

		/* start conversion */
		outb(0, dev->iobase + PCL818_AD_LO);

		timeout = 100;
		while (timeout--) {
			if (inb(dev->iobase + PCL818_STATUS) & 0x10)
				goto conv_finish;
			udelay(1);
		}
		comedi_error(dev, "A/D insn timeout");
		/* clear INT (conversion end) flag */
		outb(0, dev->iobase + PCL818_CLRINT);
		return -EIO;

conv_finish:
		data[n] = ((inb(dev->iobase + PCL818_AD_HI) << 4) |
			   (inb(dev->iobase + PCL818_AD_LO) >> 4));
	}

	return n;
}