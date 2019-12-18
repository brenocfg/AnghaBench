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
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned int c_data; } ;

/* Variables and functions */
 scalar_t__ PARPORT_C ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int parport_insn_c(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	data[0] &= 0x0f;
	if (data[0]) {
		devpriv->c_data &= ~data[0];
		devpriv->c_data |= (data[0] & data[1]);

		outb(devpriv->c_data, dev->iobase + PARPORT_C);
	}

	data[1] = devpriv->c_data & 0xf;

	return 2;
}