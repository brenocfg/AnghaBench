#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int* ul_TTLPortConfiguration; int /*<<< orphan*/  b_OutputMemoryStatus; scalar_t__ iobase; TYPE_1__* ps_BoardInfo; } ;
struct TYPE_3__ {int i_NbrTTLChannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDIDATA_DISABLE ; 
 int /*<<< orphan*/  ADDIDATA_ENABLE ; 
 unsigned char APCI16XX_TTL_INIT ; 
 unsigned char APCI16XX_TTL_INITDIRECTION ; 
 unsigned char APCI16XX_TTL_OUTPUTMEMORY ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int i_APCI16XX_InsnConfigInitTTLIO(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;
	unsigned char b_Command = 0;
	unsigned char b_Cpt = 0;
	unsigned char b_NumberOfPort =
		(unsigned char) (devpriv->ps_BoardInfo->i_NbrTTLChannel / 8);

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

		if ((b_Command == APCI16XX_TTL_INIT) ||
			(b_Command == APCI16XX_TTL_INITDIRECTION) ||
			(b_Command == APCI16XX_TTL_OUTPUTMEMORY)) {
	      /***************************************/
			/* Test the initialisation buffer size */
	      /***************************************/

			if ((b_Command == APCI16XX_TTL_INITDIRECTION)
				&& ((unsigned char) (insn->n - 1) != b_NumberOfPort)) {
		 /*******************/
				/* Data size error */
		 /*******************/

				printk("\nBuffer size error");
				i_ReturnValue = -101;
			}

			if ((b_Command == APCI16XX_TTL_OUTPUTMEMORY)
				&& ((unsigned char) (insn->n) != 2)) {
		 /*******************/
				/* Data size error */
		 /*******************/

				printk("\nBuffer size error");
				i_ReturnValue = -101;
			}
		} else {
	      /************************/
			/* Config command error */
	      /************************/

			printk("\nCommand selection error");
			i_ReturnValue = -100;
		}
	} else {
	   /*******************/
		/* Data size error */
	   /*******************/

		printk("\nBuffer size error");
		i_ReturnValue = -101;
	}

	/**************************************************************************/
	/* Test if no error occur and APCI16XX_TTL_INITDIRECTION command selected */
	/**************************************************************************/

	if ((i_ReturnValue >= 0) && (b_Command == APCI16XX_TTL_INITDIRECTION)) {
		memset(devpriv->ul_TTLPortConfiguration, 0,
			sizeof(devpriv->ul_TTLPortConfiguration));

	   /*************************************/
		/* Test the port direction selection */
	   /*************************************/

		for (b_Cpt = 1;
			(b_Cpt <= b_NumberOfPort) && (i_ReturnValue >= 0);
			b_Cpt++) {
	      /**********************/
			/* Test the direction */
	      /**********************/

			if ((data[b_Cpt] != 0) && (data[b_Cpt] != 0xFF)) {
		 /************************/
				/* Port direction error */
		 /************************/

				printk("\nPort %d direction selection error",
					(int) b_Cpt);
				i_ReturnValue = -(int) b_Cpt;
			}

	      /**************************/
			/* Save the configuration */
	      /**************************/

			devpriv->ul_TTLPortConfiguration[(b_Cpt - 1) / 4] =
				devpriv->ul_TTLPortConfiguration[(b_Cpt -
					1) / 4] | (data[b_Cpt] << (8 * ((b_Cpt -
							1) % 4)));
		}
	}

	/**************************/
	/* Test if no error occur */
	/**************************/

	if (i_ReturnValue >= 0) {
	   /***********************************/
		/* Test if TTL port initilaisation */
	   /***********************************/

		if ((b_Command == APCI16XX_TTL_INIT)
			|| (b_Command == APCI16XX_TTL_INITDIRECTION)) {
	      /******************************/
			/* Set all port configuration */
	      /******************************/

			for (b_Cpt = 0; b_Cpt <= b_NumberOfPort; b_Cpt++) {
				if ((b_Cpt % 4) == 0) {
		    /*************************/
					/* Set the configuration */
		    /*************************/

					outl(devpriv->
						ul_TTLPortConfiguration[b_Cpt /
							4],
						devpriv->iobase + 32 + b_Cpt);
				}
			}
		}
	}

	/************************************************/
	/* Test if output memory initialisation command */
	/************************************************/

	if (b_Command == APCI16XX_TTL_OUTPUTMEMORY) {
		if (data[1]) {
			devpriv->b_OutputMemoryStatus = ADDIDATA_ENABLE;
		} else {
			devpriv->b_OutputMemoryStatus = ADDIDATA_DISABLE;
		}
	}

	return i_ReturnValue;
}