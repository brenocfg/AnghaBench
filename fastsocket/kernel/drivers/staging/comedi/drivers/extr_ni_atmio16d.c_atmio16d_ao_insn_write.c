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
struct TYPE_2__ {unsigned int* ao_readback; int /*<<< orphan*/  dac1_coding; int /*<<< orphan*/  dac0_coding; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC0_REG ; 
 scalar_t__ DAC1_REG ; 
 int EINVAL ; 
 int /*<<< orphan*/  dac_2comp ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int atmio16d_ao_insn_write(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int chan;
	int d;
#ifdef DEBUG1
	printk("atmio16d_ao_insn_write\n");
#endif

	chan = CR_CHAN(insn->chanspec);

	for (i = 0; i < insn->n; i++) {
		d = data[i];
		switch (chan) {
		case 0:
			if (devpriv->dac0_coding == dac_2comp) {
				d ^= 0x800;
			}
			outw(d, dev->iobase + DAC0_REG);
			break;
		case 1:
			if (devpriv->dac1_coding == dac_2comp) {
				d ^= 0x800;
			}
			outw(d, dev->iobase + DAC1_REG);
			break;
		default:
			return -EINVAL;
		}
		devpriv->ao_readback[chan] = data[i];
	}
	return i;
}