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
struct TYPE_4__ {int* ul_TTLPortConfiguration; scalar_t__ iobase; TYPE_1__* ps_BoardInfo; } ;
struct TYPE_3__ {int i_NbrTTLChannel; } ;

/* Variables and functions */
 unsigned char APCI16XX_TTL_READCHANNEL ; 
 unsigned char APCI16XX_TTL_READPORT ; 
 unsigned char CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned char CR_RANGE (int /*<<< orphan*/ ) ; 
 TYPE_2__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI16XX_InsnBitsReadTTLIO(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;
	unsigned char b_Command = 0;
	unsigned char b_NumberOfPort =
		(unsigned char) (devpriv->ps_BoardInfo->i_NbrTTLChannel / 8);
	unsigned char b_SelectedPort = CR_RANGE(insn->chanspec);
	unsigned char b_InputChannel = CR_CHAN(insn->chanspec);
	unsigned char *pb_Status;
	unsigned int dw_Status;

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

		if ((b_Command == APCI16XX_TTL_READCHANNEL)
			|| (b_Command == APCI16XX_TTL_READPORT)) {
	      /**************************/
			/* Test the selected port */
	      /**************************/

			if (b_SelectedPort < b_NumberOfPort) {
		 /**********************/
				/* Test if input port */
		 /**********************/

				if (((devpriv->ul_TTLPortConfiguration
							[b_SelectedPort /
								4] >> (8 *
								(b_SelectedPort
									%
									4))) &
						0xFF) == 0) {
		    /***************************/
					/* Test the channel number */
		    /***************************/

					if ((b_Command ==
							APCI16XX_TTL_READCHANNEL)
						&& (b_InputChannel > 7)) {
		       /*******************************************/
						/* The selected TTL digital input is wrong */
		       /*******************************************/

						printk("\nChannel selection error");
						i_ReturnValue = -103;
					}
				} else {
		    /****************************************/
					/* The selected TTL input port is wrong */
		    /****************************************/

					printk("\nPort selection error");
					i_ReturnValue = -102;
				}
			} else {
		 /****************************************/
				/* The selected TTL input port is wrong */
		 /****************************************/

				printk("\nPort selection error");
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
		pb_Status = (unsigned char *) &data[0];

	   /*******************************/
		/* Get the digital inpu status */
	   /*******************************/

		dw_Status =
			inl(devpriv->iobase + 8 + ((b_SelectedPort / 4) * 4));
		dw_Status = (dw_Status >> (8 * (b_SelectedPort % 4))) & 0xFF;

	   /***********************/
		/* Save the port value */
	   /***********************/

		*pb_Status = (unsigned char) dw_Status;

	   /***************************************/
		/* Test if read channel status command */
	   /***************************************/

		if (b_Command == APCI16XX_TTL_READCHANNEL) {
			*pb_Status = (*pb_Status >> b_InputChannel) & 1;
		}
	}

	return i_ReturnValue;
}