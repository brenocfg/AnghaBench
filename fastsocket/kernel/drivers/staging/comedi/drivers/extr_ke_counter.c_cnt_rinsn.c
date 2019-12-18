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
struct comedi_subdevice {int maxdata; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned char inb (scalar_t__) ; 

__attribute__((used)) static int cnt_rinsn(struct comedi_device *dev,
		     struct comedi_subdevice *s, struct comedi_insn *insn,
		     unsigned int *data)
{
	unsigned char a0, a1, a2, a3, a4;
	int chan = CR_CHAN(insn->chanspec);
	int result;

	a0 = inb(dev->iobase + chan * 0x20);
	a1 = inb(dev->iobase + chan * 0x20 + 0x04);
	a2 = inb(dev->iobase + chan * 0x20 + 0x08);
	a3 = inb(dev->iobase + chan * 0x20 + 0x0c);
	a4 = inb(dev->iobase + chan * 0x20 + 0x10);

	result = (a1 + (a2 * 256) + (a3 * 65536));
	if (a4 > 0)
		result = result - s->maxdata;

	*data = (unsigned int)result;

	/* return the number of samples read */
	return 1;
}