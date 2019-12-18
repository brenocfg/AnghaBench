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
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ dio_counter_iobase; } ;

/* Variables and functions */
 scalar_t__ DO_REG ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int do_wbits(struct comedi_device *dev, struct comedi_subdevice *s,
		    struct comedi_insn *insn, unsigned int *data)
{
	data[0] &= 0xf;
	/*  zero bits we are going to change */
	s->state &= ~data[0];
	/*  set new bits */
	s->state |= data[0] & data[1];

	writeb(s->state, priv(dev)->dio_counter_iobase + DO_REG);

	data[1] = s->state;

	return 2;
}