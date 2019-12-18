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
struct comedi_subdevice {unsigned int state; unsigned int io_bits; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DT2817_DATA ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int dt2817_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	unsigned int changed;

	/* It's questionable whether it is more important in
	 * a driver like this to be deterministic or fast.
	 * We choose fast. */

	if (data[0]) {
		changed = s->state;
		s->state &= ~data[0];
		s->state |= (data[0] & data[1]);
		changed ^= s->state;
		changed &= s->io_bits;
		if (changed & 0x000000ff)
			outb(s->state & 0xff, dev->iobase + DT2817_DATA + 0);
		if (changed & 0x0000ff00)
			outb((s->state >> 8) & 0xff,
			     dev->iobase + DT2817_DATA + 1);
		if (changed & 0x00ff0000)
			outb((s->state >> 16) & 0xff,
			     dev->iobase + DT2817_DATA + 2);
		if (changed & 0xff000000)
			outb((s->state >> 24) & 0xff,
			     dev->iobase + DT2817_DATA + 3);
	}
	data[1] = inb(dev->iobase + DT2817_DATA + 0);
	data[1] |= (inb(dev->iobase + DT2817_DATA + 1) << 8);
	data[1] |= (inb(dev->iobase + DT2817_DATA + 2) << 16);
	data[1] |= (inb(dev->iobase + DT2817_DATA + 3) << 24);

	return 2;
}