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
struct TYPE_2__ {short cfg1; unsigned int* ao_readback; } ;

/* Variables and functions */
 scalar_t__ ATAO_CFG1 ; 
 scalar_t__ ATAO_DACn (int) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 short GRP2WR ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (short,scalar_t__) ; 

__attribute__((used)) static int atao_ao_winsn(struct comedi_device *dev, struct comedi_subdevice *s,
			 struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);
	short bits;

	for (i = 0; i < insn->n; i++) {
		bits = data[i] - 0x800;
		if (chan == 0) {
			devpriv->cfg1 |= GRP2WR;
			outw(devpriv->cfg1, dev->iobase + ATAO_CFG1);
		}
		outw(bits, dev->iobase + ATAO_DACn(chan));
		if (chan == 0) {
			devpriv->cfg1 &= ~GRP2WR;
			outw(devpriv->cfg1, dev->iobase + ATAO_CFG1);
		}
		devpriv->ao_readback[chan] = data[i];
	}

	return i;
}