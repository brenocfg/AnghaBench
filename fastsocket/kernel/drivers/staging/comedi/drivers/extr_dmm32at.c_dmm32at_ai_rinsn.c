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
struct comedi_subdevice {int n_chan; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMM32AT_AICONF ; 
 int /*<<< orphan*/  DMM32AT_AIHIGH ; 
 int /*<<< orphan*/  DMM32AT_AILOW ; 
 int /*<<< orphan*/  DMM32AT_AILSB ; 
 int /*<<< orphan*/  DMM32AT_AIMSB ; 
 int /*<<< orphan*/  DMM32AT_AIRBACK ; 
 int /*<<< orphan*/  DMM32AT_AISTAT ; 
 int /*<<< orphan*/  DMM32AT_CONV ; 
 int /*<<< orphan*/  DMM32AT_FIFOCNTRL ; 
 int DMM32AT_FIFORESET ; 
 unsigned char DMM32AT_STATUS ; 
 int ETIMEDOUT ; 
 int* dmm32at_rangebits ; 
 void* dmm_inb (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmm_outb (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int dmm32at_ai_rinsn(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	int n, i;
	unsigned int d;
	unsigned char status;
	unsigned short msb, lsb;
	unsigned char chan;
	int range;

	/* get the channel and range number */

	chan = CR_CHAN(insn->chanspec) & (s->n_chan - 1);
	range = CR_RANGE(insn->chanspec);

	/* printk("channel=0x%02x, range=%d\n",chan,range); */

	/* zero scan and fifo control and reset fifo */
	dmm_outb(dev, DMM32AT_FIFOCNTRL, DMM32AT_FIFORESET);

	/* write the ai channel range regs */
	dmm_outb(dev, DMM32AT_AILOW, chan);
	dmm_outb(dev, DMM32AT_AIHIGH, chan);
	/* set the range bits */
	dmm_outb(dev, DMM32AT_AICONF, dmm32at_rangebits[range]);

	/* wait for circuit to settle */
	for (i = 0; i < 40000; i++) {
		status = dmm_inb(dev, DMM32AT_AIRBACK);
		if ((status & DMM32AT_STATUS) == 0)
			break;
	}
	if (i == 40000) {
		printk("timeout\n");
		return -ETIMEDOUT;
	}

	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		dmm_outb(dev, DMM32AT_CONV, 0xff);
		/* wait for conversion to end */
		for (i = 0; i < 40000; i++) {
			status = dmm_inb(dev, DMM32AT_AISTAT);
			if ((status & DMM32AT_STATUS) == 0)
				break;
		}
		if (i == 40000) {
			printk("timeout\n");
			return -ETIMEDOUT;
		}

		/* read data */
		lsb = dmm_inb(dev, DMM32AT_AILSB);
		msb = dmm_inb(dev, DMM32AT_AIMSB);

		/* invert sign bit to make range unsigned, this is an
		   idiosyncracy of the diamond board, it return
		   conversions as a signed value, i.e. -32768 to
		   32767, flipping the bit and interpreting it as
		   signed gives you a range of 0 to 65535 which is
		   used by comedi */
		d = ((msb ^ 0x0080) << 8) + lsb;

		data[n] = d;
	}

	/* return the number of samples read/written */
	return n;
}