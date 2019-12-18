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
struct TYPE_8__ {TYPE_3__ s_BoardInfos; TYPE_2__* s_ModuleInfo; } ;
struct TYPE_5__ {int b_DigitalInit; int b_ChannelAMode; int b_ChannelBMode; int b_OutputMemoryEnabled; unsigned char dw_OutputMemory; } ;
struct TYPE_6__ {TYPE_1__ s_DigitalIOInfo; } ;

/* Variables and functions */
 int APCI1710_DIGITAL_IO ; 
#define  APCI1710_INPUT 131 
#define  APCI1710_OFF 130 
#define  APCI1710_ON 129 
#define  APCI1710_OUTPUT 128 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 

int i_APCI1710_InsnBitsDigitalIOPortOnOff(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_WriteValue = 0;
	unsigned int dw_StatusReg;
	unsigned char b_ModulNbr, b_PortValue;
	unsigned char b_PortOperation, b_PortOnOFF;

	unsigned char *pb_PortValue;

	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_PortOperation = (unsigned char) data[0];	/*  Input or output */
	b_PortOnOFF = (unsigned char) data[1];	/*  if output then On or Off */
	b_PortValue = (unsigned char) data[2];	/*  if out put then Value */
	i_ReturnValue = insn->n;
	pb_PortValue = (unsigned char *) &data[0];
/* if input then read value */

	switch (b_PortOperation) {
	case APCI1710_INPUT:
		/**************************/
		/* Test the module number */
		/**************************/

		if (b_ModulNbr < 4) {
			/*******************************/
			/* Test if digital I/O counter */
			/*******************************/

			if ((devpriv->s_BoardInfos.
					dw_MolduleConfiguration[b_ModulNbr] &
					0xFFFF0000UL) == APCI1710_DIGITAL_IO) {
				/**********************************************/
				/* Test if the digital I/O module initialised */
				/**********************************************/

				if (devpriv->s_ModuleInfo[b_ModulNbr].
					s_DigitalIOInfo.b_DigitalInit == 1) {
					/**************************/
					/* Read all digital input */
					/**************************/

					/* INPDW (ps_APCI1710Variable->
					 * s_Board [b_BoardHandle].
					 * s_BoardInfos.
					 * ui_Address + (64 * b_ModulNbr),
					 * &dw_StatusReg);
					 */

					dw_StatusReg =
						inl(devpriv->s_BoardInfos.
						ui_Address + (64 * b_ModulNbr));
					*pb_PortValue =
						(unsigned char) (dw_StatusReg ^ 0x1C);

				} else {
					/*******************************/
					/* Digital I/O not initialised */
					/*******************************/

					i_ReturnValue = -4;
				}
			} else {
				/******************************************/
				/* The module is not a digital I/O module */
				/******************************************/

				i_ReturnValue = -3;
			}
		} else {
	   /***********************/
			/* Module number error */
	   /***********************/

			i_ReturnValue = -2;
		}

		break;

	case APCI1710_OUTPUT:
	/**************************/
		/* Test the module number */
	/**************************/

		if (b_ModulNbr < 4) {
	   /*******************************/
			/* Test if digital I/O counter */
	   /*******************************/

			if ((devpriv->s_BoardInfos.
					dw_MolduleConfiguration[b_ModulNbr] &
					0xFFFF0000UL) == APCI1710_DIGITAL_IO) {
	      /**********************************************/
				/* Test if the digital I/O module initialised */
	      /**********************************************/

				if (devpriv->s_ModuleInfo[b_ModulNbr].
					s_DigitalIOInfo.b_DigitalInit == 1) {
		 /***********************/
					/* Test the port value */
		 /***********************/

					if (b_PortValue <= 7) {
		    /***********************************/
						/* Test the digital output channel */
		    /***********************************/

		    /**************************/
						/* Test if channel A used */
		    /**************************/

						if ((b_PortValue & 2) == 2) {
							if (devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_DigitalIOInfo.
								b_ChannelAMode
								!= 1) {
			  /*******************************************/
								/* The digital channel A is used for input */
			  /*******************************************/

								i_ReturnValue =
									-6;
							}
						}	/*  if ((b_PortValue & 2) == 2) */

						/**************************/
						/* Test if channel B used */
						/**************************/

						if ((b_PortValue & 4) == 4) {
							if (devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_DigitalIOInfo.
								b_ChannelBMode
								!= 1) {
								/*******************************************/
								/* The digital channel B is used for input */
								/*******************************************/

								i_ReturnValue =
									-7;
							}
						}	/*  if ((b_PortValue & 4) == 4) */

						/***********************/
						/* Test if error occur */
						/***********************/

						if (i_ReturnValue >= 0) {

							/* if(data[1]) { */

							switch (b_PortOnOFF) {
								/*********************************/
								/* Test if set Port ON                   */
								/*********************************/

							case APCI1710_ON:

								/*********************************/
								/* Test if output memory enabled */
								/*********************************/

								if (devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_DigitalIOInfo.
									b_OutputMemoryEnabled
									== 1) {
									dw_WriteValue
										=
										devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_DigitalIOInfo.
										dw_OutputMemory
										|
										b_PortValue;

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_DigitalIOInfo.
										dw_OutputMemory
										=
										dw_WriteValue;
								} else {
									dw_WriteValue
										=
										b_PortValue;
								}
								break;

								/*  If Set PORT  OFF */
							case APCI1710_OFF:

			   /*********************************/
								/* Test if output memory enabled */
		       /*********************************/

								if (devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_DigitalIOInfo.
									b_OutputMemoryEnabled
									== 1) {
									dw_WriteValue
										=
										devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_DigitalIOInfo.
										dw_OutputMemory
										&
										(0xFFFFFFFFUL
										-
										b_PortValue);

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_DigitalIOInfo.
										dw_OutputMemory
										=
										dw_WriteValue;
								} else {
									/*****************************/
									/* Digital Output Memory OFF */
									/*****************************/

									i_ReturnValue
										=
										-8;
								}
							}	/*  switch */

							/*******************/
							/* Write the value */
							/*******************/

							/* OUTPDW (ps_APCI1710Variable->
							 * s_Board [b_BoardHandle].
							 * s_BoardInfos.
							 * ui_Address + (64 * b_ModulNbr),
							 * dw_WriteValue); */

							outl(dw_WriteValue,
								devpriv->
								s_BoardInfos.
								ui_Address +
								(64 * b_ModulNbr));
						}
					} else {
						/**********************/
						/* Output value wrong */
						/**********************/

						i_ReturnValue = -4;
					}
				} else {
					/*******************************/
					/* Digital I/O not initialised */
					/*******************************/

					i_ReturnValue = -5;
				}
			} else {
	      /******************************************/
				/* The module is not a digital I/O module */
	      /******************************************/

				i_ReturnValue = -3;
			}
		} else {
	   /***********************/
			/* Module number error */
	   /***********************/

			i_ReturnValue = -2;
		}
		break;

	default:
		i_ReturnValue = -9;
		DPRINTK("NO INPUT/OUTPUT specified\n");
	}			/* switch INPUT / OUTPUT */
	return i_ReturnValue;
}