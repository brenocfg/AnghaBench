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
struct daqboard2000_hw {unsigned int* dacSetting; int dacControl; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int* ao_readback; struct daqboard2000_hw* daq; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static int daqboard2000_ao_insn_write(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_insn *insn,
				      unsigned int *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);
	struct daqboard2000_hw *fpga = devpriv->daq;
	int timeout;

	for (i = 0; i < insn->n; i++) {
		/*
		 * OK, since it works OK without enabling the DAC's, let's keep
		 * it as simple as possible...
		 */
		/* fpga->dacControl = (chan + 2) * 0x0010 | 0x0001; udelay(1000); */
		fpga->dacSetting[chan] = data[i];
		for (timeout = 0; timeout < 20; timeout++) {
			if ((fpga->dacControl & ((chan + 1) * 0x0010)) == 0) {
				break;
			}
			/* udelay(2); */
		}
		devpriv->ao_readback[chan] = data[i];
		/*
		 * Since we never enabled the DAC's, we don't need to disable it...
		 * fpga->dacControl = (chan + 2) * 0x0010 | 0x0000; udelay(1000);
		 */
	}

	return i;
}