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
struct TYPE_2__ {scalar_t__ iobase; scalar_t__ b_DigitalOutputRegister; } ;

/* Variables and functions */
 scalar_t__ APCI2032_DIGITAL_OP ; 
 scalar_t__ APCI2032_DIGITAL_OP_INTERRUPT ; 
 scalar_t__ APCI2032_DIGITAL_OP_WATCHDOG ; 
 scalar_t__ APCI2032_TCW_PROG ; 
 scalar_t__ APCI2032_TCW_RELOAD_VALUE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 scalar_t__ ui_Type ; 

int i_APCI2032_Reset(struct comedi_device *dev)
{
	devpriv->b_DigitalOutputRegister = 0;
	ui_Type = 0;
	outl(0x0, devpriv->iobase + APCI2032_DIGITAL_OP);	/* Resets the output channels */
	outl(0x0, devpriv->iobase + APCI2032_DIGITAL_OP_INTERRUPT);	/* Disables the interrupt. */
	outl(0x0, devpriv->iobase + APCI2032_DIGITAL_OP_WATCHDOG + APCI2032_TCW_PROG);	/* disable the watchdog */
	outl(0x0, devpriv->iobase + APCI2032_DIGITAL_OP_WATCHDOG + APCI2032_TCW_RELOAD_VALUE);	/* reload=0 */
	return 0;
}