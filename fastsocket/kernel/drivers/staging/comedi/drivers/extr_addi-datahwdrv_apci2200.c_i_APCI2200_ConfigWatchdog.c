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
 scalar_t__ APCI2200_WATCHDOG ; 
 scalar_t__ APCI2200_WATCHDOG_ENABLEDISABLE ; 
 scalar_t__ APCI2200_WATCHDOG_RELOAD_VALUE ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI2200_ConfigWatchdog(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	if (data[0] == 0) {
		/* Disable the watchdog */
		outw(0x0,
			devpriv->iobase + APCI2200_WATCHDOG +
			APCI2200_WATCHDOG_ENABLEDISABLE);
		/* Loading the Reload value */
		outw(data[1],
			devpriv->iobase + APCI2200_WATCHDOG +
			APCI2200_WATCHDOG_RELOAD_VALUE);
		data[1] = data[1] >> 16;
		outw(data[1],
			devpriv->iobase + APCI2200_WATCHDOG +
			APCI2200_WATCHDOG_RELOAD_VALUE + 2);
	}			/* if(data[0]==0) */
	else {
		printk("\nThe input parameters are wrong\n");
		return -EINVAL;
	}			/* elseif(data[0]==0) */

	return insn->n;
}