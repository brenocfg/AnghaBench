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
struct TYPE_2__ {unsigned int* ul_TTLPortConfiguration; scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned char APCI3XXX_TTL_INIT_DIRECTION_PORT2 ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI3XXX_InsnConfigInitTTLIO(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;
	unsigned char b_Command = 0;

	/************************/
	/* Test the buffer size */
	/************************/

	if (insn->n >= 1) {
	   /*******************/
		/* Get the command */
		/* **************** */

		b_Command = (unsigned char) data[0];

	   /********************/
		/* Test the command */
	   /********************/

		if (b_Command == APCI3XXX_TTL_INIT_DIRECTION_PORT2) {
	      /***************************************/
			/* Test the initialisation buffer size */
	      /***************************************/

			if ((b_Command == APCI3XXX_TTL_INIT_DIRECTION_PORT2)
				&& (insn->n != 2)) {
		 /*******************/
				/* Data size error */
		 /*******************/

				printk("Buffer size error\n");
				i_ReturnValue = -101;
			}
		} else {
	      /************************/
			/* Config command error */
	      /************************/

			printk("Command selection error\n");
			i_ReturnValue = -100;
		}
	} else {
	   /*******************/
		/* Data size error */
	   /*******************/

		printk("Buffer size error\n");
		i_ReturnValue = -101;
	}

	/*********************************************************************************/
	/* Test if no error occur and APCI3XXX_TTL_INIT_DIRECTION_PORT2 command selected */
	/*********************************************************************************/

	if ((i_ReturnValue >= 0)
		&& (b_Command == APCI3XXX_TTL_INIT_DIRECTION_PORT2)) {
	   /**********************/
		/* Test the direction */
	   /**********************/

		if ((data[1] == 0) || (data[1] == 0xFF)) {
	      /**************************/
			/* Save the configuration */
	      /**************************/

			devpriv->ul_TTLPortConfiguration[0] =
				devpriv->ul_TTLPortConfiguration[0] | data[1];
		} else {
	      /************************/
			/* Port direction error */
	      /************************/

			printk("Port 2 direction selection error\n");
			i_ReturnValue = -1;
		}
	}

	/**************************/
	/* Test if no error occur */
	/**************************/

	if (i_ReturnValue >= 0) {
	   /***********************************/
		/* Test if TTL port initilaisation */
	   /***********************************/

		if (b_Command == APCI3XXX_TTL_INIT_DIRECTION_PORT2) {
	      /*************************/
			/* Set the configuration */
	      /*************************/

			outl(data[1], devpriv->iobase + 224);
		}
	}

	return i_ReturnValue;
}