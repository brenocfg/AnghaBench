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
 int APCI1500_RW_MASTER_CONFIGURATION_CONTROL ; 
 int APCI1500_RW_MASTER_INTERRUPT_CONTROL ; 
 int APCI1500_RW_PORT_A_COMMAND_AND_STATUS ; 
 int APCI1500_RW_PORT_A_SPECIFICATION ; 
 int APCI1500_RW_PORT_B_COMMAND_AND_STATUS ; 
 scalar_t__ APCI1500_Z8536_CONTROL_REGISTER ; 
 int EINVAL ; 
#define  START 129 
#define  STOP 128 
 TYPE_1__* devpriv ; 
 int i_Event1Status ; 
 int i_Event2Status ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1500_StartStopInputEvent(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	int i_Event1InterruptStatus = 0, i_Event2InterruptStatus =
		0, i_RegValue;
	switch (data[0]) {
	case START:
	      /*************************/
		/* Tests the port number */
	      /*************************/

		if (data[1] == 1 || data[1] == 2) {
		  /***************************/
			/* Test if port 1 selected */
		  /***************************/

			if (data[1] == 1) {
		    /*****************************/
				/* Test if event initialised */
		    /*****************************/
				if (i_Event1Status == 1) {
		       /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
		       /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /******************/
					/* Disable Port A */
		       /******************/
					outb(0xF0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
		       /***************************************************/
					/* Selects the command and status register of      */
					/* port 1                                          */
		       /***************************************************/
					outb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*************************************/
					/* Allows the pattern interrupt      */
		       /*************************************/
					outb(0xC0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
		       /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************/
					/* Enable Port A */
		       /*****************/
					outb(0xF4,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					i_Event1InterruptStatus = 1;
					outb(APCI1500_RW_PORT_A_SPECIFICATION,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					i_RegValue =
						inb(devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);

					/* Selects the master interrupt control register */
		       /*************************************************/
					outb(APCI1500_RW_MASTER_INTERRUPT_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /**********************************************/
					/* Authorizes the main interrupt on the board */
		       /**********************************************/
					outb(0xD0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);

				}	/*  if(i_Event1Status==1) */
				else {
					printk("\nEvent 1 not initialised\n");
					return -EINVAL;
				}	/* else if(i_Event1Status==1) */
			}	/* if (data[1]==1) */
			if (data[1] == 2) {

				if (i_Event2Status == 1) {
			    /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
			    /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /******************/
					/* Disable Port B */
		       /******************/
					outb(0x74,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
		       /***************************************************/
					/* Selects the command and status register of      */
					/* port 2                                          */
		       /***************************************************/
					outb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*************************************/
					/* Allows the pattern interrupt      */
		       /*************************************/
					outb(0xC0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
		       /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************/
					/* Enable Port B */
		       /*****************/
					outb(0xF4,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);

					/* Selects the master interrupt control register */
		       /*************************************************/
					outb(APCI1500_RW_MASTER_INTERRUPT_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /**********************************************/
					/* Authorizes the main interrupt on the board */
		       /**********************************************/
					outb(0xD0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					i_Event2InterruptStatus = 1;
				}	/*  if(i_Event2Status==1) */
				else {
					printk("\nEvent 2 not initialised\n");
					return -EINVAL;
				}	/* else if(i_Event2Status==1) */
			}	/*  if(data[1]==2) */
		}		/*  if (data[1] == 1 || data[0] == 2) */
		else {
			printk("\nThe port parameter is in error\n");
			return -EINVAL;
		}		/* else if (data[1] == 1 || data[0] == 2) */

		break;

	case STOP:
		  /*************************/
		/* Tests the port number */
		  /*************************/

		if (data[1] == 1 || data[1] == 2) {
		  /***************************/
			/* Test if port 1 selected */
		  /***************************/

			if (data[1] == 1) {
		    /*****************************/
				/* Test if event initialised */
		    /*****************************/
				if (i_Event1Status == 1) {
		       /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
		       /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /******************/
					/* Disable Port A */
		       /******************/
					outb(0xF0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
		       /***************************************************/
					/* Selects the command and status register of      */
					/* port 1                                          */
		       /***************************************************/
					outb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*************************************/
					/* Inhibits the pattern interrupt      */
		       /*************************************/
					outb(0xE0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
		       /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************/
					/* Enable Port A */
		       /*****************/
					outb(0xF4,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					i_Event1InterruptStatus = 0;
				}	/*  if(i_Event1Status==1) */
				else {
					printk("\nEvent 1 not initialised\n");
					return -EINVAL;
				}	/* else if(i_Event1Status==1) */
			}	/* if (data[1]==1) */
			if (data[1] == 2) {
			 /*****************************/
				/* Test if event initialised */
			 /*****************************/
				if (i_Event2Status == 1) {
			  /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
			  /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
			  /******************/
					/* Disable Port B */
			  /******************/
					outb(0x74,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
			  /***************************************************/
					/* Selects the command and status register of      */
					/* port 2                                         */
			  /***************************************************/
					outb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*************************************/
					/* Inhibits the pattern interrupt      */
		       /*************************************/
					outb(0xE0,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************************************************************/
					/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register */
		       /*****************************************************************/
					outb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		       /*****************/
					/* Enable Port B */
		       /*****************/
					outb(0xF4,
						devpriv->iobase +
						APCI1500_Z8536_CONTROL_REGISTER);
					i_Event2InterruptStatus = 0;
				}	/*  if(i_Event2Status==1) */
				else {
					printk("\nEvent 2 not initialised\n");
					return -EINVAL;
				}	/* else if(i_Event2Status==1) */
			}	/* if(data[1]==2) */

		}		/*  if (data[1] == 1 || data[1] == 2) */
		else {
			printk("\nThe port parameter is in error\n");
			return -EINVAL;
		}		/* else if (data[1] == 1 || data[1] == 2) */
		break;
	default:
		printk("\nThe option of START/STOP logic does not exist\n");
		return -EINVAL;
	}			/* switch(data[0]) */

	return insn->n;
}