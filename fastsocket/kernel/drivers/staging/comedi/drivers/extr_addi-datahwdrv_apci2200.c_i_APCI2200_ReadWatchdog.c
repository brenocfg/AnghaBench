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
 scalar_t__ APCI2200_WATCHDOG_STATUS ; 
 TYPE_1__* devpriv ; 
 int inw (scalar_t__) ; 

int i_APCI2200_ReadWatchdog(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	data[0] =
		inw(devpriv->iobase + APCI2200_WATCHDOG +
		APCI2200_WATCHDOG_STATUS) & 0x1;
	return insn->n;
}