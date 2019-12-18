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
struct comedi_subdevice {unsigned int state; unsigned int io_bits; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ PCI20000_DIO_0 ; 
 scalar_t__ PCI20000_DIO_1 ; 
 scalar_t__ PCI20000_DIO_2 ; 
 scalar_t__ PCI20000_DIO_3 ; 
 TYPE_1__* devpriv ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pci20xxx_dio_insn_bits(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
	unsigned int mask = data[0];

	s->state &= ~mask;
	s->state |= (mask & data[1]);

	mask &= s->io_bits;
	if (mask & 0x000000ff)
		writeb((s->state >> 0) & 0xff,
		       devpriv->ioaddr + PCI20000_DIO_0);
	if (mask & 0x0000ff00)
		writeb((s->state >> 8) & 0xff,
		       devpriv->ioaddr + PCI20000_DIO_1);
	if (mask & 0x00ff0000)
		writeb((s->state >> 16) & 0xff,
		       devpriv->ioaddr + PCI20000_DIO_2);
	if (mask & 0xff000000)
		writeb((s->state >> 24) & 0xff,
		       devpriv->ioaddr + PCI20000_DIO_3);

	data[1] = readb(devpriv->ioaddr + PCI20000_DIO_0);
	data[1] |= readb(devpriv->ioaddr + PCI20000_DIO_1) << 8;
	data[1] |= readb(devpriv->ioaddr + PCI20000_DIO_2) << 16;
	data[1] |= readb(devpriv->ioaddr + PCI20000_DIO_3) << 24;

	return 2;
}