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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int status1; int status2; } ;

/* Variables and functions */
 int AREF_DIFF ; 
 int CR_AREF (int /*<<< orphan*/ ) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int ETIME ; 
 int TIMEOUT ; 
 TYPE_1__* devpriv ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int das16cs_ai_rinsn(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int to;
	int aref;
	int range;
	int chan;
	static int range_bits[] = { 0x800, 0x000, 0x100, 0x200 };

	chan = CR_CHAN(insn->chanspec);
	aref = CR_AREF(insn->chanspec);
	range = CR_RANGE(insn->chanspec);

	outw(chan, dev->iobase + 2);

	devpriv->status1 &= ~0xf320;
	devpriv->status1 |= (aref == AREF_DIFF) ? 0 : 0x0020;
	outw(devpriv->status1, dev->iobase + 4);

	devpriv->status2 &= ~0xff00;
	devpriv->status2 |= range_bits[range];
	outw(devpriv->status2, dev->iobase + 6);

	for (i = 0; i < insn->n; i++) {
		outw(0, dev->iobase);

#define TIMEOUT 1000
		for (to = 0; to < TIMEOUT; to++) {
			if (inw(dev->iobase + 4) & 0x0080)
				break;
		}
		if (to == TIMEOUT) {
			printk("cb_das16_cs: ai timeout\n");
			return -ETIME;
		}
		data[i] = (unsigned short)inw(dev->iobase + 0);
	}

	return i;
}