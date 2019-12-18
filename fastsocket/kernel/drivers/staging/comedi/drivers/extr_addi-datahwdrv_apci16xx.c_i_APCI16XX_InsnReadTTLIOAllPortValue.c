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
struct TYPE_4__ {unsigned int* ul_TTLPortConfiguration; scalar_t__ iobase; TYPE_1__* ps_BoardInfo; } ;
struct TYPE_3__ {int i_NbrTTLChannel; } ;

/* Variables and functions */
 unsigned char APCI16XX_TTL_READ_ALL_INPUTS ; 
 unsigned char APCI16XX_TTL_READ_ALL_OUTPUTS ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 TYPE_2__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI16XX_InsnReadTTLIOAllPortValue(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned char b_Command = (unsigned char) CR_AREF(insn->chanspec);
	int i_ReturnValue = insn->n;
	unsigned char b_Cpt = 0;
	unsigned char b_NumberOfPort = 0;
	unsigned int *pls_ReadData = data;

	/********************/
	/* Test the command */
	/********************/

	if ((b_Command == APCI16XX_TTL_READ_ALL_INPUTS)
		|| (b_Command == APCI16XX_TTL_READ_ALL_OUTPUTS)) {
	   /**********************************/
		/* Get the number of 32-Bit ports */
	   /**********************************/

		b_NumberOfPort =
			(unsigned char) (devpriv->ps_BoardInfo->i_NbrTTLChannel / 32);
		if ((b_NumberOfPort * 32) <
			devpriv->ps_BoardInfo->i_NbrTTLChannel) {
			b_NumberOfPort = b_NumberOfPort + 1;
		}

	   /************************/
		/* Test the buffer size */
	   /************************/

		if (insn->n >= b_NumberOfPort) {
			if (b_Command == APCI16XX_TTL_READ_ALL_INPUTS) {
		 /**************************/
				/* Read all digital input */
		 /**************************/

				for (b_Cpt = 0; b_Cpt < b_NumberOfPort; b_Cpt++) {
		    /************************/
					/* Read the 32-Bit port */
		    /************************/

					pls_ReadData[b_Cpt] =
						inl(devpriv->iobase + 8 +
						(b_Cpt * 4));

		    /**************************************/
					/* Mask all channels used als outputs */
		    /**************************************/

					pls_ReadData[b_Cpt] =
						pls_ReadData[b_Cpt] &
						(~devpriv->
						ul_TTLPortConfiguration[b_Cpt]);
				}
			} else {
		 /****************************/
				/* Read all digital outputs */
		 /****************************/

				for (b_Cpt = 0; b_Cpt < b_NumberOfPort; b_Cpt++) {
		    /************************/
					/* Read the 32-Bit port */
		    /************************/

					pls_ReadData[b_Cpt] =
						inl(devpriv->iobase + 20 +
						(b_Cpt * 4));

		    /**************************************/
					/* Mask all channels used als outputs */
		    /**************************************/

					pls_ReadData[b_Cpt] =
						pls_ReadData[b_Cpt] & devpriv->
						ul_TTLPortConfiguration[b_Cpt];
				}
			}
		} else {
	      /*******************/
			/* Data size error */
	      /*******************/

			printk("\nBuffer size error");
			i_ReturnValue = -101;
		}
	} else {
	   /*****************/
		/* Command error */
	   /*****************/

		printk("\nCommand selection error");
		i_ReturnValue = -100;
	}

	return i_ReturnValue;
}