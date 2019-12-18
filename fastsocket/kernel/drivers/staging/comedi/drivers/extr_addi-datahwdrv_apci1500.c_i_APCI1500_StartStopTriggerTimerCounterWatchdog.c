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
 scalar_t__ APCI1500_Z8536_CONTROL_REGISTER ; 
#define  COUNTER1 133 
#define  COUNTER2 132 
#define  COUNTER3 131 
 int EINVAL ; 
#define  START 130 
#define  STOP 129 
#define  TRIGGER 128 
 TYPE_1__* devpriv ; 
 int i_TimerCounter1Enabled ; 
 int i_TimerCounter1Init ; 
 int i_TimerCounter2Enabled ; 
 int i_TimerCounter2Init ; 
 int i_TimerCounterWatchdogInterrupt ; 
 int i_WatchdogCounter3Enabled ; 
 int i_WatchdogCounter3Init ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1500_StartStopTriggerTimerCounterWatchdog(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_CommandAndStatusValue;

	switch (data[0]) {
	case COUNTER1:
		switch (data[1]) {
		case START:
			if (i_TimerCounter1Init == 1) {
				if (i_TimerCounterWatchdogInterrupt == 1) {
					i_CommandAndStatusValue = 0xC4;	/* Enable the interrupt */
				}	/*  if(i_TimerCounterWatchdogInterrupt==1) */
				else {
					i_CommandAndStatusValue = 0xE4;	/* disable the interrupt */
				}	/* elseif(i_TimerCounterWatchdogInterrupt==1) */
					      /**************************/
				/* Starts timer/counter 1 */
					      /**************************/
				i_TimerCounter1Enabled = 1;
						/********************************************/
				/* Selects the commands and status register */
						/********************************************/
				outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				outb(i_CommandAndStatusValue,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
			}	/* if( i_TimerCounter1Init==1) */
			else {
				printk("\nCounter/Timer1 not configured\n");
				return -EINVAL;
			}
			break;

		case STOP:

					      /**************************/
			/* Stop timer/counter 1 */
					      /**************************/

						/********************************************/
			/* Selects the commands and status register */
						/********************************************/
			outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			outb(0x00,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			i_TimerCounter1Enabled = 0;
			break;

		case TRIGGER:
			if (i_TimerCounter1Init == 1) {
				if (i_TimerCounter1Enabled == 1) {
						 /************************/
					/* Set Trigger and gate */
						 /************************/

					i_CommandAndStatusValue = 0x6;
				}	/* if( i_TimerCounter1Enabled==1) */
				else {
						   /***************/
					/* Set Trigger */
						   /***************/

					i_CommandAndStatusValue = 0x2;
				}	/* elseif(i_TimerCounter1Enabled==1) */

						/********************************************/
				/* Selects the commands and status register */
						/********************************************/
				outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				outb(i_CommandAndStatusValue,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
			}	/* if( i_TimerCounter1Init==1) */
			else {
				printk("\nCounter/Timer1 not configured\n");
				return -EINVAL;
			}
			break;

		default:
			printk("\nThe specified option for start/stop/trigger does not exist\n");
			return -EINVAL;
		}		/* switch(data[1]) */
		break;

	case COUNTER2:
		switch (data[1]) {
		case START:
			if (i_TimerCounter2Init == 1) {
				if (i_TimerCounterWatchdogInterrupt == 1) {
					i_CommandAndStatusValue = 0xC4;	/* Enable the interrupt */
				}	/*  if(i_TimerCounterWatchdogInterrupt==1) */
				else {
					i_CommandAndStatusValue = 0xE4;	/* disable the interrupt */
				}	/* elseif(i_TimerCounterWatchdogInterrupt==1) */
					      /**************************/
				/* Starts timer/counter 2 */
					      /**************************/
				i_TimerCounter2Enabled = 1;
						/********************************************/
				/* Selects the commands and status register */
						/********************************************/
				outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				outb(i_CommandAndStatusValue,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
			}	/* if( i_TimerCounter2Init==1) */
			else {
				printk("\nCounter/Timer2 not configured\n");
				return -EINVAL;
			}
			break;

		case STOP:

					      /**************************/
			/* Stop timer/counter 2 */
					      /**************************/

						/********************************************/
			/* Selects the commands and status register */
						/********************************************/
			outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			outb(0x00,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			i_TimerCounter2Enabled = 0;
			break;
		case TRIGGER:
			if (i_TimerCounter2Init == 1) {
				if (i_TimerCounter2Enabled == 1) {
						 /************************/
					/* Set Trigger and gate */
						 /************************/

					i_CommandAndStatusValue = 0x6;
				}	/* if( i_TimerCounter2Enabled==1) */
				else {
						   /***************/
					/* Set Trigger */
						   /***************/

					i_CommandAndStatusValue = 0x2;
				}	/* elseif(i_TimerCounter2Enabled==1) */

						/********************************************/
				/* Selects the commands and status register */
						/********************************************/
				outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				outb(i_CommandAndStatusValue,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
			}	/* if( i_TimerCounter2Init==1) */
			else {
				printk("\nCounter/Timer2 not configured\n");
				return -EINVAL;
			}
			break;
		default:
			printk("\nThe specified option for start/stop/trigger does not exist\n");
			return -EINVAL;
		}		/* switch(data[1]) */
		break;
	case COUNTER3:
		switch (data[1]) {
		case START:
			if (i_WatchdogCounter3Init == 1) {

				if (i_TimerCounterWatchdogInterrupt == 1) {
					i_CommandAndStatusValue = 0xC4;	/* Enable the interrupt */
				}	/*  if(i_TimerCounterWatchdogInterrupt==1) */
				else {
					i_CommandAndStatusValue = 0xE4;	/* disable the interrupt */
				}	/* elseif(i_TimerCounterWatchdogInterrupt==1) */
					      /**************************/
				/* Starts Watchdog/counter 3 */
					      /**************************/
				i_WatchdogCounter3Enabled = 1;
						/********************************************/
				/* Selects the commands and status register */
						/********************************************/
				outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				outb(i_CommandAndStatusValue,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

			}	/*  if( i_WatchdogCounter3init==1) */
			else {
				printk("\nWatchdog/Counter3 not configured\n");
				return -EINVAL;
			}
			break;

		case STOP:

					      /**************************/
			/* Stop Watchdog/counter 3 */
					      /**************************/

						/********************************************/
			/* Selects the commands and status register */
						/********************************************/
			outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			outb(0x00,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			i_WatchdogCounter3Enabled = 0;
			break;

		case TRIGGER:
			switch (data[2]) {
			case 0:	/* triggering counter 3 */
				if (i_WatchdogCounter3Init == 1) {
					if (i_WatchdogCounter3Enabled == 1) {
							       /************************/
						/* Set Trigger and gate */
							       /************************/

						i_CommandAndStatusValue = 0x6;
					}	/* if( i_WatchdogCounter3Enabled==1) */
					else {
							   /***************/
						/* Set Trigger */
							   /***************/

						i_CommandAndStatusValue = 0x2;
					}	/* elseif(i_WatchdogCounter3Enabled==1) */

						/********************************************/
					/* Selects the commands and status register */
						/********************************************/
					outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					outb(i_CommandAndStatusValue,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
				}	/* if( i_WatchdogCounter3Init==1) */
				else {
					printk("\nCounter3 not configured\n");
					return -EINVAL;
				}
				break;
			case 1:
				/* triggering Watchdog 3 */
				if (i_WatchdogCounter3Init == 1) {

						/********************************************/
					/* Selects the commands and status register */
						/********************************************/
					outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					outb(0x6,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
				}	/* if( i_WatchdogCounter3Init==1) */
				else {
					printk("\nWatchdog 3 not configured\n");
					return -EINVAL;
				}
				break;
			default:
				printk("\nWrong choice of watchdog/counter3\n");
				return -EINVAL;
			}	/* switch(data[2]) */
			break;
		default:
			printk("\nThe specified option for start/stop/trigger does not exist\n");
			return -EINVAL;
		}		/* switch(data[1]) */
		break;
	default:
		printk("\nThe specified choice for counter/watchdog/timer does not exist\n");
		return -EINVAL;
	}			/* switch(data[0]) */
	return insn->n;
}