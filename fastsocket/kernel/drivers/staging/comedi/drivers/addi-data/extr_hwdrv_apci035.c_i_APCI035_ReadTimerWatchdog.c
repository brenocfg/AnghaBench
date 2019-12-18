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
struct comedi_insn {int* unused; int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ b_TimerSelectMode; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ ADDIDATA_TIMER ; 
 TYPE_1__* devpriv ; 
 int i_WatchdogNbr ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI035_ReadTimerWatchdog(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_Status = 0;	/*  Status register */
	i_WatchdogNbr = insn->unused[0];

	/******************/
	/* Get the status */
	/******************/

	ui_Status = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 16);

	/***********************************/
	/* Get the software trigger status */
	/***********************************/

	data[0] = ((ui_Status >> 1) & 1);
	/***********************************/
	/* Get the hardware trigger status */
	/***********************************/
	data[1] = ((ui_Status >> 2) & 1);
	/*********************************/
	/* Get the software clear status */
	/*********************************/
	data[2] = ((ui_Status >> 3) & 1);
	/***************************/
	/* Get the overflow status */
	/***************************/
	data[3] = ((ui_Status >> 0) & 1);
	if (devpriv->b_TimerSelectMode == ADDIDATA_TIMER) {
		data[4] = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 0);

	}			/*   if  (devpriv->b_TimerSelectMode==ADDIDATA_TIMER) */

	return insn->n;
}