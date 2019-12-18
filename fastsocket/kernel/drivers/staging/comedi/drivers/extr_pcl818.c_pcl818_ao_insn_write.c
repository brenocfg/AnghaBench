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
 scalar_t__ PCL718_DA2_HI ; 
 scalar_t__ PCL718_DA2_LO ; 
 scalar_t__ PCL818_DA_HI ; 
 scalar_t__ PCL818_DA_LO ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pcl818_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int n;
	int chan = CR_CHAN(insn->chanspec);

	for (n = 0; n < insn->n; n++) {
		devpriv->ao_readback[chan] = data[n];
		outb((data[n] & 0x000f) << 4, dev->iobase +
		     (chan ? PCL718_DA2_LO : PCL818_DA_LO));
		outb((data[n] & 0x0ff0) >> 4, dev->iobase +
		     (chan ? PCL718_DA2_HI : PCL818_DA_HI));
	}

	return n;
}