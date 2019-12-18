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
struct TYPE_2__ {scalar_t__ iobase; scalar_t__ i_IobaseAddon; int /*<<< orphan*/  tsk_Current; } ;

/* Variables and functions */
 scalar_t__ APCI1500_CLK_SELECT ; 
 unsigned int APCI1500_CONTINUOUS ; 
 unsigned int APCI1500_COUNTER ; 
 unsigned int APCI1500_DISABLE ; 
 unsigned int APCI1500_ENABLE ; 
 unsigned int APCI1500_HARDWARE_GATE ; 
 unsigned int APCI1500_HARDWARE_TRIGGER ; 
 int APCI1500_RW_CPT_TMR1_CMD_STATUS ; 
 int APCI1500_RW_CPT_TMR1_MODE_SPECIFICATION ; 
 int APCI1500_RW_CPT_TMR1_TIME_CST_HIGH ; 
 int APCI1500_RW_CPT_TMR1_TIME_CST_LOW ; 
 int APCI1500_RW_CPT_TMR2_CMD_STATUS ; 
 int APCI1500_RW_CPT_TMR2_MODE_SPECIFICATION ; 
 int APCI1500_RW_CPT_TMR2_TIME_CST_HIGH ; 
 int APCI1500_RW_CPT_TMR2_TIME_CST_LOW ; 
 int APCI1500_RW_CPT_TMR3_CMD_STATUS ; 
 int APCI1500_RW_CPT_TMR3_MODE_SPECIFICATION ; 
 int APCI1500_RW_CPT_TMR3_TIME_CST_HIGH ; 
 int APCI1500_RW_CPT_TMR3_TIME_CST_LOW ; 
 int APCI1500_RW_MASTER_CONFIGURATION_CONTROL ; 
 unsigned int APCI1500_SINGLE ; 
 unsigned int APCI1500_SOFTWARE_GATE ; 
 unsigned int APCI1500_SOFTWARE_TRIGGER ; 
 unsigned int APCI1500_TIMER ; 
 unsigned int APCI1500_WATCHDOG ; 
 scalar_t__ APCI1500_Z8536_CONTROL_REGISTER ; 
