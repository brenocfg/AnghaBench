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
struct comedi_device {unsigned long iobase; } ;
struct TYPE_2__ {unsigned int* ao_readback; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inb (unsigned long) ; 
 int /*<<< orphan*/  outb (unsigned int,unsigned long) ; 

__attribute__((used)) static int fl512_ao_insn(struct comedi_device *dev,
			 struct comedi_subdevice *s, struct comedi_insn *insn,
			 unsigned int *data)
{
	int n;
	int chan = CR_CHAN(insn->chanspec);	/* get chan to write */
	unsigned long iobase = dev->iobase;	/* get base address  */

	for (n = 0; n < insn->n; n++) {	/* write n data set */
		outb(data[n] & 0x0ff, iobase + 4 + 2 * chan);	/* write low byte   */
		outb((data[n] & 0xf00) >> 8, iobase + 4 + 2 * chan);	/* write high byte  */
		inb(iobase + 4 + 2 * chan);	/* trig */

		devpriv->ao_readback[chan] = data[n];
	}
	return n;
}