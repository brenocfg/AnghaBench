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
struct TYPE_2__ {scalar_t__ i_IobaseAddon; } ;

/* Variables and functions */
 scalar_t__ APCI2016_WATCHDOG_STATUS ; 
 TYPE_1__* devpriv ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

int i_APCI2016_ReadWatchdog(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	udelay(5);
	data[0] = inw(devpriv->i_IobaseAddon + APCI2016_WATCHDOG_STATUS) & 0x1;
	return insn->n;
}