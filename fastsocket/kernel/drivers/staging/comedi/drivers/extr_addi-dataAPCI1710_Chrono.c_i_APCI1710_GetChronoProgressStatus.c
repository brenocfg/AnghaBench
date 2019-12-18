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
struct TYPE_5__ {int b_ChronoInit; } ;
struct TYPE_6__ {TYPE_1__ s_ChronoModuleInfo; } ;

/* Variables and functions */
 int APCI1710_CHRONOMETER ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI1710_GetChronoProgressStatus(struct comedi_device *dev,
	unsigned char b_ModulNbr, unsigned char *pb_ChronoStatus)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;

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

				dw_Status = inl(devpriv->s_BoardInfos.
					ui_Address + 8 + (64 * b_ModulNbr));

		 /********************/
				/* Test if overflow */
		 /********************/

				if ((dw_Status & 8) == 8) {
		    /******************/
					/* Overflow occur */
		    /******************/

					*pb_ChronoStatus = 3;
				}	/*  if ((dw_Status & 8) == 8) */
				else {
		    /*******************************/
					/* Test if measurement stopped */
		    /*******************************/

					if ((dw_Status & 2) == 2) {
		       /***********************/
						/* A stop signal occur */
		       /***********************/

						*pb_ChronoStatus = 2;
					}	/*  if ((dw_Status & 2) == 2) */
					else {
		       /*******************************/
						/* Test if measurement started */
		       /*******************************/

						if ((dw_Status & 1) == 1) {
			  /************************/
							/* A start signal occur */
			  /************************/

							*pb_ChronoStatus = 1;
						}	/*  if ((dw_Status & 1) == 1) */
						else {
			  /***************************/
							/* Measurement not started */
			  /***************************/

							*pb_ChronoStatus = 0;
						}	/*  if ((dw_Status & 1) == 1) */
					}	/*  if ((dw_Status & 2) == 2) */
				}	/*  if ((dw_Status & 8) == 8) */
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