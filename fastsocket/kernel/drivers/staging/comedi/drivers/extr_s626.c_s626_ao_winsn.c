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
typedef  size_t uint16_t ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
typedef  scalar_t__ int16_t ;
struct TYPE_2__ {unsigned int* ao_readback; } ;

/* Variables and functions */
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDAC (struct comedi_device*,size_t,scalar_t__) ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static int s626_ao_winsn(struct comedi_device *dev, struct comedi_subdevice *s,
			 struct comedi_insn *insn, unsigned int *data)
{

	int i;
	uint16_t chan = CR_CHAN(insn->chanspec);
	int16_t dacdata;

	for (i = 0; i < insn->n; i++) {
		dacdata = (int16_t) data[i];
		devpriv->ao_readback[CR_CHAN(insn->chanspec)] = data[i];
		dacdata -= (0x1fff);

		SetDAC(dev, chan, dacdata);
	}

	return i;
}