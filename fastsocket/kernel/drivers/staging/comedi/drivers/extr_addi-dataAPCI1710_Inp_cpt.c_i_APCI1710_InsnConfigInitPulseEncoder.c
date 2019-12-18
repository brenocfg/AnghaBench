#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_8__ {int dw_SetRegister; TYPE_2__* s_PulseEncoderInfo; } ;
struct TYPE_9__ {TYPE_3__ s_PulseEncoderModuleInfo; } ;
struct TYPE_7__ {int b_PulseEncoderInit; } ;

/* Variables and functions */
 int APCI1710_PULSE_ENCODER ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI1710_InsnConfigInitPulseEncoder(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_IntRegister;

	unsigned char b_ModulNbr;
	unsigned char b_PulseEncoderNbr;
	unsigned char b_InputLevelSelection;
	unsigned char b_TriggerOutputAction;
	unsigned int ul_StartValue;

	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_PulseEncoderNbr = (unsigned char) data[0];
	b_InputLevelSelection = (unsigned char) data[1];
	b_TriggerOutputAction = (unsigned char) data[2];
	ul_StartValue = (unsigned int) data[3];

	i_ReturnValue = insn->n;

	/***********************************/
	/* Test the selected module number */
	/***********************************/

	if (b_ModulNbr <= 3) {
	   /*************************/
		/* Test if pulse encoder */
	   /*************************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				APCI1710_PULSE_ENCODER) ==
			APCI1710_PULSE_ENCODER) {
	      /******************************************/
			/* Test the selected pulse encoder number */
	      /******************************************/

			if (b_PulseEncoderNbr <= 3) {
		 /************************/
				/* Test the input level */
		 /************************/

				if ((b_InputLevelSelection == 0)
					|| (b_InputLevelSelection == 1)) {
		    /*******************************************/
					/* Test the ouput TRIGGER action selection */
		    /*******************************************/

					if ((b_TriggerOutputAction <= 2)
						|| (b_PulseEncoderNbr > 0)) {
						if (ul_StartValue > 1) {

							dw_IntRegister =
								inl(devpriv->
								s_BoardInfos.
								ui_Address +
								20 +
								(64 * b_ModulNbr));

			  /***********************/
							/* Set the start value */
			  /***********************/

							outl(ul_StartValue,
								devpriv->
								s_BoardInfos.
								ui_Address +
								(b_PulseEncoderNbr
									* 4) +
								(64 * b_ModulNbr));

			  /***********************/
							/* Set the input level */
			  /***********************/
							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_PulseEncoderModuleInfo.
								dw_SetRegister =
								(devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_PulseEncoderModuleInfo.
								dw_SetRegister &
								(0xFFFFFFFFUL -
									(1UL << (8 + b_PulseEncoderNbr)))) | ((1UL & (~b_InputLevelSelection)) << (8 + b_PulseEncoderNbr));

			  /*******************************/
							/* Test if output trigger used */
			  /*******************************/

							if ((b_TriggerOutputAction > 0) && (b_PulseEncoderNbr > 1)) {
			     /****************************/
								/* Enable the output action */
			     /****************************/

								devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_SetRegister
									=
									devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_SetRegister
									| (1UL
									<< (4 + b_PulseEncoderNbr));

			     /*********************************/
								/* Set the output TRIGGER action */
			     /*********************************/

								devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_SetRegister
									=
									(devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_SetRegister
									&
									(0xFFFFFFFFUL
										-
										(1UL << (12 + b_PulseEncoderNbr)))) | ((1UL & (b_TriggerOutputAction - 1)) << (12 + b_PulseEncoderNbr));
							} else {
			     /*****************************/
								/* Disable the output action */
			     /*****************************/

								devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_SetRegister
									=
									devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_SetRegister
									&
									(0xFFFFFFFFUL
									-
									(1UL << (4 + b_PulseEncoderNbr)));
							}

			  /*************************/
							/* Set the configuration */
			  /*************************/

							outl(devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_PulseEncoderModuleInfo.
								dw_SetRegister,
								devpriv->
								s_BoardInfos.
								ui_Address +
								20 +
								(64 * b_ModulNbr));

							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_PulseEncoderModuleInfo.
								s_PulseEncoderInfo
								[b_PulseEncoderNbr].
								b_PulseEncoderInit
								= 1;
						} else {
			  /**************************************/
							/* Pulse encoder start value is wrong */
			  /**************************************/

							DPRINTK("Pulse encoder start value is wrong\n");
							i_ReturnValue = -6;
						}
					} else {
		       /****************************************************/
						/* Digital TRIGGER output action selection is wrong */
		       /****************************************************/

						DPRINTK("Digital TRIGGER output action selection is wrong\n");
						i_ReturnValue = -5;
					}
				} else {
		    /**********************************/
					/* Input level selection is wrong */
		    /**********************************/

					DPRINTK("Input level selection is wrong\n");
					i_ReturnValue = -4;
				}
			} else {
		 /************************************/
				/* Pulse encoder selection is wrong */
		 /************************************/

				DPRINTK("Pulse encoder selection is wrong\n");
				i_ReturnValue = -3;
			}
		} else {
	      /********************************************/
			/* The module is not a pulse encoder module */
	      /********************************************/

			DPRINTK("The module is not a pulse encoder module\n");
			i_ReturnValue = -2;
		}
	} else {
	   /********************************************/
		/* The module is not a pulse encoder module */
	   /********************************************/

		DPRINTK("The module is not a pulse encoder module\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}