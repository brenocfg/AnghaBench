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
struct TYPE_2__ {scalar_t__ iobase; int /*<<< orphan*/  tsk_Current; } ;

/* Variables and functions */
 unsigned int APCI1032_DIGITAL_IP_INTERRUPT_DISABLE ; 
 scalar_t__ APCI1032_DIGITAL_IP_INTERRUPT_STATUS ; 
 scalar_t__ APCI1032_DIGITAL_IP_IRQ ; 
 int /*<<< orphan*/  SIGIO ; 
 TYPE_1__* devpriv ; 
 void* inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ui_InterruptStatus ; 

__attribute__((used)) static void v_APCI1032_Interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;

	unsigned int ui_Temp;
	/* disable the interrupt */
	ui_Temp = inl(devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);
	outl(ui_Temp & APCI1032_DIGITAL_IP_INTERRUPT_DISABLE,
		devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);
	ui_InterruptStatus =
		inl(devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_STATUS);
	ui_InterruptStatus = ui_InterruptStatus & 0X0000FFFF;
	send_sig(SIGIO, devpriv->tsk_Current, 0);	/*  send signal to the sample */
	outl(ui_Temp, devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);	/* enable the interrupt */
	return;
}