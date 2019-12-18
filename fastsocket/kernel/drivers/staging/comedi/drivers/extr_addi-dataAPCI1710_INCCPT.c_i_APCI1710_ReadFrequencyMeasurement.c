#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_9__ {scalar_t__ ui_Address; } ;
struct TYPE_14__ {TYPE_6__* s_ModuleInfo; TYPE_2__ s_BoardInfos; } ;
struct TYPE_10__ {int b_ModeRegister1; } ;
struct TYPE_11__ {TYPE_3__ s_ByteModeRegister; } ;
struct TYPE_8__ {int b_CounterInit; int b_FrequencyMeasurementInit; int b_FrequencyMeasurementEnable; } ;
struct TYPE_12__ {TYPE_4__ s_ModeRegister; TYPE_1__ s_InitFlag; } ;
struct TYPE_13__ {TYPE_5__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 int APCI1710_16BIT_COUNTER ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_7__* devpriv ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI1710_ReadFrequencyMeasurement(struct comedi_device *dev,
	unsigned char b_ModulNbr,
	unsigned char *pb_Status, unsigned char *pb_UDStatus, unsigned int *pul_ReadValue)
{
	int i_ReturnValue = 0;
	unsigned int ui_16BitValue;
	unsigned int dw_StatusReg;

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /*******************************/
		/* Test if counter initialised */
	   /*******************************/

		if (devpriv->
			s_ModuleInfo[b_ModulNbr].
			s_SiemensCounterInfo.s_InitFlag.b_CounterInit == 1) {
	      /********************************************/
			/* Test if frequency mesurement initialised */
	      /********************************************/

			if (devpriv->
				s_ModuleInfo[b_ModulNbr].
				s_SiemensCounterInfo.
				s_InitFlag.b_FrequencyMeasurementInit == 1) {
		 /******************/
				/* Test if enable */
		 /******************/

				if (devpriv->
					s_ModuleInfo[b_ModulNbr].
					s_SiemensCounterInfo.
					s_InitFlag.
					b_FrequencyMeasurementEnable == 1) {
		    /*******************/
					/* Read the status */
		    /*******************/

					dw_StatusReg =
						inl(devpriv->s_BoardInfos.
						ui_Address + 32 +
						(64 * b_ModulNbr));

		    /**************************/
					/* Test if frequency stop */
		    /**************************/

					if (dw_StatusReg & 1) {
						*pb_Status = 2;
						*pb_UDStatus =
							(unsigned char) ((dw_StatusReg >>
								1) & 3);

		       /******************/
						/* Read the value */
		       /******************/

						*pul_ReadValue =
							inl(devpriv->
							s_BoardInfos.
							ui_Address + 28 +
							(64 * b_ModulNbr));

						if (*pb_UDStatus == 0) {
			  /*************************/
							/* Test the counter mode */
			  /*************************/

							if ((devpriv->s_ModuleInfo[b_ModulNbr].s_SiemensCounterInfo.s_ModeRegister.s_ByteModeRegister.b_ModeRegister1 & APCI1710_16BIT_COUNTER) == APCI1710_16BIT_COUNTER) {
			     /****************************************/
								/* Test if 16-bit counter 1 pulse occur */
			     /****************************************/

								if ((*pul_ReadValue & 0xFFFFU) != 0) {
									ui_16BitValue
										=
										(unsigned int)
										*
										pul_ReadValue
										&
										0xFFFFU;
									*pul_ReadValue
										=
										(*pul_ReadValue
										&
										0xFFFF0000UL)
										|
										(0xFFFFU
										-
										ui_16BitValue);
								}

			     /****************************************/
								/* Test if 16-bit counter 2 pulse occur */
			     /****************************************/

								if ((*pul_ReadValue & 0xFFFF0000UL) != 0) {
									ui_16BitValue
										=
										(unsigned int)
										(
										(*pul_ReadValue
											>>
											16)
										&
										0xFFFFU);
									*pul_ReadValue
										=
										(*pul_ReadValue
										&
										0xFFFFUL)
										|
										(
										(0xFFFFU - ui_16BitValue) << 16);
								}
							} else {
								if (*pul_ReadValue != 0) {
									*pul_ReadValue
										=
										0xFFFFFFFFUL
										-
										*pul_ReadValue;
								}
							}
						} else {
							if (*pb_UDStatus == 1) {
			     /****************************************/
								/* Test if 16-bit counter 2 pulse occur */
			     /****************************************/

								if ((*pul_ReadValue & 0xFFFF0000UL) != 0) {
									ui_16BitValue
										=
										(unsigned int)
										(
										(*pul_ReadValue
											>>
											16)
										&
										0xFFFFU);
									*pul_ReadValue
										=
										(*pul_ReadValue
										&
										0xFFFFUL)
										|
										(
										(0xFFFFU - ui_16BitValue) << 16);
								}
							} else {
								if (*pb_UDStatus
									== 2) {
				/****************************************/
									/* Test if 16-bit counter 1 pulse occur */
				/****************************************/

									if ((*pul_ReadValue & 0xFFFFU) != 0) {
										ui_16BitValue
											=
											(unsigned int)
											*
											pul_ReadValue
											&
											0xFFFFU;
										*pul_ReadValue
											=
											(*pul_ReadValue
											&
											0xFFFF0000UL)
											|
											(0xFFFFU
											-
											ui_16BitValue);
									}
								}
							}
						}
					} else {
						*pb_Status = 1;
						*pb_UDStatus = 0;
					}
				} else {
					*pb_Status = 0;
					*pb_UDStatus = 0;
				}
			} else {
		 /***********************************************/
				/* Frequency measurement logic not initialised */
		 /***********************************************/

				DPRINTK("Frequency measurement logic not initialised\n");
				i_ReturnValue = -4;
			}
		} else {
	      /****************************************/
			/* Counter not initialised see function */
			/* "i_APCI1710_InitCounter"             */
	      /****************************************/

			DPRINTK("Counter not initialised\n");
			i_ReturnValue = -3;
		}
	} else {
	   /*************************************************/
		/* The selected module number parameter is wrong */
	   /*************************************************/

		DPRINTK("The selected module number parameter is wrong\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}