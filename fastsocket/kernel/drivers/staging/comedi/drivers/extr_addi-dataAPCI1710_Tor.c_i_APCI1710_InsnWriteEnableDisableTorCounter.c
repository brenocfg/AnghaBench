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
struct TYPE_9__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__ s_BoardInfos; TYPE_3__* s_ModuleInfo; int /*<<< orphan*/  tsk_Current; } ;
struct TYPE_7__ {TYPE_1__* s_TorCounterInfo; } ;
struct TYPE_8__ {TYPE_2__ s_TorCounterModuleInfo; } ;
struct TYPE_6__ {unsigned char b_InterruptEnable; } ;

/* Variables and functions */
 unsigned char APCI1710_CONTINUOUS ; 
#define  APCI1710_DISABLE 129 
#define  APCI1710_ENABLE 128 
 unsigned char APCI1710_SINGLE ; 
 int APCI1710_TOR_COUNTER ; 
 unsigned char APCI1710_TOR_DOUBLE_MODE ; 
 unsigned char APCI1710_TOR_QUADRUPLE_MODE ; 
 unsigned char APCI1710_TOR_SIMPLE_MODE ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  current ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

int i_APCI1710_InsnWriteEnableDisableTorCounter(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;
	unsigned int dw_DummyRead;
	unsigned int dw_ConfigReg;
	unsigned char b_ModulNbr, b_Action;
	unsigned char b_TorCounter;
	unsigned char b_InputMode;
	unsigned char b_ExternGate;
	unsigned char b_CycleMode;
	unsigned char b_InterruptEnable;

	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_Action = (unsigned char) data[0];	/*  enable or disable */
	b_TorCounter = (unsigned char) data[1];
	b_InputMode = (unsigned char) data[2];
	b_ExternGate = (unsigned char) data[3];
	b_CycleMode = (unsigned char) data[4];
	b_InterruptEnable = (unsigned char) data[5];
	i_ReturnValue = insn->n;;
	devpriv->tsk_Current = current;	/*  Save the current process task structure */
	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /***********************/
		/* Test if tor counter */
	   /***********************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_TOR_COUNTER) {
	      /**********************************/
			/* Test the tor counter selection */
	      /**********************************/

			if (b_TorCounter <= 1) {
				switch (b_Action)	/*  Enable or Disable */
				{
				case APCI1710_ENABLE:
		 /***********************************/
					/* Test if tor counter initialised */
		 /***********************************/

					dw_Status =
						inl(devpriv->s_BoardInfos.
						ui_Address + 8 +
						(16 * b_TorCounter) +
						(64 * b_ModulNbr));

					if (dw_Status & 0x10) {
		    /******************************/
						/* Test the input signal mode */
		    /******************************/

						if (b_InputMode == 0 ||
							b_InputMode == 1 ||
							b_InputMode ==
							APCI1710_TOR_SIMPLE_MODE
							|| b_InputMode ==
							APCI1710_TOR_DOUBLE_MODE
							|| b_InputMode ==
							APCI1710_TOR_QUADRUPLE_MODE)
						{
		       /************************************/
							/* Test the extern gate signal mode */
		       /************************************/

							if (b_ExternGate == 0
								|| b_ExternGate
								== 1
								|| b_InputMode >
								1) {
			  /*********************************/
								/* Test the cycle mode parameter */
			  /*********************************/

								if ((b_CycleMode == APCI1710_SINGLE) || (b_CycleMode == APCI1710_CONTINUOUS)) {
			     /***************************/
									/* Test the interrupt flag */
			     /***************************/

									if ((b_InterruptEnable == APCI1710_ENABLE) || (b_InterruptEnable == APCI1710_DISABLE)) {

				   /***************************/
										/* Save the interrupt mode */
				   /***************************/

										devpriv->
											s_ModuleInfo
											[b_ModulNbr].
											s_TorCounterModuleInfo.
											s_TorCounterInfo
											[b_TorCounter].
											b_InterruptEnable
											=
											b_InterruptEnable;

				   /*******************/
										/* Get the command */
				   /*******************/

										dw_ConfigReg
											=
											inl
											(devpriv->
											s_BoardInfos.
											ui_Address
											+
											4
											+
											(16 * b_TorCounter) + (64 * b_ModulNbr));

										dw_ConfigReg
											=
											(dw_ConfigReg
											>>
											4)
											&
											0x30;

				   /********************************/
										/* Test if not direct mode used */
				   /********************************/

										if (b_InputMode > 1) {
				      /*******************************/
											/* Extern gate can not be used */
				      /*******************************/

											b_ExternGate
												=
												0;

				      /*******************************************/
											/* Enable the extern gate for the Signal B */
				      /*******************************************/

											dw_ConfigReg
												=
												dw_ConfigReg
												|
												0x40;

				      /***********************/
											/* Test if simple mode */
				      /***********************/

											if (b_InputMode == APCI1710_TOR_SIMPLE_MODE) {
					 /**************************/
												/* Enable the sinple mode */
					 /**************************/

												dw_ConfigReg
													=
													dw_ConfigReg
													|
													0x780;

											}	/*  if (b_InputMode == APCI1710_TOR_SIMPLE_MODE) */

				      /***********************/
											/* Test if double mode */
				      /***********************/

											if (b_InputMode == APCI1710_TOR_DOUBLE_MODE) {
					 /**************************/
												/* Enable the double mode */
					 /**************************/

												dw_ConfigReg
													=
													dw_ConfigReg
													|
													0x180;

											}	/*  if (b_InputMode == APCI1710_TOR_DOUBLE_MODE) */

											b_InputMode
												=
												0;
										}	/*  if (b_InputMode > 1) */

				   /*******************/
										/* Set the command */
				   /*******************/

										dw_ConfigReg
											=
											dw_ConfigReg
											|
											b_CycleMode
											|
											(b_InterruptEnable
											*
											2)
											|
											(b_InputMode
											*
											4)
											|
											(b_ExternGate
											*
											8);

				   /*****************************/
										/* Clear the status register */
				   /*****************************/

										dw_DummyRead
											=
											inl
											(devpriv->
											s_BoardInfos.
											ui_Address
											+
											0
											+
											(16 * b_TorCounter) + (64 * b_ModulNbr));

				   /***************************************/
										/* Clear the interrupt status register */
				   /***************************************/

										dw_DummyRead
											=
											inl
											(devpriv->
											s_BoardInfos.
											ui_Address
											+
											12
											+
											(16 * b_TorCounter) + (64 * b_ModulNbr));

				   /********************/
										/* Set the commando */
				   /********************/

										outl(dw_ConfigReg, devpriv->s_BoardInfos.ui_Address + 4 + (16 * b_TorCounter) + (64 * b_ModulNbr));

				   /****************/
										/* Set the gate */
				   /****************/

										outl(1, devpriv->s_BoardInfos.ui_Address + 8 + (16 * b_TorCounter) + (64 * b_ModulNbr));

									}	/*  if ((b_InterruptEnable == APCI1710_ENABLE) || (b_InterruptEnable == APCI1710_DISABLE)) */
									else {
				/********************************/
										/* Interrupt parameter is wrong */
				/********************************/

										DPRINTK("Interrupt parameter is wrong\n");
										i_ReturnValue
											=
											-9;
									}	/*  if ((b_InterruptEnable == APCI1710_ENABLE) || (b_InterruptEnable == APCI1710_DISABLE)) */
								}	/*  if ((b_CycleMode == APCI1710_SINGLE) || (b_CycleMode == APCI1710_CONTINUOUS)) */
								else {
			     /***********************************************/
									/* Tor counter acquisition mode cycle is wrong */
			     /***********************************************/

									DPRINTK("Tor counter acquisition mode cycle is wrong\n");
									i_ReturnValue
										=
										-8;
								}	/*  if ((b_CycleMode == APCI1710_SINGLE) || (b_CycleMode == APCI1710_CONTINUOUS)) */
							}	/*  if (b_ExternGate >= 0 && b_ExternGate <= 1) */
							else {
			  /***********************************/
								/* Extern gate input mode is wrong */
			  /***********************************/

								DPRINTK("Extern gate input mode is wrong\n");
								i_ReturnValue =
									-7;
							}	/*  if (b_ExternGate >= 0 && b_ExternGate <= 1) */
						}	/*  if (b_InputMode >= 0 && b_InputMode <= 1) */
						else {
		       /***************************************/
							/* Tor input signal selection is wrong */
		       /***************************************/

							DPRINTK("Tor input signal selection is wrong\n");
							i_ReturnValue = -6;
						}
					} else {
		    /*******************************/
						/* Tor counter not initialised */
		    /*******************************/

						DPRINTK("Tor counter not initialised\n");
						i_ReturnValue = -5;
					}
					break;

				case APCI1710_DISABLE:
			 /***********************************/
					/* Test if tor counter initialised */
		 /***********************************/

					dw_Status = inl(devpriv->s_BoardInfos.
						ui_Address + 8 +
						(16 * b_TorCounter) +
						(64 * b_ModulNbr));

		 /*******************************/
					/* Test if counter initialised */
		 /*******************************/

					if (dw_Status & 0x10) {
		    /***************************/
						/* Test if counter enabled */
		    /***************************/

						if (dw_Status & 0x1) {
		       /****************************/
							/* Clear the interrupt mode */
		       /****************************/
							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_TorCounterModuleInfo.
								s_TorCounterInfo
								[b_TorCounter].
								b_InterruptEnable
								=
								APCI1710_DISABLE;

		       /******************/
							/* Clear the gate */
		       /******************/

							outl(0, devpriv->
								s_BoardInfos.
								ui_Address + 8 +
								(16 * b_TorCounter) + (64 * b_ModulNbr));
						}	/*  if (dw_Status & 0x1) */
						else {
		       /***************************/
							/* Tor counter not enabled */
		       /***************************/

							DPRINTK("Tor counter not enabled \n");
							i_ReturnValue = -6;
						}	/*  if (dw_Status & 0x1) */
					}	/*  if (dw_Status & 0x10) */
					else {
		    /*******************************/
						/* Tor counter not initialised */
		    /*******************************/

						DPRINTK("Tor counter not initialised\n");
						i_ReturnValue = -5;
					}	/*  // if (dw_Status & 0x10) */

				}	/*  switch */
			}	/*  if (b_TorCounter <= 1) */
			else {
		 /**********************************/
				/* Tor counter selection is wrong */
		 /**********************************/

				DPRINTK("Tor counter selection is wrong\n");
				i_ReturnValue = -4;
			}	/*  if (b_TorCounter <= 1) */
		} else {
	      /******************************************/
			/* The module is not a tor counter module */
	      /******************************************/

			DPRINTK("The module is not a tor counter module \n");
			i_ReturnValue = -3;
		}
	} else {
	   /***********************/
		/* Module number error */
	   /***********************/

		DPRINTK("Module number error \n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}