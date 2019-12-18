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
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCL711_DO_HI ; 
 scalar_t__ PCL711_DO_LO ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int pcl711_do_insn_bits(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	if (insn->n != 2)
		return -EINVAL;

	if (data[0]) {
		s->state &= ~data[0];
		s->state |= data[0] & data[1];
	}
	if (data[0] & 0x00ff)
		outb(s->state & 0xff, dev->iobase + PCL711_DO_LO);
	if (data[0] & 0xff00)
		outb((s->state >> 8), dev->iobase + PCL711_DO_HI);

	data[1] = s->state;

	return 2;
}