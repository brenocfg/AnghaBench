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
struct TYPE_2__ {scalar_t__ iobase; int /*<<< orphan*/  tsk_Current; scalar_t__ i_IobaseAmcc; } ;

/* Variables and functions */
 scalar_t__ APCI1500_COUNTER ; 
 scalar_t__ APCI1500_OR_PRIORITY ; 
 int APCI1500_RW_CPT_TMR1_CMD_STATUS ; 
 int APCI1500_RW_CPT_TMR2_CMD_STATUS ; 
 int APCI1500_RW_CPT_TMR3_CMD_STATUS ; 
 int APCI1500_RW_MASTER_INTERRUPT_CONTROL ; 
 int APCI1500_RW_PORT_A_COMMAND_AND_STATUS ; 
 int APCI1500_RW_PORT_A_INTERRUPT_CONTROL ; 
 int APCI1500_RW_PORT_A_SPECIFICATION ; 
 int APCI1500_RW_PORT_B_COMMAND_AND_STATUS ; 
 scalar_t__ APCI1500_Z8536_CONTROL_REGISTER ; 
 scalar_t__ APCI1500_Z8536_PORT_B ; 
 int /*<<< orphan*/  SIGIO ; 
 TYPE_1__* devpriv ; 
 scalar_t__ i_CounterLogic ; 
 int i_InputChannel ; 
 int i_InterruptMask ; 
 scalar_t__ i_Logic ; 
 int inb (scalar_t__) ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v_APCI1500_Interrupt(int irq, void *d)
{

	struct comedi_device *dev = d;
	unsigned int ui_InterruptStatus = 0;
	int i_RegValue = 0;
	i_InterruptMask = 0;

 /***********************************/
	/* Read the board interrupt status */
 /***********************************/
	ui_InterruptStatus = inl(devpriv->i_IobaseAmcc + 0x38);

  /***************************************/
	/* Test if board generated a interrupt */
  /***************************************/
	if ((ui_InterruptStatus & 0x800000) == 0x800000) {
      /************************/
		/* Disable all Interrupt */
      /************************/
      /*************************************************/
		/* Selects the master interrupt control register */
      /*************************************************/
		/* outb(APCI1500_RW_MASTER_INTERRUPT_CONTROL,devpriv->iobase+APCI1500_Z8536_CONTROL_REGISTER); */
	/**********************************************/
		/* Disables  the main interrupt on the board */
	/**********************************************/
		/* outb(0x00,devpriv->iobase+APCI1500_Z8536_CONTROL_REGISTER); */

   /*****************************************************/
		/* Selects the command and status register of port A */
   /*****************************************************/
		outb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS,
			devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		i_RegValue =
			inb(devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		if ((i_RegValue & 0x60) == 0x60) {
	   /*****************************************************/
			/* Selects the command and status register of port A */
	   /*****************************************************/
			outb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
	    /***********************************/
			/* Deletes the interrupt of port A */
	    /***********************************/
			i_RegValue = (i_RegValue & 0x0F) | 0x20;
			outb(i_RegValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			i_InterruptMask = i_InterruptMask | 1;
			if (i_Logic == APCI1500_OR_PRIORITY) {
				outb(APCI1500_RW_PORT_A_SPECIFICATION,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				i_RegValue =
					inb(devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

	      /***************************************************/
				/* Selects the interrupt vector register of port A */
	      /***************************************************/
				outb(APCI1500_RW_PORT_A_INTERRUPT_CONTROL,
					devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);
				i_RegValue =
					inb(devpriv->iobase +
					APCI1500_Z8536_CONTROL_REGISTER);

				i_InputChannel = 1 + (i_RegValue >> 1);

			}	/*  if(i_Logic==APCI1500_OR_PRIORITY) */
			else {
				i_InputChannel = 0;
			}	/* elseif(i_Logic==APCI1500_OR_PRIORITY) */
		}		/*  if ((i_RegValue & 0x60) == 0x60) */

	   /*****************************************************/
		/* Selects the command and status register of port B */
	   /*****************************************************/
		outb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,
			devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		i_RegValue =
			inb(devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		if ((i_RegValue & 0x60) == 0x60) {
	     /*****************************************************/
			/* Selects the command and status register of port B */
	     /*****************************************************/
			outb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
	     /***********************************/
			/* Deletes the interrupt of port B */
	     /***********************************/
			i_RegValue = (i_RegValue & 0x0F) | 0x20;
			outb(i_RegValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			printk("\n\n\n");
	     /****************/
			/* Reads port B */
	     /****************/
			i_RegValue =
				inb((unsigned int) devpriv->iobase +
				APCI1500_Z8536_PORT_B);

			i_RegValue = i_RegValue & 0xC0;
	      /**************************************/
			/* Tests if this is an external error */
	      /**************************************/

			if (i_RegValue) {
				/* Disable the interrupt */
		     /*****************************************************/
				/* Selects the command and status register of port B */
		     /*****************************************************/
				outl(0x0, devpriv->i_IobaseAmcc + 0x38);

				if (i_RegValue & 0x80) {
					i_InterruptMask =
						i_InterruptMask | 0x40;
				}	/* if (i_RegValue & 0x80) */

				if (i_RegValue & 0x40) {
					i_InterruptMask =
						i_InterruptMask | 0x80;
				}	/* if (i_RegValue & 0x40) */
			}	/*  if (i_RegValue) */
			else {
				i_InterruptMask = i_InterruptMask | 2;
			}	/*  if (i_RegValue) */
		}		/* if ((i_RegValue & 0x60) == 0x60) */

		/*****************************************************/
		/* Selects the command and status register of timer 1 */
		/*****************************************************/
		outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
			devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		i_RegValue =
			inb(devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		if ((i_RegValue & 0x60) == 0x60) {
		   /*****************************************************/
			/* Selects the command and status register of timer 1 */
		   /*****************************************************/
			outb(APCI1500_RW_CPT_TMR1_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
		   /***********************************/
			/* Deletes the interrupt of timer 1 */
		   /***********************************/
			i_RegValue = (i_RegValue & 0x0F) | 0x20;
			outb(i_RegValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			i_InterruptMask = i_InterruptMask | 4;
		}		/*  if ((i_RegValue & 0x60) == 0x60) */
		/*****************************************************/
		/* Selects the command and status register of timer 2 */
		/*****************************************************/
		outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
			devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		i_RegValue =
			inb(devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		if ((i_RegValue & 0x60) == 0x60) {
		   /*****************************************************/
			/* Selects the command and status register of timer 2 */
		   /*****************************************************/
			outb(APCI1500_RW_CPT_TMR2_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
		   /***********************************/
			/* Deletes the interrupt of timer 2 */
		   /***********************************/
			i_RegValue = (i_RegValue & 0x0F) | 0x20;
			outb(i_RegValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			i_InterruptMask = i_InterruptMask | 8;
		}		/*  if ((i_RegValue & 0x60) == 0x60) */

		/*****************************************************/
		/* Selects the command and status register of timer 3 */
		/*****************************************************/
		outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
			devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		i_RegValue =
			inb(devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
		if ((i_RegValue & 0x60) == 0x60) {
		   /*****************************************************/
			/* Selects the command and status register of timer 3 */
		   /*****************************************************/
			outb(APCI1500_RW_CPT_TMR3_CMD_STATUS,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
		   /***********************************/
			/* Deletes the interrupt of timer 3 */
		   /***********************************/
			i_RegValue = (i_RegValue & 0x0F) | 0x20;
			outb(i_RegValue,
				devpriv->iobase +
				APCI1500_Z8536_CONTROL_REGISTER);
			if (i_CounterLogic == APCI1500_COUNTER) {
				i_InterruptMask = i_InterruptMask | 0x10;
			}	/* if(i_CounterLogic==APCI1500_COUNTER) */
			else {
				i_InterruptMask = i_InterruptMask | 0x20;
			}
		}		/*  if ((i_RegValue & 0x60) == 0x60) */

		send_sig(SIGIO, devpriv->tsk_Current, 0);	/*  send signal to the sample */
	       /***********************/
		/* Enable all Interrupts */
	       /***********************/

	       /*************************************************/
		/* Selects the master interrupt control register */
	       /*************************************************/
		outb(APCI1500_RW_MASTER_INTERRUPT_CONTROL,
			devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
	       /**********************************************/
		/* Authorizes the main interrupt on the board */
	       /**********************************************/
		outb(0xD0, devpriv->iobase + APCI1500_Z8536_CONTROL_REGISTER);
	}			/*   if ((ui_InterruptStatus & 0x800000) == 0x800000) */
	else {
		printk("\nInterrupt from unknown source\n");

	}			/* else if ((ui_InterruptStatus & 0x800000) == 0x800000) */
	return;
}