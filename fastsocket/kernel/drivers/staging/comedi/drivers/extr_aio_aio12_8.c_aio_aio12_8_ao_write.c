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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int iobase; } ;
struct TYPE_2__ {unsigned int* ao_readback; } ;

/* Variables and functions */
 int AIO12_8_DAC_0 ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned long DAC_ENABLE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned int,unsigned long) ; 

__attribute__((used)) static int aio_aio12_8_ao_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);
	unsigned long port = dev->iobase + AIO12_8_DAC_0 + (2 * chan);

	/* enable DACs */
	outb(0x01, dev->iobase + DAC_ENABLE);

	for (i = 0; i < insn->n; i++) {
		outb(data[i] & 0xFF, port);	/*  LSB */
		outb((data[i] >> 8) & 0x0F, port + 1);	/*  MSB */
		devpriv->ao_readback[chan] = data[i];
	}
	return insn->n;
}