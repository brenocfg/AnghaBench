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
struct TYPE_2__ {scalar_t__ b_TimerSelectMode; int b_ModeSelectRegister; scalar_t__ iobase; scalar_t__ i_IobaseAmcc; } ;

/* Variables and functions */
 scalar_t__ ADDIDATA_COUNTER ; 
 scalar_t__ ADDIDATA_TIMER ; 
 scalar_t__ ADDIDATA_WATCHDOG ; 
 scalar_t__ APCI1564_DIGITAL_OP_WATCHDOG ; 
 scalar_t__ APCI1564_TCW_SYNC_ENABLEDISABLE ; 
 scalar_t__ APCI1564_TCW_TRIG_STATUS ; 
 scalar_t__ APCI1564_TIMER ; 
 TYPE_1__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1564_ReadTimerCounterWatchdog(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ul_Command1 = 0;

	if (devpriv->b_TimerSelectMode == ADDIDATA_WATCHDOG) {
		/*  Stores the status of the Watchdog */
		data[0] =
			inl(devpriv->i_IobaseAmcc +
			APCI1564_DIGITAL_OP_WATCHDOG +
			APCI1564_TCW_TRIG_STATUS) & 0x1;
		data[1] =
			inl(devpriv->i_IobaseAmcc +
			APCI1564_DIGITAL_OP_WATCHDOG);
	}			/*  if  (devpriv->b_TimerSelectMode==ADDIDATA_WATCHDOG) */
	else if (devpriv->b_TimerSelectMode == ADDIDATA_TIMER) {
		/*  Stores the status of the Timer */
		data[0] =
			inl(devpriv->i_IobaseAmcc + APCI1564_TIMER +
			APCI1564_TCW_TRIG_STATUS) & 0x1;

		/*  Stores the Actual value of the Timer */
		data[1] = inl(devpriv->i_IobaseAmcc + APCI1564_TIMER);
	}			/*  else if  (devpriv->b_TimerSelectMode==ADDIDATA_TIMER) */
	else if (devpriv->b_TimerSelectMode == ADDIDATA_COUNTER) {
		/*  Read the Counter Actual Value. */
		data[0] =
			inl(devpriv->iobase + ((devpriv->b_ModeSelectRegister -
					1) * 0x20) +
			APCI1564_TCW_SYNC_ENABLEDISABLE);
		ul_Command1 =
			inl(devpriv->iobase + ((devpriv->b_ModeSelectRegister -
					1) * 0x20) + APCI1564_TCW_TRIG_STATUS);

      /***********************************/
		/* Get the software trigger status */
      /***********************************/
		data[1] = (unsigned char) ((ul_Command1 >> 1) & 1);

      /***********************************/
		/* Get the hardware trigger status */
      /***********************************/
		data[2] = (unsigned char) ((ul_Command1 >> 2) & 1);

      /*********************************/
		/* Get the software clear status */
      /*********************************/
		data[3] = (unsigned char) ((ul_Command1 >> 3) & 1);

      /***************************/
		/* Get the overflow status */
      /***************************/
		data[4] = (unsigned char) ((ul_Command1 >> 0) & 1);
	}			/*  else  if  (devpriv->b_TimerSelectMode==ADDIDATA_COUNTER) */
	else if ((devpriv->b_TimerSelectMode != ADDIDATA_TIMER)
		&& (devpriv->b_TimerSelectMode != ADDIDATA_WATCHDOG)
		&& (devpriv->b_TimerSelectMode != ADDIDATA_COUNTER)) {
		printk("\n Invalid Subdevice !!!\n");
	}			/*  else if ((devpriv->b_TimerSelectMode!=ADDIDATA_TIMER) && (devpriv->b_TimerSelectMode!=ADDIDATA_WATCHDOG)&& (devpriv->b_TimerSelectMode!=ADDIDATA_COUNTER)) */
	return insn->n;
}