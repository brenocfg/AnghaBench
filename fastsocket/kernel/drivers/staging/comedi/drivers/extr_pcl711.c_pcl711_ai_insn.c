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
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {scalar_t__ is_8112; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ PCL711_AD_HI ; 
 scalar_t__ PCL711_AD_LO ; 
 int PCL711_DRDY ; 
 scalar_t__ PCL711_MODE ; 
 scalar_t__ PCL711_SOFTTRIG ; 
 int PCL711_TIMEOUT ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pcl711_set_changain (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* this_board ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pcl711_ai_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int i, n;
	int hi, lo;

	pcl711_set_changain(dev, insn->chanspec);

	for (n = 0; n < insn->n; n++) {
		/*
		 *  Write the correct mode (software polling) and start polling by writing
		 *  to the trigger register
		 */
		outb(1, dev->iobase + PCL711_MODE);

		if (this_board->is_8112) {
		} else {
			outb(0, dev->iobase + PCL711_SOFTTRIG);
		}

		i = PCL711_TIMEOUT;
		while (--i) {
			hi = inb(dev->iobase + PCL711_AD_HI);
			if (!(hi & PCL711_DRDY))
				goto ok;
			udelay(1);
		}
		printk("comedi%d: pcl711: A/D timeout\n", dev->minor);
		return -ETIME;

ok:
		lo = inb(dev->iobase + PCL711_AD_LO);

		data[n] = ((hi & 0xf) << 8) | lo;
	}

	return n;
}