#define  COUNTER1 130 
#define  COUNTER2 129 
#define  COUNTER3 128 
 int EINVAL ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 unsigned int i_CounterLogic ; 
 int i_TimerCounter1Init ; 
 int i_TimerCounter2Init ; 
 unsigned int i_TimerCounterWatchdogInterrupt ; 
 int i_WatchdogCounter3Init ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1500_ConfigCounterTimerWatchdog(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_TimerCounterMode, i_MasterConfiguration;

	devpriv->tsk_Current = current;

/* Selection of the input clock */
	if (data[0] == 0 || data[0] == 1 || data[0] == 2) {
		outw(data[0], devpriv->i_IobaseAddon + APCI1500_CLK_SELECT);
	}			/*  if(data[0]==0||data[0]==1||data[0]==2) */
	else {
		if (data[0] != 3) {
			printk("\nThe option for input clock selection does not exist\n");
			return -EINVAL;
		}		/*  if(data[0]!=3) */
	}			/* elseif(data[0]==0||data[0]==1||data[0]==2) */
	/* Select the counter/timer */
	switch (data[1]) {
	case COUNTER1:
		/* selecting counter or timer */
		switch (data[2]) {
		case 0:
			data[2] = APCI1500_COUNTER;
			break;
		case 1:
			data[2] = APCI1500_TIMER;
			break;
		default:
			printk("\nThis choice is not a timer nor a counter\n");
			return -EINVAL;
		}		/*  switch(data[2]) */

		/* Selecting  single or continuous mode */
		switch (data[4]) {
		case 0:
			data[4] = APCI1500_CONTINUOUS;
			break;
		case 1:
			data[4] = APCI1500_SINGLE;
			break;
		default:
			printk("\nThis option for single/continuous mode does not exist\n");
			return -EINVAL;
		}		/*  switch(data[4]) */

		i_TimerCounterMode = data[2] | data[4] | 7;
			 /*************************/
		/* Test the reload value */
			 /*************************/

		if ((data[3] >= 0) && (data[3] <= 65535)) {
			if (data[7] == APCI1500_ENABLE
				|| data[7] == APCI1500_DISABLE) {

				/************************************************/
				/* Selects the mode register of timer/counter 1 */
				/************************************************/
				outb(APCI1500_RW_CPT_TMR1_MODE_SPECIFICATION,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				/***********************/
				/* Writes the new mode */
				/***********************/
				outb(i_TimerCounterMode,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				/****************************************************/
				/* Selects the constant register of timer/counter 1 */
				/****************************************************/

				outb(APCI1500_RW_CPT_TMR1_TIME_CST_LOW,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				  /*************************/
				/* Writes the low value  */
				  /*************************/

				outb(data[3],
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				   /****************************************************/
				/* Selects the constant register of timer/counter 1 */
				   /****************************************************/

				outb(APCI1500_RW_CPT_TMR1_TIME_CST_HIGH,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				  /**************************/
				/* Writes the high value  */
				  /**************************/

				data[3] = data[3] >> 8;
				outb(data[3],
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				     /*********************************************/
				/* Selects the master configuration register */
				     /*********************************************/

				outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				     /**********************/
				/* Reads the register */
				     /**********************/

				i_MasterConfiguration =
					inb(devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				       /********************************************************/
				/* Enables timer/counter 1 and triggers timer/counter 1 */
				       /********************************************************/

				i_MasterConfiguration =
					i_MasterConfiguration | 0x40;

				    /*********************************************/
				/* Selects the master configuration register */
				    /*********************************************/
				outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				      /********************************/
				/* Writes the new configuration */
				      /********************************/
				outb(i_MasterConfiguration,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
					 /****************************************/
				/* Selects the commands register of     */
				/* timer/counter 1                      */
					 /****************************************/

				outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				       /***************************/
				/* Disable timer/counter 1 */
				       /***************************/

				outb(0x0,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
					  /****************************************/
				/* Selects the commands register of     */
				/* timer/counter 1                      */
					  /****************************************/
				outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				      /***************************/
				/* Trigger timer/counter 1 */
				      /***************************/
				outb(0x2,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
			}	/* if(data[7]== APCI1500_ENABLE ||data[7]== APCI1500_DISABLE) */
			else {
				printk("\nError in selection of interrupt enable or disable\n");
				return -EINVAL;
			}	/* elseif(data[7]== APCI1500_ENABLE ||data[7]== APCI1500_DISABLE) */
		}		/*  if ((data[3]>= 0) && (data[3] <= 65535)) */
		else {
			printk("\nError in selection of reload value\n");
			return -EINVAL;
		}		/* else if ((data[3]>= 0) && (data[3] <= 65535)) */
		i_TimerCounterWatchdogInterrupt = data[7];
		i_TimerCounter1Init = 1;
		break;

	case COUNTER2:		/* selecting counter or timer */
		switch (data[2]) {
		case 0:
			data[2] = APCI1500_COUNTER;
			break;
		case 1:
			data[2] = APCI1500_TIMER;
			break;
		default:
			printk("\nThis choice is not a timer nor a counter\n");
			return -EINVAL;
		}		/*  switch(data[2]) */

		/* Selecting  single or continuous mode */
		switch (data[4]) {
		case 0:
			data[4] = APCI1500_CONTINUOUS;
			break;
		case 1:
			data[4] = APCI1500_SINGLE;
			break;
		default:
			printk("\nThis option for single/continuous mode does not exist\n");
			return -EINVAL;
		}		/*  switch(data[4]) */

		/* Selecting  software or hardware trigger */
		switch (data[5]) {
		case 0:
			data[5] = APCI1500_SOFTWARE_TRIGGER;
			break;
		case 1:
			data[5] = APCI1500_HARDWARE_TRIGGER;
			break;
		default:
			printk("\nThis choice for software or hardware trigger does not exist\n");
			return -EINVAL;
		}		/*  switch(data[5]) */

		/* Selecting  software or hardware gate */
		switch (data[6]) {
		case 0:
			data[6] = APCI1500_SOFTWARE_GATE;
			break;
		case 1:
			data[6] = APCI1500_HARDWARE_GATE;
			break;
		default:
			printk("\nThis choice for software or hardware gate does not exist\n");
			return -EINVAL;
		}		/*  switch(data[6]) */

		i_TimerCounterMode = data[2] | data[4] | data[5] | data[6] | 7;

			     /*************************/
		/* Test the reload value */
			     /*************************/

		if ((data[3] >= 0) && (data[3] <= 65535)) {
			if (data[7] == APCI1500_ENABLE
				|| data[7] == APCI1500_DISABLE) {

				/************************************************/
				/* Selects the mode register of timer/counter 2 */
				/************************************************/
				outb(APCI1500_RW_CPT_TMR2_MODE_SPECIFICATION,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				/***********************/
				/* Writes the new mode */
				/***********************/
				outb(i_TimerCounterMode,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				/****************************************************/
				/* Selects the constant register of timer/counter 2 */
				/****************************************************/

				outb(APCI1500_RW_CPT_TMR2_TIME_CST_LOW,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				  /*************************/
				/* Writes the low value  */
				  /*************************/

				outb(data[3],
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				   /****************************************************/
				/* Selects the constant register of timer/counter 2 */
				   /****************************************************/

				outb(APCI1500_RW_CPT_TMR2_TIME_CST_HIGH,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				  /**************************/
				/* Writes the high value  */
				  /**************************/

				data[3] = data[3] >> 8;
				outb(data[3],
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				     /*********************************************/
				/* Selects the master configuration register */
				     /*********************************************/

				outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				     /**********************/
				/* Reads the register */
				     /**********************/

				i_MasterConfiguration =
					inb(devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				       /********************************************************/
				/* Enables timer/counter 2 and triggers timer/counter 2 */
				       /********************************************************/

				i_MasterConfiguration =
					i_MasterConfiguration | 0x20;

				    /*********************************************/
				/* Selects the master configuration register */
				    /*********************************************/
				outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				      /********************************/
				/* Writes the new configuration */
				      /********************************/
				outb(i_MasterConfiguration,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
					 /****************************************/
				/* Selects the commands register of     */
				/* timer/counter 2                      */
					 /****************************************/

				outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				       /***************************/
				/* Disable timer/counter 2 */
				       /***************************/

				outb(0x0,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
					  /****************************************/
				/* Selects the commands register of     */
				/* timer/counter 2                      */
					  /****************************************/
				outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				      /***************************/
				/* Trigger timer/counter 1 */
				      /***************************/
				outb(0x2,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
			}	/* if(data[7]== APCI1500_ENABLE ||data[7]== APCI1500_DISABLE) */
			else {
				printk("\nError in selection of interrupt enable or disable\n");
				return -EINVAL;
			}	/* elseif(data[7]== APCI1500_ENABLE ||data[7]== APCI1500_DISABLE) */
		}		/*  if ((data[3]>= 0) && (data[3] <= 65535)) */
		else {
			printk("\nError in selection of reload value\n");
			return -EINVAL;
		}		/* else if ((data[3]>= 0) && (data[3] <= 65535)) */
		i_TimerCounterWatchdogInterrupt = data[7];
		i_TimerCounter2Init = 1;
		break;

	case COUNTER3:		/* selecting counter or watchdog */
		switch (data[2]) {
		case 0:
			data[2] = APCI1500_COUNTER;
			break;
		case 1:
			data[2] = APCI1500_WATCHDOG;
			break;
		default:
			printk("\nThis choice is not a watchdog nor a counter\n");
			return -EINVAL;
		}		/*  switch(data[2]) */

		/* Selecting  single or continuous mode */
		switch (data[4]) {
		case 0:
			data[4] = APCI1500_CONTINUOUS;
			break;
		case 1:
			data[4] = APCI1500_SINGLE;
			break;
		default:
			printk("\nThis option for single/continuous mode does not exist\n");
			return -EINVAL;
		}		/*  switch(data[4]) */

		/* Selecting  software or hardware gate */
		switch (data[6]) {
		case 0:
			data[6] = APCI1500_SOFTWARE_GATE;
			break;
		case 1:
			data[6] = APCI1500_HARDWARE_GATE;
			break;
		default:
			printk("\nThis choice for software or hardware gate does not exist\n");
			return -EINVAL;
		}		/*  switch(data[6]) */

		      /*****************************/
		/* Test if used for watchdog */
			  /*****************************/

		if (data[2] == APCI1500_WATCHDOG) {
			     /*****************************/
			/* - Enables the output line */
			/* - Enables retrigger       */
			/* - Pulses output           */
			     /*****************************/
			i_TimerCounterMode = data[2] | data[4] | 0x54;
		}		/* if (data[2] == APCI1500_WATCHDOG) */
		else {
			i_TimerCounterMode = data[2] | data[4] | data[6] | 7;
		}		/* elseif (data[2] == APCI1500_WATCHDOG) */
				 /*************************/
		/* Test the reload value */
			     /*************************/

		if ((data[3] >= 0) && (data[3] <= 65535)) {
			if (data[7] == APCI1500_ENABLE
				|| data[7] == APCI1500_DISABLE) {

				/************************************************/
				/* Selects the mode register of watchdog/counter 3 */
				/************************************************/
				outb(APCI1500_RW_CPT_TMR3_MODE_SPECIFICATION,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				/***********************/
				/* Writes the new mode */
				/***********************/
				outb(i_TimerCounterMode,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				/****************************************************/
				/* Selects the constant register of watchdog/counter 3 */
				/****************************************************/

				outb(APCI1500_RW_CPT_TMR3_TIME_CST_LOW,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				  /*************************/
				/* Writes the low value  */
				  /*************************/

				outb(data[3],
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				   /****************************************************/
				/* Selects the constant register of watchdog/counter 3 */
				   /****************************************************/

				outb(APCI1500_RW_CPT_TMR3_TIME_CST_HIGH,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				  /**************************/
				/* Writes the high value  */
				  /**************************/

				data[3] = data[3] >> 8;
				outb(data[3],
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				     /*********************************************/
				/* Selects the master configuration register */
				     /*********************************************/

				outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				     /**********************/
				/* Reads the register */
				     /**********************/

				i_MasterConfiguration =
					inb(devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				       /********************************************************/
				/* Enables watchdog/counter 3 and triggers watchdog/counter 3 */
				       /********************************************************/

				i_MasterConfiguration =
					i_MasterConfiguration | 0x10;

				    /*********************************************/
				/* Selects the master configuration register */
				    /*********************************************/
				outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				      /********************************/
				/* Writes the new configuration */
				      /********************************/
				outb(i_MasterConfiguration,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				      /********************/
				/* Test if COUNTER */
					  /********************/
				if (data[2] == APCI1500_COUNTER) {

					    /*************************************/
					/* Selects the command register of   */
					/* watchdog/counter 3                */
						 /*************************************/
					outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					      /*************************************************/
					/* Disable the  watchdog/counter 3 and starts it */
						  /*************************************************/
					outb(0x0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);

					      /*************************************/
					/* Selects the command register of   */
					/* watchdog/counter 3                */
						  /*************************************/

					outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					     /*************************************************/
					/* Trigger the  watchdog/counter 3 and starts it */
						 /*************************************************/
					outb(0x2,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);

				}	/* elseif(data[2]==APCI1500_COUNTER) */

			}	/* if(data[7]== APCI1500_ENABLE ||data[7]== APCI1500_DISABLE) */
			else {
				printk("\nError in selection of interrupt enable or disable\n");
				return -EINVAL;
			}	/* elseif(data[7]== APCI1500_ENABLE ||data[7]== APCI1500_DISABLE) */
		}		/*  if ((data[3]>= 0) && (data[3] <= 65535)) */
		else {
			printk("\nError in selection of reload value\n");
			return -EINVAL;
		}		/* else if ((data[3]>= 0) && (data[3] <= 65535)) */
		i_TimerCounterWatchdogInterrupt = data[7];
		i_WatchdogCounter3Init = 1;
		break;

	default:
		printk("\nThe specified counter\timer option does not exist\n");
	}			/* switch(data[1]) */
	i_CounterLogic = data[2];
	return insn->n;
}