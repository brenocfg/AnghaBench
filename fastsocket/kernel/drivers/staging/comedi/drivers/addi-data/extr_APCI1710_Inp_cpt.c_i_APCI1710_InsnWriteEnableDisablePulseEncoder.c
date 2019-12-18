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
struct TYPE_9__ {int /*<<< orphan*/  ui_Address; } ;
struct TYPE_10__ {TYPE_4__ s_BoardInfos; TYPE_3__* s_ModuleInfo; int /*<<< orphan*/  tsk_Current; } ;
struct TYPE_7__ {int dw_SetRegister; unsigned long dw_ControlRegister; TYPE_1__* s_PulseEncoderInfo; } ;
struct TYPE_8__ {TYPE_2__ s_PulseEncoderModuleInfo; } ;
struct TYPE_6__ {int b_PulseEncoderInit; } ;

/* Variables and functions */
 unsigned char APCI1710_CONTINUOUS ; 
#define  APCI1710_DISABLE 129 
#define  APCI1710_ENABLE 128 
 unsigned char APCI1710_SINGLE ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  current ; 
 TYPE_5__* devpriv ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

int i_APCI1710_InsnWriteEnableDisablePulseEncoder(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned char b_ModulNbr;
	unsigned char b_PulseEncoderNbr;
	unsigned char b_CycleSelection;
	unsigned char b_InterruptHandling;
	unsigned char b_Action;

	i_ReturnValue = insn->n;
	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_Action = (unsigned char) data[0];
	b_PulseEncoderNbr = (unsigned char) data[1];
	b_CycleSelection = (unsigned char) data[2];
	b_InterruptHandling = (unsigned char) data[3];

	/***********************************/
	/* Test the selected module number */
	/***********************************/

	if (b_ModulNbr <= 3) {
	   /******************************************/
		/* Test the selected pulse encoder number */
	   /******************************************/

		if (b_PulseEncoderNbr <= 3) {
	      /*************************************/
			/* Test if pulse encoder initialised */
	      /*************************************/

			if (devpriv->s_ModuleInfo[b_ModulNbr].
				s_PulseEncoderModuleInfo.
				s_PulseEncoderInfo[b_PulseEncoderNbr].
				b_PulseEncoderInit == 1) {
				switch (b_Action) {

				case APCI1710_ENABLE:
		 /****************************/
					/* Test the cycle selection */
		 /****************************/

					if (b_CycleSelection ==
						APCI1710_CONTINUOUS
						|| b_CycleSelection ==
						APCI1710_SINGLE) {
		    /*******************************/
						/* Test the interrupt handling */
		    /*******************************/

						if (b_InterruptHandling ==
							APCI1710_ENABLE
							|| b_InterruptHandling
							== APCI1710_DISABLE) {
		       /******************************/
							/* Test if interrupt not used */
		       /******************************/

							if (b_InterruptHandling
								==
								APCI1710_DISABLE)
							{
			  /*************************/
								/* Disable the interrupt */
			  /*************************/

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
									(1UL << b_PulseEncoderNbr));
							} else {

			     /************************/
								/* Enable the interrupt */
			     /************************/

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
									<<
									b_PulseEncoderNbr);
								devpriv->tsk_Current = current;	/*  Save the current process task structure */

							}

							if (i_ReturnValue >= 0) {
			  /***********************************/
								/* Enable or disable the interrupt */
			  /***********************************/

								outl(devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_SetRegister,
									devpriv->
									s_BoardInfos.
									ui_Address
									+ 20 +
									(64 * b_ModulNbr));

			  /****************************/
								/* Enable the pulse encoder */
			  /****************************/
								devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_ControlRegister
									=
									devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_ControlRegister
									| (1UL
									<<
									b_PulseEncoderNbr);

			  /**********************/
								/* Set the cycle mode */
			  /**********************/

								devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_ControlRegister
									=
									(devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_ControlRegister
									&
									(0xFFFFFFFFUL
										-
										(1 << (b_PulseEncoderNbr + 4)))) | ((b_CycleSelection & 1UL) << (4 + b_PulseEncoderNbr));

			  /****************************/
								/* Enable the pulse encoder */
			  /****************************/

								outl(devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_PulseEncoderModuleInfo.
									dw_ControlRegister,
									devpriv->
									s_BoardInfos.
									ui_Address
									+ 16 +
									(64 * b_ModulNbr));
							}
						} else {
		       /************************************/
							/* Interrupt handling mode is wrong */
		       /************************************/

							DPRINTK("Interrupt handling mode is wrong\n");
							i_ReturnValue = -6;
						}
					} else {
		    /*********************************/
						/* Cycle selection mode is wrong */
		    /*********************************/

						DPRINTK("Cycle selection mode is wrong\n");
						i_ReturnValue = -5;
					}
					break;

				case APCI1710_DISABLE:
					devpriv->s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_ControlRegister =
						devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_ControlRegister &
						(0xFFFFFFFFUL -
						(1UL << b_PulseEncoderNbr));

		 /*****************************/
					/* Disable the pulse encoder */
		 /*****************************/

					outl(devpriv->s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_ControlRegister,
						devpriv->s_BoardInfos.
						ui_Address + 16 +
						(64 * b_ModulNbr));

					break;
				}	/*  switch End */

			} else {
		 /*********************************/
				/* Pulse encoder not initialised */
		 /*********************************/

				DPRINTK("Pulse encoder not initialised\n");
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
	   /*****************************/
		/* Module selection is wrong */
	   /*****************************/

		DPRINTK("Module selection is wrong\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}