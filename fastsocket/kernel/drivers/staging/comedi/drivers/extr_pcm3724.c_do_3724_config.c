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
struct comedi_device {unsigned long iobase; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int CR_A_IO ; 
 int CR_B_IO ; 
 int CR_CW ; 
 int CR_C_IO ; 
 unsigned long SIZE_8255 ; 
 unsigned long _8255_CR ; 
 int compute_buffer (int,int,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 

__attribute__((used)) static void do_3724_config(struct comedi_device *dev,
			   struct comedi_subdevice *s, int chanspec)
{
	int config;
	int buffer_config;
	unsigned long port_8255_cfg;

	config = CR_CW;
	buffer_config = 0;

	/* 1 in io_bits indicates output, 1 in config indicates input */
	if (!(s->io_bits & 0x0000ff)) {
		config |= CR_A_IO;
	}
	if (!(s->io_bits & 0x00ff00)) {
		config |= CR_B_IO;
	}
	if (!(s->io_bits & 0xff0000)) {
		config |= CR_C_IO;
	}

	buffer_config = compute_buffer(0, 0, dev->subdevices);
	buffer_config = compute_buffer(buffer_config, 1, (dev->subdevices) + 1);

	if (s == dev->subdevices) {
		port_8255_cfg = dev->iobase + _8255_CR;
	} else {
		port_8255_cfg = dev->iobase + SIZE_8255 + _8255_CR;
	}
	outb(buffer_config, dev->iobase + 8);	/* update buffer register */
	/* printk("pcm3724 buffer_config (%lx) %d, %x\n", dev->iobase + _8255_CR, chanspec, buffer_config); */
	outb(config, port_8255_cfg);
}