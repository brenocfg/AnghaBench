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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int registers; unsigned int* ao_readback; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (char,unsigned long) ; 

__attribute__((used)) static int ao_winsn(struct comedi_device *dev, struct comedi_subdevice *s,
		    struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);
	unsigned long offset = devpriv->registers + chan * 2;

	/* Writing a list of values to an AO channel is probably not
	 * very useful, but that's how the interface is defined. */
	for (i = 0; i < insn->n; i++) {
		/*  first, load the low byte */
		outb((char)(data[i] & 0x00ff), offset);
		/*  next, write the high byte -- only after this is written is
		   the channel voltage updated in the DAC, unless
		   we're in simultaneous xfer mode (jumper on card)
		   then a rinsn is necessary to actually update the DAC --
		   see ao_rinsn() below... */
		outb((char)(data[i] >> 8 & 0x00ff), offset + 1);

		/* for testing only.. the actual rinsn SHOULD do an inw!
		   (see the stuff about simultaneous XFER mode on this board) */
		devpriv->ao_readback[chan] = data[i];
	}

	/* return the number of samples read/written */
	return i;
}