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
struct comedi_device {int dummy; } ;
struct TYPE_7__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_8__ {TYPE_3__ s_BoardInfos; TYPE_2__* s_ModuleInfo; } ;
struct TYPE_5__ {int b_ChronoInit; scalar_t__ b_CycleMode; } ;
struct TYPE_6__ {TYPE_1__ s_ChronoModuleInfo; } ;

/* Variables and functions */
 int APCI1710_CHRONOMETER ; 
 scalar_t__ APCI1710_CONTINUOUS ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

int i_APCI1710_ReadChronoValue(struct comedi_device *dev,
	unsigned char b_ModulNbr,
	unsigned int ui_TimeOut, unsigned char *pb_ChronoStatus, unsigned int *pul_ChronoValue)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;
	unsigned int dw_TimeOut = 0;

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

			if (devpriv->
				s_ModuleInfo[b_ModulNbr].
				s_ChronoModuleInfo.b_ChronoInit == 1) {
		 /*****************************/
				/* Test the timout parameter */
		 /*****************************/

				if ((ui_TimeOut >= 0)
					&& (ui_TimeOut <= 65535UL)) {

					for (;;) {
			  /*******************/
						/* Read the status */
			  /*******************/

						dw_Status =
							inl(devpriv->
							s_BoardInfos.
							ui_Address + 8 +
							(64 * b_ModulNbr));

			  /********************/
						/* Test if overflow */
			  /********************/

						if ((dw_Status & 8) == 8) {
			     /******************/
							/* Overflow occur */
			     /******************/

							*pb_ChronoStatus = 3;

			     /***************************/
							/* Test if continuous mode */
			     /***************************/

							if (devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_ChronoModuleInfo.
								b_CycleMode ==
								APCI1710_CONTINUOUS)
							{
				/*************************/
								/* Clear status register */
				/*************************/

								outl(0, devpriv->s_BoardInfos.ui_Address + 36 + (64 * b_ModulNbr));
							}

							break;
						}	/*  if ((dw_Status & 8) == 8) */
						else {
			     /*******************************/
							/* Test if measurement stopped */
			     /*******************************/

							if ((dw_Status & 2) ==
								2) {
				/***********************/
								/* A stop signal occur */
				/***********************/

								*pb_ChronoStatus
									= 2;

				/***************************/
								/* Test if continnous mode */
				/***************************/

								if (devpriv->
									s_ModuleInfo
									[b_ModulNbr].
									s_ChronoModuleInfo.
									b_CycleMode
									==
									APCI1710_CONTINUOUS)
								{
				   /*************************/
									/* Clear status register */
				   /*************************/

									outl(0, devpriv->s_BoardInfos.ui_Address + 36 + (64 * b_ModulNbr));
								}
								break;
							}	/*  if ((dw_Status & 2) == 2) */
							else {
				/*******************************/
								/* Test if measurement started */
				/*******************************/

								if ((dw_Status & 1) == 1) {
				   /************************/
									/* A start signal occur */
				   /************************/

									*pb_ChronoStatus
										=
										1;
								}	/*  if ((dw_Status & 1) == 1) */
								else {
				   /***************************/
									/* Measurement not started */
				   /***************************/

									*pb_ChronoStatus
										=
										0;
								}	/*  if ((dw_Status & 1) == 1) */
							}	/*  if ((dw_Status & 2) == 2) */
						}	/*  if ((dw_Status & 8) == 8) */

						if (dw_TimeOut == ui_TimeOut) {
			     /*****************/
							/* Timeout occur */
			     /*****************/

							break;
						} else {
			     /*************************/
							/* Increment the timeout */
			     /*************************/

							dw_TimeOut =
								dw_TimeOut + 1;
							mdelay(1000);

						}
					}	/*  for (;;) */

		       /*****************************/
					/* Test if stop signal occur */
		       /*****************************/

					if (*pb_ChronoStatus == 2) {
			  /**********************************/
						/* Read the measured timing value */
			  /**********************************/

						*pul_ChronoValue =
							inl(devpriv->
							s_BoardInfos.
							ui_Address + 4 +
							(64 * b_ModulNbr));

						if (*pul_ChronoValue != 0) {
							*pul_ChronoValue =
								*pul_ChronoValue
								- 1;
						}
					} else {
			  /*************************/
						/* Test if timeout occur */
			  /*************************/

						if ((*pb_ChronoStatus != 3)
							&& (dw_TimeOut ==
								ui_TimeOut)
							&& (ui_TimeOut != 0)) {
			     /*****************/
							/* Timeout occur */
			     /*****************/

							*pb_ChronoStatus = 4;
						}
					}

				} else {
		    /******************************/
					/* Timeout parameter is wrong */
		    /******************************/
					DPRINTK("Timeout parameter is wrong\n");
					i_ReturnValue = -5;
				}
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