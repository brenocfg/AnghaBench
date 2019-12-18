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
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {scalar_t__ do_hi; scalar_t__ do_lo; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int pcl726_do_insn_bits(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	if (insn->n != 2)
		return -EINVAL;

	if (data[0]) {
		s->state &= ~data[0];
		s->state |= data[0] & data[1];
	}
	if (data[1] & 0x00ff)
		outb(s->state & 0xff, dev->iobase + this_board->do_lo);
	if (data[1] & 0xff00)
		outb((s->state >> 8), dev->iobase + this_board->do_hi);

	data[1] = s->state;

	return 2;
}