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
struct TYPE_2__ {scalar_t__ iobase; int /*<<< orphan*/  tsk_Current; } ;

/* Variables and functions */
 unsigned int ADDIDATA_ENABLE ; 
 unsigned int ADDIDATA_OR ; 
 scalar_t__ APCI1032_DIGITAL_IP_INTERRUPT_MODE1 ; 
 scalar_t__ APCI1032_DIGITAL_IP_INTERRUPT_MODE2 ; 
 scalar_t__ APCI1032_DIGITAL_IP_IRQ ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

int i_APCI1032_ConfigDigitalInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_TmpValue;

	unsigned int ul_Command1 = 0;
	unsigned int ul_Command2 = 0;
	devpriv->tsk_Current = current;

  /*******************************/
	/* Set the digital input logic */
  /*******************************/
	if (data[0] == ADDIDATA_ENABLE) {
		ul_Command1 = ul_Command1 | data[2];
		ul_Command2 = ul_Command2 | data[3];
		outl(ul_Command1,
			devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_MODE1);
		outl(ul_Command2,
			devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_MODE2);
		if (data[1] == ADDIDATA_OR) {
			outl(0x4, devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);
			ui_TmpValue =
				inl(devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);
		}		/* if (data[1] == ADDIDATA_OR) */
		else {
			outl(0x6, devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);
		}		/* else if(data[1] == ADDIDATA_OR) */
	}			/*  if( data[0] == ADDIDATA_ENABLE) */
	else {
		ul_Command1 = ul_Command1 & 0xFFFF0000;
		ul_Command2 = ul_Command2 & 0xFFFF0000;
		outl(ul_Command1,
			devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_MODE1);
		outl(ul_Command2,
			devpriv->iobase + APCI1032_DIGITAL_IP_INTERRUPT_MODE2);
		outl(0x0, devpriv->iobase + APCI1032_DIGITAL_IP_IRQ);
	}			/* else if  ( data[0] == ADDIDATA_ENABLE) */

	return insn->n;
}