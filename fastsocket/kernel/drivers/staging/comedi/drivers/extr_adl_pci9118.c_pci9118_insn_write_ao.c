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
struct TYPE_2__ {unsigned int* ao_data; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int PCI9118_DA1 ; 
 int PCI9118_DA2 ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pci9118_insn_write_ao(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	int n, chanreg, ch;

	ch = CR_CHAN(insn->chanspec);
	if (ch) {
		chanreg = PCI9118_DA2;
	} else {
		chanreg = PCI9118_DA1;
	}

	for (n = 0; n < insn->n; n++) {
		outl(data[n], dev->iobase + chanreg);
		devpriv->ao_data[ch] = data[n];
	}

	return n;
}