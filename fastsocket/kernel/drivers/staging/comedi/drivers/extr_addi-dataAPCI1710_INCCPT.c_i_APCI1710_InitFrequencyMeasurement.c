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
struct TYPE_9__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_14__ {TYPE_6__* s_ModuleInfo; TYPE_2__ s_BoardInfos; } ;
struct TYPE_8__ {int b_CounterInit; int b_FrequencyMeasurementInit; } ;
struct TYPE_10__ {int b_ModeRegister4; } ;
struct TYPE_11__ {TYPE_3__ s_ByteModeRegister; } ;
struct TYPE_12__ {TYPE_1__ s_InitFlag; TYPE_4__ s_ModeRegister; } ;
struct TYPE_13__ {TYPE_5__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 unsigned char APCI1710_30MHZ ; 
 unsigned char APCI1710_33MHZ ; 
 unsigned char APCI1710_40MHZ ; 
 int APCI1710_DISABLE_40MHZ_FREQUENCY ; 
 int APCI1710_ENABLE_40MHZ_FREQUENCY ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_7__* devpriv ; 
 int /*<<< orphan*/  fpu_begin () ; 
 int /*<<< orphan*/  fpu_end () ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI1710_InitFrequencyMeasurement(struct comedi_device *dev,
	unsigned char b_ModulNbr,
	unsigned char b_PCIInputClock,
	unsigned char b_TimingUnity,
	unsigned int ul_TimingInterval, unsigned int *pul_RealTimingInterval)
{
	int i_ReturnValue = 0;
	unsigned int ul_TimerValue = 0;
	double d_RealTimingInterval;
	unsigned int dw_Status = 0;

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
	      /**************************/
			/* Test the PCI bus clock */
	      /**************************/

			if ((b_PCIInputClock == APCI1710_30MHZ) ||
				(b_PCIInputClock == APCI1710_33MHZ) ||
				(b_PCIInputClock == APCI1710_40MHZ)) {
		 /************************/
				/* Test the timing unit */
		 /************************/

				if (b_TimingUnity <= 2) {
		    /**********************************/
					/* Test the base timing selection */
		    /**********************************/

					if (((b_PCIInputClock == APCI1710_30MHZ)
							&& (b_TimingUnity == 0)
							&& (ul_TimingInterval >=
								266)
							&& (ul_TimingInterval <=
								8738133UL))
						|| ((b_PCIInputClock ==
								APCI1710_30MHZ)
							&& (b_TimingUnity == 1)
							&& (ul_TimingInterval >=
								1)
							&& (ul_TimingInterval <=
								8738UL))
						|| ((b_PCIInputClock ==
								APCI1710_30MHZ)
							&& (b_TimingUnity == 2)
							&& (ul_TimingInterval >=
								1)
							&& (ul_TimingInterval <=
								8UL))
						|| ((b_PCIInputClock ==
								APCI1710_33MHZ)
							&& (b_TimingUnity == 0)
							&& (ul_TimingInterval >=
								242)
							&& (ul_TimingInterval <=
								7943757UL))
						|| ((b_PCIInputClock ==
								APCI1710_33MHZ)
							&& (b_TimingUnity == 1)
							&& (ul_TimingInterval >=
								1)
							&& (ul_TimingInterval <=
								7943UL))
						|| ((b_PCIInputClock ==
								APCI1710_33MHZ)
							&& (b_TimingUnity == 2)
							&& (ul_TimingInterval >=
								1)
							&& (ul_TimingInterval <=
								7UL))
						|| ((b_PCIInputClock ==
								APCI1710_40MHZ)
							&& (b_TimingUnity == 0)
							&& (ul_TimingInterval >=
								200)
							&& (ul_TimingInterval <=
								6553500UL))
						|| ((b_PCIInputClock ==
								APCI1710_40MHZ)
							&& (b_TimingUnity == 1)
							&& (ul_TimingInterval >=
								1)
							&& (ul_TimingInterval <=
								6553UL))
						|| ((b_PCIInputClock ==
								APCI1710_40MHZ)
							&& (b_TimingUnity == 2)
							&& (ul_TimingInterval >=
								1)
							&& (ul_TimingInterval <=
								6UL))) {
		       /**********************/
						/* Test if 40MHz used */
		       /**********************/

						if (b_PCIInputClock ==
							APCI1710_40MHZ) {
			  /******************************/
							/* Test if firmware >= Rev1.5 */
			  /******************************/

							if ((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF) >= 0x3135) {
			     /*********************************/
								/* Test if 40MHz quartz on board */
			     /*********************************/

								/*INPDW (ps_APCI1710Variable->
								   s_Board [b_BoardHandle].
								   s_BoardInfos.
								   ui_Address + 36 + (64 * b_ModulNbr), &dw_Status); */
								dw_Status =
									inl
									(devpriv->
									s_BoardInfos.
									ui_Address
									+ 36 +
									(64 * b_ModulNbr));

			     /******************************/
								/* Test the quartz flag (DQ0) */
			     /******************************/

								if ((dw_Status & 1) != 1) {
				/*****************************/
									/* 40MHz quartz not on board */
				/*****************************/

									DPRINTK("40MHz quartz not on board\n");
									i_ReturnValue
										=
										-7;
								}
							} else {
			     /*****************************/
								/* 40MHz quartz not on board */
			     /*****************************/
								DPRINTK("40MHz quartz not on board\n");
								i_ReturnValue =
									-7;
							}
						}	/*  if (b_PCIInputClock == APCI1710_40MHZ) */

		       /***************************/
						/* Test if not error occur */
		       /***************************/

						if (i_ReturnValue == 0) {
			  /****************************/
							/* Test the INC_CPT version */
			  /****************************/

							if ((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF) >= 0x3131) {

				/**********************/
								/* Test if 40MHz used */
				/**********************/

								if (b_PCIInputClock == APCI1710_40MHZ) {
				   /*********************************/
									/* Enable the 40MHz quarz (DQ30) */
				   /*********************************/

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_SiemensCounterInfo.
										s_ModeRegister.
										s_ByteModeRegister.
										b_ModeRegister4
										=
										devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_SiemensCounterInfo.
										s_ModeRegister.
										s_ByteModeRegister.
										b_ModeRegister4
										|
										APCI1710_ENABLE_40MHZ_FREQUENCY;
								}	/*  if (b_PCIInputClock == APCI1710_40MHZ) */
								else {
				   /**********************************/
									/* Disable the 40MHz quarz (DQ30) */
				   /**********************************/

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_SiemensCounterInfo.
										s_ModeRegister.
										s_ByteModeRegister.
										b_ModeRegister4
										=
										devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_SiemensCounterInfo.
										s_ModeRegister.
										s_ByteModeRegister.
										b_ModeRegister4
										&
										APCI1710_DISABLE_40MHZ_FREQUENCY;

								}	/*  if (b_PCIInputClock == APCI1710_40MHZ) */

			     /********************************/
								/* Calculate the division fator */
			     /********************************/

								fpu_begin();
								switch (b_TimingUnity) {
				/******/
									/* ns */
				/******/

								case 0:

					/******************/
									/* Timer 0 factor */
					/******************/

									ul_TimerValue
										=
										(unsigned int)
										(ul_TimingInterval
										*
										(0.00025 * b_PCIInputClock));

					/*******************/
									/* Round the value */
					/*******************/

									if ((double)((double)ul_TimingInterval * (0.00025 * (double)b_PCIInputClock)) >= ((double)((double)ul_TimerValue + 0.5))) {
										ul_TimerValue
											=
											ul_TimerValue
											+
											1;
									}

					/*****************************/
									/* Calculate the real timing */
					/*****************************/

									*pul_RealTimingInterval
										=
										(unsigned int)
										(ul_TimerValue
										/
										(0.00025 * (double)b_PCIInputClock));
									d_RealTimingInterval
										=
										(double)
										ul_TimerValue
										/
										(0.00025
										*
										(double)
										b_PCIInputClock);

									if ((double)((double)ul_TimerValue / (0.00025 * (double)b_PCIInputClock)) >= (double)((double)*pul_RealTimingInterval + 0.5)) {
										*pul_RealTimingInterval
											=
											*pul_RealTimingInterval
											+
											1;
									}

									ul_TimingInterval
										=
										ul_TimingInterval
										-
										1;
									ul_TimerValue
										=
										ul_TimerValue
										-
										2;

									break;

				/******/
									/* æs */
				/******/

								case 1:

					/******************/
									/* Timer 0 factor */
					/******************/

									ul_TimerValue
										=
										(unsigned int)
										(ul_TimingInterval
										*
										(0.25 * b_PCIInputClock));

					/*******************/
									/* Round the value */
					/*******************/

									if ((double)((double)ul_TimingInterval * (0.25 * (double)b_PCIInputClock)) >= ((double)((double)ul_TimerValue + 0.5))) {
										ul_TimerValue
											=
											ul_TimerValue
											+
											1;
									}

					/*****************************/
									/* Calculate the real timing */
					/*****************************/

									*pul_RealTimingInterval
										=
										(unsigned int)
										(ul_TimerValue
										/
										(0.25 * (double)b_PCIInputClock));
									d_RealTimingInterval
										=
										(double)
										ul_TimerValue
										/
										(
										(double)
										0.25
										*
										(double)
										b_PCIInputClock);

									if ((double)((double)ul_TimerValue / (0.25 * (double)b_PCIInputClock)) >= (double)((double)*pul_RealTimingInterval + 0.5)) {
										*pul_RealTimingInterval
											=
											*pul_RealTimingInterval
											+
											1;
									}

									ul_TimingInterval
										=
										ul_TimingInterval
										-
										1;
									ul_TimerValue
										=
										ul_TimerValue
										-
										2;

									break;

				/******/
									/* ms */
				/******/

								case 2:

					/******************/
									/* Timer 0 factor */
					/******************/

									ul_TimerValue
										=
										ul_TimingInterval
										*
										(250.0
										*
										b_PCIInputClock);

					/*******************/
									/* Round the value */
					/*******************/

									if ((double)((double)ul_TimingInterval * (250.0 * (double)b_PCIInputClock)) >= ((double)((double)ul_TimerValue + 0.5))) {
										ul_TimerValue
											=
											ul_TimerValue
											+
											1;
									}

					/*****************************/
									/* Calculate the real timing */
					/*****************************/

									*pul_RealTimingInterval
										=
										(unsigned int)
										(ul_TimerValue
										/
										(250.0 * (double)b_PCIInputClock));
									d_RealTimingInterval
										=
										(double)
										ul_TimerValue
										/
										(250.0
										*
										(double)
										b_PCIInputClock);

									if ((double)((double)ul_TimerValue / (250.0 * (double)b_PCIInputClock)) >= (double)((double)*pul_RealTimingInterval + 0.5)) {
										*pul_RealTimingInterval
											=
											*pul_RealTimingInterval
											+
											1;
									}

									ul_TimingInterval
										=
										ul_TimingInterval
										-
										1;
									ul_TimerValue
										=
										ul_TimerValue
										-
										2;

									break;
								}

								fpu_end();
			     /*************************/
								/* Write the timer value */
			     /*************************/

								outl(ul_TimerValue, devpriv->s_BoardInfos.ui_Address + 32 + (64 * b_ModulNbr));

			     /*******************************/
								/* Set the initialisation flag */
			     /*******************************/

								devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_SiemensCounterInfo.
									s_InitFlag.
									b_FrequencyMeasurementInit
									= 1;
							} else {
			     /***************************/
								/* Counter not initialised */
			     /***************************/

								DPRINTK("Counter not initialised\n");
								i_ReturnValue =
									-3;
							}
						}	/*  if (i_ReturnValue == 0) */
					} else {
		       /**********************************/
						/* Base timing selection is wrong */
		       /**********************************/

						DPRINTK("Base timing selection is wrong\n");
						i_ReturnValue = -6;
					}
				} else {
		    /***********************************/
					/* Timing unity selection is wrong */
		    /***********************************/

					DPRINTK("Timing unity selection is wrong\n");
					i_ReturnValue = -5;
				}
			} else {
		 /*****************************************/
				/* The selected PCI input clock is wrong */
		 /*****************************************/

				DPRINTK("The selected PCI input clock is wrong\n");
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