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
 TYPE_1__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI035_ReadAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_CommandRegister = 0;
/******************/
/*  Set the start */
/******************/
	ui_CommandRegister = 0x80000;
 /******************************/
	/* Write the command register */
 /******************************/
	outl(ui_CommandRegister, devpriv->iobase + 128 + 8);

/***************************************/
/* Read the digital value of the input */
/***************************************/
	data[0] = inl(devpriv->iobase + 128 + 28);
	return insn->n;
}