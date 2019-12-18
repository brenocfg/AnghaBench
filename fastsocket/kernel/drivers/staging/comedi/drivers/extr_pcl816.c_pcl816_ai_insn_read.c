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
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EIO ; 
 scalar_t__ PCL816_AD_HI ; 
 scalar_t__ PCL816_AD_LO ; 
 scalar_t__ PCL816_CLRINT ; 
 scalar_t__ PCL816_CONTROL ; 
 scalar_t__ PCL816_MUX ; 
 scalar_t__ PCL816_RANGE ; 
 scalar_t__ PCL816_STATUS ; 
 int PCL816_STATUS_DRDY_MASK ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pcl816_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int n;
	int timeout;

	DPRINTK("mode 0 analog input\n");
	/*  software trigger, DMA and INT off */
	outb(0, dev->iobase + PCL816_CONTROL);
	/*  clear INT (conversion end) flag */
	outb(0, dev->iobase + PCL816_CLRINT);

	/*  Set the input channel */
	outb(CR_CHAN(insn->chanspec) & 0xf, dev->iobase + PCL816_MUX);
	outb(CR_RANGE(insn->chanspec), dev->iobase + PCL816_RANGE);	/* select gain */

	for (n = 0; n < insn->n; n++) {

		outb(0, dev->iobase + PCL816_AD_LO);	/* start conversion */

		timeout = 100;
		while (timeout--) {
			if (!(inb(dev->iobase + PCL816_STATUS) &
			      PCL816_STATUS_DRDY_MASK)) {
				/*  return read value */
				data[n] =
				    ((inb(dev->iobase +
					  PCL816_AD_HI) << 8) |
				     (inb(dev->iobase + PCL816_AD_LO)));

				outb(0, dev->iobase + PCL816_CLRINT);	/* clear INT (conversion end) flag */
				break;
			}
			udelay(1);
		}
		/*  Return timeout error */
		if (!timeout) {
			comedi_error(dev, "A/D insn timeout\n");
			data[0] = 0;
			outb(0, dev->iobase + PCL816_CLRINT);	/* clear INT (conversion end) flag */
			return -EIO;
		}

	}
	return n;
}