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
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI1032_DIGITAL_IP_INTERRUPT_MODE1 ; 
 scalar_t__ APCI1032_DIGITAL_IP_INTERRUPT_MODE2 ; 
 scalar_t__ APCI1032_DIGITAL_IP_INTERRUPT_STATUS ; 
 scalar_t__ APCI1032_DIGITAL_IP_IRQ ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

int i_APCI1032_Reset(struct comedi_device *dev)
{
	outl(0x0, devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);	/* disable the interrupts */
	inl(devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_STATUS);	/* Reset the interrupt status register */
	outl(0x0, devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_MODE1);	/* Disable the and/or interrupt */
	outl(0x0, devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_MODE2);
	return 0;
}