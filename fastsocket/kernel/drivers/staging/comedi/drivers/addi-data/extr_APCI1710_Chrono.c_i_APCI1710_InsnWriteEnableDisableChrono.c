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
struct TYPE_7__ {int* dw_MolduleConfiguration; int /*<<< orphan*/  ui_Address; } ;
struct TYPE_8__ {TYPE_3__ s_BoardInfos; TYPE_2__* s_ModuleInfo; int /*<<< orphan*/  tsk_Current; } ;
struct TYPE_5__ {int b_ChronoInit; unsigned char b_InterruptMask; unsigned char b_CycleMode; int dw_ConfigReg; } ;
struct TYPE_6__ {TYPE_1__ s_ChronoModuleInfo; } ;

/* Variables and functions */
 int APCI1710_CHRONOMETER ; 
 unsigned char APCI1710_CONTINUOUS ; 
#define  APCI1710_DISABLE 129 
#define  APCI1710_ENABLE 128 
 unsigned char APCI1710_SINGLE ; 
 unsigned char CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  current ; 
 TYPE_4__* devpriv ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

int i_APCI1710_InsnWriteEnableDisableChrono(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned char b_ModulNbr, b_CycleMode, b_InterruptEnable, b_Action;
	b_ModulNbr = CR_AREF(insn->chanspec);
	b_Action = (unsigned char) data[0];
	b_CycleMode = (unsigned char) data[1];
	b_InterruptEnable = (unsigned char) data[2];
	i_ReturnValue = insn->n;

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /***********************/
		/* Test if chronometer */
	   /***********************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_CHRONOMETER) {
	      /***********************************/
			/* Test if chronometer initialised */
	      /***********************************/

			if (devpriv->s_ModuleInfo[b_ModulNbr].
				s_ChronoModuleInfo.b_ChronoInit == 1) {

				switch (b_Action) {

				case APCI1710_ENABLE:

		 /*********************************/
					/* Test the cycle mode parameter */
		 /*********************************/

					if ((b_CycleMode == APCI1710_SINGLE)
						|| (b_CycleMode ==
							APCI1710_CONTINUOUS)) {
		    /***************************/
						/* Test the interrupt flag */
		    /***************************/

						if ((b_InterruptEnable ==
								APCI1710_ENABLE)
							|| (b_InterruptEnable ==
								APCI1710_DISABLE))
						{

			  /***************************/
							/* Save the interrupt flag */
			  /***************************/

							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_ChronoModuleInfo.
								b_InterruptMask
								=
								b_InterruptEnable;

			  /***********************/
							/* Save the cycle mode */
			  /***********************/

							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_ChronoModuleInfo.
								b_CycleMode =
								b_CycleMode;

							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_ChronoModuleInfo.
								dw_ConfigReg =
								(devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_ChronoModuleInfo.
								dw_ConfigReg &
								0x8F) | ((1 &
									b_InterruptEnable)
								<< 5) | ((1 &
									b_CycleMode)
								<< 6) | 0x10;

			  /*****************************/
							/* Test if interrupt enabled */
			  /*****************************/

							if (b_InterruptEnable ==
								APCI1710_ENABLE)
							{
			     /****************************/
								/* Clear the interrupt flag */
			     /****************************/

								outl(devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_ChronoModuleInfo.
									dw_ConfigReg,
									devpriv->
									s_BoardInfos.
									ui_Address
									+ 32 +
									(64 * b_ModulNbr));
								devpriv->tsk_Current = current;	/*  Save the current process task structure */
							}

			  /***********************************/
							/* Enable or disable the interrupt */
							/* Enable the chronometer          */
			  /***********************************/

							outl(devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_ChronoModuleInfo.
								dw_ConfigReg,
								devpriv->
								s_BoardInfos.
								ui_Address +
								16 +
								(64 * b_ModulNbr));

			  /*************************/
							/* Clear status register */
			  /*************************/

							outl(0, devpriv->
								s_BoardInfos.
								ui_Address +
								36 +
								(64 * b_ModulNbr));

						}	/*  if ((b_InterruptEnable == APCI1710_ENABLE) || (b_InterruptEnable == APCI1710_DISABLE)) */
						else {
		       /********************************/
							/* Interrupt parameter is wrong */
		       /********************************/

							DPRINTK("Interrupt parameter is wrong\n");
							i_ReturnValue = -6;
						}	/*  if ((b_InterruptEnable == APCI1710_ENABLE) || (b_InterruptEnable == APCI1710_DISABLE)) */
					}	/*  if ((b_CycleMode == APCI1710_SINGLE) || (b_CycleMode == APCI1710_CONTINUOUS)) */
					else {
		    /***********************************************/
						/* Chronometer acquisition mode cycle is wrong */
		    /***********************************************/

						DPRINTK("Chronometer acquisition mode cycle is wrong\n");
						i_ReturnValue = -5;
					}	/*  if ((b_CycleMode == APCI1710_SINGLE) || (b_CycleMode == APCI1710_CONTINUOUS)) */
					break;

				case APCI1710_DISABLE:

					devpriv->s_ModuleInfo[b_ModulNbr].
						s_ChronoModuleInfo.
						b_InterruptMask = 0;

					devpriv->s_ModuleInfo[b_ModulNbr].
						s_ChronoModuleInfo.
						dw_ConfigReg =
						devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_ChronoModuleInfo.
						dw_ConfigReg & 0x2F;

		 /***************************/
					/* Disable the interrupt   */
					/* Disable the chronometer */
		 /***************************/

					outl(devpriv->s_ModuleInfo[b_ModulNbr].
						s_ChronoModuleInfo.dw_ConfigReg,
						devpriv->s_BoardInfos.
						ui_Address + 16 +
						(64 * b_ModulNbr));

		 /***************************/
					/* Test if continuous mode */
		 /***************************/

					if (devpriv->s_ModuleInfo[b_ModulNbr].
						s_ChronoModuleInfo.
						b_CycleMode ==
						APCI1710_CONTINUOUS) {
		    /*************************/
						/* Clear status register */
		    /*************************/

						outl(0, devpriv->s_BoardInfos.
							ui_Address + 36 +
							(64 * b_ModulNbr));
					}
					break;

				default:
					DPRINTK("Inputs wrong! Enable or Disable chrono\n");
					i_ReturnValue = -8;
				}	/*  switch ENABLE/DISABLE */
			} else {
		 /*******************************/
				/* Chronometer not initialised */
		 /*******************************/

				DPRINTK("Chronometer not initialised\n");
				i_ReturnValue = -4;
			}
		} else {
	      /******************************************/
			/* The module is not a Chronometer module */
	      /******************************************/

			DPRINTK("The module is not a Chronometer module\n");
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