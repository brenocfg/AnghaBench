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
struct comedi_subdevice {int io_bits; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DT2817_CR ; 
 int EINVAL ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int dt2817_dio_insn_config(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
	int mask;
	int chan;
	int oe = 0;

	if (insn->n != 1)
		return -EINVAL;

	chan = CR_CHAN(insn->chanspec);
	if (chan < 8) {
		mask = 0xff;
	} else if (chan < 16) {
		mask = 0xff00;
	} else if (chan < 24) {
		mask = 0xff0000;
	} else
		mask = 0xff000000;
	if (data[0])
		s->io_bits |= mask;
	else
		s->io_bits &= ~mask;

	if (s->io_bits & 0x000000ff)
		oe |= 0x1;
	if (s->io_bits & 0x0000ff00)
		oe |= 0x2;
	if (s->io_bits & 0x00ff0000)
		oe |= 0x4;
	if (s->io_bits & 0xff000000)
		oe |= 0x8;

	outb(oe, dev->iobase + DT2817_CR);

	return 1;
}