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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_IobaseAddon; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI2016_DIGITAL_OP ; 
 scalar_t__ APCI2016_WATCHDOG_ENABLEDISABLE ; 
 scalar_t__ APCI2016_WATCHDOG_RELOAD_VALUE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

int i_APCI2016_Reset(struct comedi_device *dev)
{
	outw(0x0, devpriv->iobase + APCI2016_DIGITAL_OP);	/*  Resets the digital output channels */
	outw(0x0, devpriv->i_IobaseAddon + APCI2016_WATCHDOG_ENABLEDISABLE);
	outw(0x0, devpriv->i_IobaseAddon + APCI2016_WATCHDOG_RELOAD_VALUE);
	outw(0x0, devpriv->i_IobaseAddon + APCI2016_WATCHDOG_RELOAD_VALUE + 2);
	return 0;
}