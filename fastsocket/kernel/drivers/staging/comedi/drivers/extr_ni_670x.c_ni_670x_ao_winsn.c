#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int* ao_readback; TYPE_1__* mite; } ;
struct TYPE_3__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 scalar_t__ AO_CHAN_OFFSET ; 
 scalar_t__ AO_VALUE_OFFSET ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ni_670x_ao_winsn(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);

	/* Channel number mapping :

	   NI 6703/ NI 6704     | NI 6704 Only
	   ----------------------------------------------------
	   vch(0)       :       0       | ich(16)       :       1
	   vch(1)       :       2       | ich(17)       :       3
	   .    :       .       |   .                   .
	   .    :       .       |   .                   .
	   .    :       .       |   .                   .
	   vch(15)      :       30      | ich(31)       :       31      */

	for (i = 0; i < insn->n; i++) {
		writel(((chan & 15) << 1) | ((chan & 16) >> 4), devpriv->mite->daq_io_addr + AO_CHAN_OFFSET);	/* First write in channel register which channel to use */
		writel(data[i], devpriv->mite->daq_io_addr + AO_VALUE_OFFSET);	/* write channel value */
		devpriv->ao_readback[chan] = data[i];
	}

	return i;
}