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
struct comedi_device {unsigned long iobase; } ;

/* Variables and functions */
 char CR_CHAN (int /*<<< orphan*/ ) ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (char,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fl512_ai_insn(struct comedi_device *dev,
			 struct comedi_subdevice *s, struct comedi_insn *insn,
			 unsigned int *data)
{
	int n;
	unsigned int lo_byte, hi_byte;
	char chan = CR_CHAN(insn->chanspec);
	unsigned long iobase = dev->iobase;

	for (n = 0; n < insn->n; n++) {	/* sample n times on selected channel */
		/* XXX probably can move next step out of for() loop -- will make
		 * AI a little bit faster. */
		outb(chan, iobase + 2);	/* select chan */
		outb(0, iobase + 3);	/* start conversion */
		/* XXX should test "done" flag instead of delay */
		udelay(30);	/* sleep 30 usec */
		lo_byte = inb(iobase + 2);	/* low 8 byte */
		hi_byte = inb(iobase + 3) & 0xf;	/* high 4 bit and mask */
		data[n] = lo_byte + (hi_byte << 8);
	}
	return n;
}