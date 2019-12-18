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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned int* ao_readback; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ PCL812_DA1_HI ; 
 scalar_t__ PCL812_DA1_LO ; 
 scalar_t__ PCL812_DA2_HI ; 
 scalar_t__ PCL812_DA2_LO ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pcl812_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int chan = CR_CHAN(insn->chanspec);
	int i;

	for (i = 0; i < insn->n; i++) {
		outb((data[i] & 0xff),
		     dev->iobase + (chan ? PCL812_DA2_LO : PCL812_DA1_LO));
		outb((data[i] >> 8) & 0x0f,
		     dev->iobase + (chan ? PCL812_DA2_HI : PCL812_DA1_HI));
		devpriv->ao_readback[chan] = data[i];
	}

	return i;
}