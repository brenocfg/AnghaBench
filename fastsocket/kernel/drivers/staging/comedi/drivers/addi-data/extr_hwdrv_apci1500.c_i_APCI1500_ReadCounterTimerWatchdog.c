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
 int APCI1500_RW_CPT_TMR1_CMD_STATUS ; 
 int APCI1500_RW_CPT_TMR2_CMD_STATUS ; 
 int APCI1500_RW_CPT_TMR3_CMD_STATUS ; 
 int APCI1500_R_CPT_TMR1_VALUE_HIGH ; 
 int APCI1500_R_CPT_TMR1_VALUE_LOW ; 
 int APCI1500_R_CPT_TMR2_VALUE_HIGH ; 
 int APCI1500_R_CPT_TMR2_VALUE_LOW ; 
 int APCI1500_R_CPT_TMR3_VALUE_HIGH ; 
 int APCI1500_R_CPT_TMR3_VALUE_LOW ; 
 scalar_t__ APCI1500_Z8536_CONTROL_REGISTER ; 
#define  COUNTER1 130 
#define  COUNTER2 129 
#define  COUNTER3 128 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 int i_TimerCounter1Enabled ; 
 int i_TimerCounter1Init ; 
 int i_TimerCounter2Enabled ; 
 int i_TimerCounter2Init ; 
 int i_WatchdogCounter3Enabled ; 
 int i_WatchdogCounter3Init ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1500_ReadCounterTimerWatchdog(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_CommandAndStatusValue;
	switch (data[0]) {
	case COUNTER1:
		/* Read counter/timer1 */
		if (i_TimerCounter1Init == 1) {
			if (i_TimerCounter1Enabled == 1) {
		  /************************/
				/* Set RCC and gate */
		  /************************/

				i_CommandAndStatusValue = 0xC;
			}	/* if( i_TimerCounter1Init==1) */
			else {
		    /***************/
				/* Set RCC */
		    /***************/

				i_CommandAndStatusValue = 0x8;
			}	/* elseif(i_TimerCounter1Init==1) */

		/********************************************/
			/* Selects the commands and status register */
		/********************************************/
			outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			outb(i_CommandAndStatusValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);

		 /***************************************/
			/* Selects the counter register (high) */
		 /***************************************/
			outb(APCI1500_R_CPT_TMR1_VALUE_HIGH,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] =
				inb(devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] = data[0] << 8;
			data[0] = data[0] & 0xff00;
			outb(APCI1500_R_CPT_TMR1_VALUE_LOW,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] =
				data[0] | inb(devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
		}		/* if( i_TimerCounter1Init==1) */
		else {
			printk("\nTimer/Counter1 not configured\n");
			return -EINVAL;
		}		/* elseif( i_TimerCounter1Init==1) */
		break;
	case COUNTER2:
		/* Read counter/timer2 */
		if (i_TimerCounter2Init == 1) {
			if (i_TimerCounter2Enabled == 1) {
		  /************************/
				/* Set RCC and gate */
		  /************************/

				i_CommandAndStatusValue = 0xC;
			}	/* if( i_TimerCounter2Init==1) */
			else {
		    /***************/
				/* Set RCC */
		    /***************/

				i_CommandAndStatusValue = 0x8;
			}	/* elseif(i_TimerCounter2Init==1) */

		/********************************************/
			/* Selects the commands and status register */
		/********************************************/
			outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			outb(i_CommandAndStatusValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);

		 /***************************************/
			/* Selects the counter register (high) */
		 /***************************************/
			outb(APCI1500_R_CPT_TMR2_VALUE_HIGH,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] =
				inb(devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] = data[0] << 8;
			data[0] = data[0] & 0xff00;
			outb(APCI1500_R_CPT_TMR2_VALUE_LOW,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] =
				data[0] | inb(devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
		}		/* if( i_TimerCounter2Init==1) */
		else {
			printk("\nTimer/Counter2 not configured\n");
			return -EINVAL;
		}		/* elseif( i_TimerCounter2Init==1) */
		break;
	case COUNTER3:
		/* Read counter/watchdog2 */
		if (i_WatchdogCounter3Init == 1) {
			if (i_WatchdogCounter3Enabled == 1) {
		  /************************/
				/* Set RCC and gate */
		  /************************/

				i_CommandAndStatusValue = 0xC;
			}	/* if( i_TimerCounter2Init==1) */
			else {
		    /***************/
				/* Set RCC */
		    /***************/

				i_CommandAndStatusValue = 0x8;
			}	/* elseif(i_WatchdogCounter3Init==1) */

		/********************************************/
			/* Selects the commands and status register */
		/********************************************/
			outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			outb(i_CommandAndStatusValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);

		 /***************************************/
			/* Selects the counter register (high) */
		 /***************************************/
			outb(APCI1500_R_CPT_TMR3_VALUE_HIGH,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] =
				inb(devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] = data[0] << 8;
			data[0] = data[0] & 0xff00;
			outb(APCI1500_R_CPT_TMR3_VALUE_LOW,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			data[0] =
				data[0] | inb(devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
		}		/* if( i_WatchdogCounter3Init==1) */
		else {
			printk("\nWatchdogCounter3 not configured\n");
			return -EINVAL;
		}		/* elseif( i_WatchdogCounter3Init==1) */
		break;
	default:
		printk("\nThe choice of timer/counter/watchdog does not exist\n");
		return -EINVAL;
	}			/* switch(data[0]) */

	return insn->n;
}