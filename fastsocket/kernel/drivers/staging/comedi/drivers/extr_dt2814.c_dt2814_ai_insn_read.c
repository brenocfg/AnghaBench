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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DT2814_CSR ; 
 scalar_t__ DT2814_DATA ; 
 int DT2814_FINISH ; 
 int DT2814_TIMEOUT ; 
 int ETIMEDOUT ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dt2814_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int n, i, hi, lo;
	int chan;
	int status = 0;

	for (n = 0; n < insn->n; n++) {
		chan = CR_CHAN(insn->chanspec);

		outb(chan, dev->iobase + DT2814_CSR);
		for (i = 0; i < DT2814_TIMEOUT; i++) {
			status = inb(dev->iobase + DT2814_CSR);
			printk("dt2814: status: %02x\n", status);
			udelay(10);
			if (status & DT2814_FINISH)
				break;
		}
		if (i >= DT2814_TIMEOUT) {
			printk("dt2814: status: %02x\n", status);
			return -ETIMEDOUT;
		}

		hi = inb(dev->iobase + DT2814_DATA);
		lo = inb(dev->iobase + DT2814_DATA);

		data[n] = (hi << 4) | (lo >> 4);
	}

	return n;
}