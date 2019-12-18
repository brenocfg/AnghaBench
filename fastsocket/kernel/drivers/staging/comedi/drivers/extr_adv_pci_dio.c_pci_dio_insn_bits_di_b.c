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
struct diosubd_data {int regs; scalar_t__ addr; } ;
struct comedi_subdevice {scalar_t__ private; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int inb (scalar_t__) ; 

__attribute__((used)) static int pci_dio_insn_bits_di_b(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
	const struct diosubd_data *d = (const struct diosubd_data *)s->private;
	int i;

	data[1] = 0;
	for (i = 0; i < d->regs; i++) {
		data[1] |= inb(dev->iobase + d->addr + i) << (8 * i);
	}

	return 2;
}