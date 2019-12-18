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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCI7432_DI ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int adl_pci7432_di_insn_bits(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	printk("comedi: pci7432_di_insn_bits called\n");
	printk("comedi: data0: %8x data1: %8x\n", data[0], data[1]);

	if (insn->n != 2)
		return -EINVAL;

	data[1] = inl(dev->iobase + PCI7432_DI) & 0xffffffff;
	printk("comedi: data1 %8x\n", data[1]);

	return 2;
}