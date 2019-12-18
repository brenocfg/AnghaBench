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
 int DT2811_ADBUSY ; 
 scalar_t__ DT2811_ADCSR ; 
 scalar_t__ DT2811_ADDATHI ; 
 scalar_t__ DT2811_ADDATLO ; 
 scalar_t__ DT2811_ADGCR ; 
 int DT2811_TIMEOUT ; 
 int ETIME ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int dt2811_ai_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int chan = CR_CHAN(insn->chanspec);
	int timeout = DT2811_TIMEOUT;
	int i;

	for (i = 0; i < insn->n; i++) {
		outb(chan, dev->iobase + DT2811_ADGCR);

		while (timeout
		       && inb(dev->iobase + DT2811_ADCSR) & DT2811_ADBUSY)
			timeout--;
		if (!timeout)
			return -ETIME;

		data[i] = inb(dev->iobase + DT2811_ADDATLO);
		data[i] |= inb(dev->iobase + DT2811_ADDATHI) << 8;
		data[i] &= 0xfff;
	}

	return i;
}