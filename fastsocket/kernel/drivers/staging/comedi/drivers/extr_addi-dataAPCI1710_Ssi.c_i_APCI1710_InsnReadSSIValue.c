#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
typedef  unsigned int dw_And2 ;
typedef  unsigned int dw_And1 ;
typedef  unsigned int dw_And ;
struct TYPE_5__ {int* dw_MolduleConfiguration; int /*<<< orphan*/  ui_Address; } ;
struct TYPE_8__ {TYPE_3__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_6__ {int b_SSIInit; int b_SSIProfile; unsigned char b_PositionTurnLength; unsigned char b_TurnCptLength; } ;
struct TYPE_7__ {TYPE_2__ s_SSICounterInfo; } ;

/* Variables and functions */
 int APCI1710_SSI_COUNTER ; 
#define  APCI1710_SSI_READ1VALUE 129 
#define  APCI1710_SSI_READALLVALUE 128 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnReadSSIValue(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned char b_Cpt;
	unsigned char b_Length;
	unsigned char b_Schift;
	unsigned char b_SSICpt;
	unsigned int dw_And;
	unsigned int dw_And1;
	unsigned int dw_And2;
	unsigned int dw_StatusReg;
	unsigned int dw_CounterValue;
	unsigned char b_ModulNbr;
	unsigned char b_SelectedSSI;
	unsigned char b_ReadType;
	unsigned int *pul_Position;
	unsigned int *pul_TurnCpt;
	unsigned int *pul_Position1;
	unsigned int *pul_TurnCpt1;

	i_ReturnValue = insn->n;
	pul_Position1 = (unsigned int *) &data[0];
/* For Read1 */
	pul_TurnCpt1 = (unsigned int *) &data[1];
/* For Read all */
	pul_Position = (unsigned int *) &data[0];	/* 0-2 */
	pul_TurnCpt = (unsigned int *) &data[3];	/* 3-5 */
	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_SelectedSSI = (unsigned char) CR_CHAN(insn->chanspec);
	b_ReadType = (unsigned char) CR_RANGE(insn->chanspec);

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /***********************/
		/* Test if SSI counter */
	   /***********************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_SSI_COUNTER) {
	      /***************************/
			/* Test if SSI initialised */
	      /***************************/

			if (devpriv->s_ModuleInfo[b_ModulNbr].
				s_SSICounterInfo.b_SSIInit == 1) {

				switch (b_ReadType) {

				case APCI1710_SSI_READ1VALUE:
		 /****************************************/
					/* Test the selected SSI counter number */
		 /****************************************/

					if (b_SelectedSSI < 3) {
		    /************************/
						/* Start the conversion */
		    /************************/

						outl(0, devpriv->s_BoardInfos.
							ui_Address + 8 +
							(64 * b_ModulNbr));

						do {
		       /*******************/
							/* Read the status */
		       /*******************/

							dw_StatusReg =
								inl(devpriv->
								s_BoardInfos.
								ui_Address +
								(64 * b_ModulNbr));
						} while ((dw_StatusReg & 0x1)
							 != 0);

		    /******************************/
						/* Read the SSI counter value */
		    /******************************/

						dw_CounterValue =
							inl(devpriv->
							s_BoardInfos.
							ui_Address + 4 +
							(b_SelectedSSI * 4) +
							(64 * b_ModulNbr));

						b_Length =
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_SSIProfile / 2;

						if ((b_Length * 2) !=
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_SSIProfile) {
							b_Length++;
						}

						b_Schift =
							b_Length -
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_PositionTurnLength;

						*pul_Position1 =
							dw_CounterValue >>
							b_Schift;

						dw_And = 1;

						for (b_Cpt = 0;
							b_Cpt <
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_PositionTurnLength;
							b_Cpt++) {
							dw_And = dw_And * 2;
						}

						*pul_Position1 =
							*pul_Position1 &
							((dw_And) - 1);

						*pul_TurnCpt1 =
							dw_CounterValue >>
							b_Length;

						dw_And = 1;

						for (b_Cpt = 0;
							b_Cpt <
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_TurnCptLength;
							b_Cpt++) {
							dw_And = dw_And * 2;
						}

						*pul_TurnCpt1 =
							*pul_TurnCpt1 &
							((dw_And) - 1);
					} else {
		    /*****************************/
						/* The selected SSI is wrong */
		    /*****************************/

						DPRINTK("The selected SSI is wrong\n");
						i_ReturnValue = -5;
					}
					break;

				case APCI1710_SSI_READALLVALUE:
					dw_And1 = 1;

					for (b_Cpt = 0;
						b_Cpt <
						devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_SSICounterInfo.
						b_PositionTurnLength; b_Cpt++) {
						dw_And1 = dw_And1 * 2;
					}

					dw_And2 = 1;

					for (b_Cpt = 0;
						b_Cpt <
						devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_SSICounterInfo.
						b_TurnCptLength; b_Cpt++) {
						dw_And2 = dw_And2 * 2;
					}

		 /************************/
					/* Start the conversion */
		 /************************/

					outl(0, devpriv->s_BoardInfos.
						ui_Address + 8 +
						(64 * b_ModulNbr));

					do {
		    /*******************/
						/* Read the status */
		    /*******************/

						dw_StatusReg =
							inl(devpriv->
							s_BoardInfos.
							ui_Address +
							(64 * b_ModulNbr));
					} while ((dw_StatusReg & 0x1) != 0);

					for (b_SSICpt = 0; b_SSICpt < 3;
						b_SSICpt++) {
		    /******************************/
						/* Read the SSI counter value */
		    /******************************/

						dw_CounterValue =
							inl(devpriv->
							s_BoardInfos.
							ui_Address + 4 +
							(b_SSICpt * 4) +
							(64 * b_ModulNbr));

						b_Length =
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_SSIProfile / 2;

						if ((b_Length * 2) !=
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_SSIProfile) {
							b_Length++;
						}

						b_Schift =
							b_Length -
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SSICounterInfo.
							b_PositionTurnLength;

						pul_Position[b_SSICpt] =
							dw_CounterValue >>
							b_Schift;
						pul_Position[b_SSICpt] =
							pul_Position[b_SSICpt] &
							((dw_And1) - 1);

						pul_TurnCpt[b_SSICpt] =
							dw_CounterValue >>
							b_Length;
						pul_TurnCpt[b_SSICpt] =
							pul_TurnCpt[b_SSICpt] &
							((dw_And2) - 1);
					}
					break;

				default:
					printk("Read Type Inputs Wrong\n");

				}	/*  switch  ending */

			} else {
		 /***********************/
				/* SSI not initialised */
		 /***********************/

				DPRINTK("SSI not initialised\n");
				i_ReturnValue = -4;
			}
		} else {
	      /**********************************/
			/* The module is not a SSI module */
	      /**********************************/

			DPRINTK("The module is not a SSI module\n");
			i_ReturnValue = -3;

		}
	} else {
	   /***********************/
		/* Module number error */
	   /***********************/

		DPRINTK("Module number error\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}