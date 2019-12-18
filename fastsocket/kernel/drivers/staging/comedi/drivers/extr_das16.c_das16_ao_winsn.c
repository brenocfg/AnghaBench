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
struct TYPE_2__ {int ao_nbits; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS16_AO_LSB (int) ; 
 scalar_t__ DAS16_AO_MSB (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int das16_ao_winsn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int lsb, msb;
	int chan;

	chan = CR_CHAN(insn->chanspec);

	for (i = 0; i < insn->n; i++) {
		if (thisboard->ao_nbits == 12) {
			lsb = (data[i] << 4) & 0xff;
			msb = (data[i] >> 4) & 0xff;
		} else {
			lsb = data[i] & 0xff;
			msb = (data[i] >> 8) & 0xff;
		}
		outb(lsb, dev->iobase + DAS16_AO_LSB(chan));
		outb(msb, dev->iobase + DAS16_AO_MSB(chan));
	}

	return i;
}