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
 int ADC_MODE_NORMAL ; 
 scalar_t__ AIO12_8_ADC ; 
 scalar_t__ AIO12_8_STATUS ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int STATUS_ADC_EOC ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int inb (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int aio_aio12_8_ai_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int n;
	unsigned char control =
	    ADC_MODE_NORMAL |
	    (CR_RANGE(insn->chanspec) << 3) | CR_CHAN(insn->chanspec);

	/* read status to clear EOC latch */
	inb(dev->iobase + AIO12_8_STATUS);

	for (n = 0; n < insn->n; n++) {
		int timeout = 5;

		/*  Setup and start conversion */
		outb(control, dev->iobase + AIO12_8_ADC);

		/*  Wait for conversion to complete */
		while (timeout &&
		       !(inb(dev->iobase + AIO12_8_STATUS) & STATUS_ADC_EOC)) {
			timeout--;
			printk("timeout %d\n", timeout);
			udelay(1);
		}
		if (timeout == 0) {
			comedi_error(dev, "ADC timeout");
			return -EIO;
		}

		data[n] = inw(dev->iobase + AIO12_8_ADC) & 0x0FFF;
	}
	return n;
}