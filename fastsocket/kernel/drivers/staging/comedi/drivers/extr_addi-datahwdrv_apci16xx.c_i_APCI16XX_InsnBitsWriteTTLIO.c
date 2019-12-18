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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int* ul_TTLPortConfiguration; scalar_t__ b_OutputMemoryStatus; scalar_t__ iobase; TYPE_1__* ps_BoardInfo; } ;
struct TYPE_3__ {int i_NbrTTLChannel; } ;

/* Variables and functions */
 scalar_t__ ADDIDATA_DISABLE ; 
 unsigned char APCI16XX_TTL_WRITECHANNEL_OFF ; 
 unsigned char APCI16XX_TTL_WRITECHANNEL_ON ; 
 unsigned char APCI16XX_TTL_WRITEPORT_OFF ; 
 unsigned char APCI16XX_TTL_WRITEPORT_ON ; 
 unsigned char CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned char CR_RANGE (int /*<<< orphan*/ ) ; 
 TYPE_2__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int i_APCI16XX_InsnBitsWriteTTLIO(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;
	unsigned char b_Command = 0;
	unsigned char b_NumberOfPort =
		(unsigned char) (devpriv->ps_BoardInfo->i_NbrTTLChannel / 8);
	unsigned char b_SelectedPort = CR_RANGE(insn->chanspec);
	unsigned char b_OutputChannel = CR_CHAN(insn->chanspec);
	unsigned int dw_Status = 0;

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

		if ((b_Command == APCI16XX_TTL_WRITECHANNEL_ON) ||
			(b_Command == APCI16XX_TTL_WRITEPORT_ON) ||
			(b_Command == APCI16XX_TTL_WRITECHANNEL_OFF) ||
			(b_Command == APCI16XX_TTL_WRITEPORT_OFF)) {
	      /**************************/
			/* Test the selected port */
	      /**************************/

			if (b_SelectedPort < b_NumberOfPort) {
		 /***********************/
				/* Test if output port */
		 /***********************/

				if (((devpriv->ul_TTLPortConfiguration
							[b_SelectedPort /
								4] >> (8 *
								(b_SelectedPort
									%
									4))) &
						0xFF) == 0xFF) {
		    /***************************/
					/* Test the channel number */
		    /***************************/

					if (((b_Command == APCI16XX_TTL_WRITECHANNEL_ON) || (b_Command == APCI16XX_TTL_WRITECHANNEL_OFF)) && (b_OutputChannel > 7)) {
		       /********************************************/
						/* The selected TTL digital output is wrong */
		       /********************************************/

						printk("\nChannel selection error");
						i_ReturnValue = -103;
					}

					if (((b_Command == APCI16XX_TTL_WRITECHANNEL_OFF) || (b_Command == APCI16XX_TTL_WRITEPORT_OFF)) && (devpriv->b_OutputMemoryStatus == ADDIDATA_DISABLE)) {
		       /********************************************/
						/* The selected TTL digital output is wrong */
		       /********************************************/

						printk("\nOutput memory disabled");
						i_ReturnValue = -104;
					}

		    /************************/
					/* Test the buffer size */
		    /************************/

					if (((b_Command == APCI16XX_TTL_WRITEPORT_ON) || (b_Command == APCI16XX_TTL_WRITEPORT_OFF)) && (insn->n < 2)) {
		       /*******************/
						/* Data size error */
		       /*******************/

						printk("\nBuffer size error");
						i_ReturnValue = -101;
					}
				} else {
		    /*****************************************/
					/* The selected TTL output port is wrong */
		    /*****************************************/

					printk("\nPort selection error %lX",
						(unsigned long)devpriv->
						ul_TTLPortConfiguration[0]);
					i_ReturnValue = -102;
				}
			} else {
		 /****************************************/
				/* The selected TTL output port is wrong */
		 /****************************************/

				printk("\nPort selection error %d %d",
					b_SelectedPort, b_NumberOfPort);
				i_ReturnValue = -102;
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

	/**************************/
	/* Test if no error occur */
	/**************************/

	if (i_ReturnValue >= 0) {
	   /********************************/
		/* Get the digital output state */
	   /********************************/

		dw_Status =
			inl(devpriv->iobase + 20 + ((b_SelectedPort / 4) * 4));

	   /**********************************/
		/* Test if output memory not used */
	   /**********************************/

		if (devpriv->b_OutputMemoryStatus == ADDIDATA_DISABLE) {
	      /*********************************/
			/* Clear the selected port value */
	      /*********************************/

			dw_Status =
				dw_Status & (0xFFFFFFFFUL -
				(0xFFUL << (8 * (b_SelectedPort % 4))));
		}

	   /******************************/
		/* Test if setting channel ON */
	   /******************************/

		if (b_Command == APCI16XX_TTL_WRITECHANNEL_ON) {
			dw_Status =
				dw_Status | (1UL << ((8 * (b_SelectedPort %
							4)) + b_OutputChannel));
		}

	   /***************************/
		/* Test if setting port ON */
	   /***************************/

		if (b_Command == APCI16XX_TTL_WRITEPORT_ON) {
			dw_Status =
				dw_Status | ((data[1] & 0xFF) << (8 *
					(b_SelectedPort % 4)));
		}

	   /*******************************/
		/* Test if setting channel OFF */
	   /*******************************/

		if (b_Command == APCI16XX_TTL_WRITECHANNEL_OFF) {
			dw_Status =
				dw_Status & (0xFFFFFFFFUL -
				(1UL << ((8 * (b_SelectedPort % 4)) +
						b_OutputChannel)));
		}

	   /****************************/
		/* Test if setting port OFF */
	   /****************************/

		if (b_Command == APCI16XX_TTL_WRITEPORT_OFF) {
			dw_Status =
				dw_Status & (0xFFFFFFFFUL -
				((data[1] & 0xFF) << (8 * (b_SelectedPort %
							4))));
		}

		outl(dw_Status,
			devpriv->iobase + 20 + ((b_SelectedPort / 4) * 4));
	}

	return i_ReturnValue;
}