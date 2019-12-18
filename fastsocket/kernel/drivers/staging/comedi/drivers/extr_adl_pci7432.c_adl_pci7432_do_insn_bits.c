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
struct comedi_device {unsigned int iobase; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PCI7432_DO ; 
 int /*<<< orphan*/  outl (int,unsigned int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int adl_pci7432_do_insn_bits(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	printk("comedi: pci7432_do_insn_bits called\n");
	printk("comedi: data0: %8x data1: %8x\n", data[0], data[1]);

	if (insn->n != 2)
		return -EINVAL;

	if (data[0]) {
		s->state &= ~data[0];
		s->state |= (data[0] & data[1]);

		printk("comedi: out: %8x on iobase %4lx\n", s->state,
		       dev->iobase + PCI7432_DO);
		outl(s->state & 0xffffffff, dev->iobase + PCI7432_DO);
	}
	return 2;
}