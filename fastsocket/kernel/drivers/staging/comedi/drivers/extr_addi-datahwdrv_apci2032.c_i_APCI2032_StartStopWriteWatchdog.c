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
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI2032_DIGITAL_OP_WATCHDOG ; 
 scalar_t__ APCI2032_TCW_PROG ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI2032_StartStopWriteWatchdog(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	switch (data[0]) {
	case 0:		/* stop the watchdog */
		outl(0x0, devpriv->iobase + APCI2032_DIGITAL_OP_WATCHDOG + APCI2032_TCW_PROG);	/* disable the watchdog */
		break;
	case 1:		/* start the watchdog */
		outl(0x0001,
			devpriv->iobase + APCI2032_DIGITAL_OP_WATCHDOG +
			APCI2032_TCW_PROG);
		break;
	case 2:		/* Software trigger */
		outl(0x0201,
			devpriv->iobase + APCI2032_DIGITAL_OP_WATCHDOG +
			APCI2032_TCW_PROG);
		break;
	default:
		printk("\nSpecified functionality does not exist\n");
		return -EINVAL;
	}
	return insn->n;
}