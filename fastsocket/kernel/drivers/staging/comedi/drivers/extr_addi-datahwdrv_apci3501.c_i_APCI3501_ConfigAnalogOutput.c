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
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  b_InterruptMode; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI3501_ANALOG_OUTPUT ; 
 scalar_t__ APCI3501_AO_VOLT_MODE ; 
 int /*<<< orphan*/  MODE0 ; 
 int /*<<< orphan*/  MODE1 ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI3501_ConfigAnalogOutput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	outl(data[0],
		devpriv->iobase + APCI3501_ANALOG_OUTPUT +
		APCI3501_AO_VOLT_MODE);

	if (data[0]) {
		devpriv->b_InterruptMode = MODE1;
	} else {
		devpriv->b_InterruptMode = MODE0;
	}
	return insn->n;
}