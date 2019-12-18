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
struct serial_data {int index; unsigned int value; int /*<<< orphan*/  kind; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int* analog_out_mapping; unsigned int* ao_readback; int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  is_channel ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,struct serial_data) ; 

__attribute__((used)) static int serial2002_ao_winsn(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int n;
	int chan;

	chan = devpriv->analog_out_mapping[CR_CHAN(insn->chanspec)];
	for (n = 0; n < insn->n; n++) {
		struct serial_data write;

		write.kind = is_channel;
		write.index = chan;
		write.value = data[n];
		serial_write(devpriv->tty, write);
		devpriv->ao_readback[chan] = data[n];
	}
	return n;
}