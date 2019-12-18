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
struct TYPE_5__ {int* dw_MolduleConfiguration; } ;
struct TYPE_8__ {TYPE_3__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_6__ {int b_ChronoInit; int b_TimingUnit; scalar_t__ d_TimingInterval; } ;
struct TYPE_7__ {TYPE_2__ s_ChronoModuleInfo; } ;

/* Variables and functions */
 int APCI1710_CHRONOMETER ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 int /*<<< orphan*/  fpu_begin () ; 
 int /*<<< orphan*/  fpu_end () ; 

int i_APCI1710_ConvertChronoValue(struct comedi_device *dev,
	unsigned char b_ModulNbr,
	unsigned int ul_ChronoValue,
	unsigned int *pul_Hour,
	unsigned char *pb_Minute,
	unsigned char *pb_Second,
	unsigned int *pui_MilliSecond, unsigned int *pui_MicroSecond, unsigned int *pui_NanoSecond)
{
	int i_ReturnValue = 0;
	double d_Hour;
	double d_Minute;
	double d_Second;
	double d_MilliSecond;
	double d_MicroSecond;
	double d_NanoSecond;

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
				fpu_begin();

				d_Hour = (double)ul_ChronoValue *(double)
					devpriv->s_ModuleInfo[b_ModulNbr].
					s_ChronoModuleInfo.d_TimingInterval;

				switch (devpriv->
					s_ModuleInfo[b_ModulNbr].
					s_ChronoModuleInfo.b_TimingUnit) {
				case 0:
					d_Hour = d_Hour / (double)1000.0;

				case 1:
					d_Hour = d_Hour / (double)1000.0;

				case 2:
					d_Hour = d_Hour / (double)1000.0;

				case 3:
					d_Hour = d_Hour / (double)60.0;

				case 4:
			    /**********************/
					/* Calculate the hour */
			    /**********************/

					d_Hour = d_Hour / (double)60.0;
					*pul_Hour = (unsigned int) d_Hour;

			    /************************/
					/* Calculate the minute */
			    /************************/

					d_Minute = d_Hour - *pul_Hour;
					d_Minute = d_Minute * 60;
					*pb_Minute = (unsigned char) d_Minute;

			    /************************/
					/* Calculate the second */
			    /************************/

					d_Second = d_Minute - *pb_Minute;
					d_Second = d_Second * 60;
					*pb_Second = (unsigned char) d_Second;

			    /*****************************/
					/* Calculate the mini second */
			    /*****************************/

					d_MilliSecond = d_Second - *pb_Second;
					d_MilliSecond = d_MilliSecond * 1000;
					*pui_MilliSecond = (unsigned int) d_MilliSecond;

			    /******************************/
					/* Calculate the micro second */
			    /******************************/

					d_MicroSecond =
						d_MilliSecond -
						*pui_MilliSecond;
					d_MicroSecond = d_MicroSecond * 1000;
					*pui_MicroSecond = (unsigned int) d_MicroSecond;

			    /******************************/
					/* Calculate the micro second */
			    /******************************/

					d_NanoSecond =
						d_MicroSecond -
						*pui_MicroSecond;
					d_NanoSecond = d_NanoSecond * 1000;
					*pui_NanoSecond = (unsigned int) d_NanoSecond;
					break;
				}

				fpu_end();
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