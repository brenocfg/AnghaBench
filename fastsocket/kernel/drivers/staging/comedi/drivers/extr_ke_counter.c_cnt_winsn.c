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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int cnt_winsn(struct comedi_device *dev,
		     struct comedi_subdevice *s, struct comedi_insn *insn,
		     unsigned int *data)
{
	int chan = CR_CHAN(insn->chanspec);

	outb((unsigned char)((data[0] >> 24) & 0xff),
	     dev->iobase + chan * 0x20 + 0x10);
	outb((unsigned char)((data[0] >> 16) & 0xff),
	     dev->iobase + chan * 0x20 + 0x0c);
	outb((unsigned char)((data[0] >> 8) & 0xff),
	     dev->iobase + chan * 0x20 + 0x08);
	outb((unsigned char)((data[0] >> 0) & 0xff),
	     dev->iobase + chan * 0x20 + 0x04);

	/* return the number of samples written */
	return 1;
}