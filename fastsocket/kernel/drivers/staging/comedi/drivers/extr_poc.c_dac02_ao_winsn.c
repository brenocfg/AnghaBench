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
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; scalar_t__ private; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC02_LSB (int) ; 
 scalar_t__ DAC02_MSB (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int dac02_ao_winsn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int temp;
	int chan;
	int output;

	chan = CR_CHAN(insn->chanspec);
	((unsigned int *)dev->private)[chan] = data[0];
	output = data[0];
#ifdef wrong
	/*  convert to complementary binary if range is bipolar */
	if ((CR_RANGE(insn->chanspec) & 0x2) == 0)
		output = ~output;
#endif
	temp = (output << 4) & 0xf0;
	outb(temp, dev->iobase + DAC02_LSB(chan));
	temp = (output >> 4) & 0xff;
	outb(temp, dev->iobase + DAC02_MSB(chan));

	return 1;
}