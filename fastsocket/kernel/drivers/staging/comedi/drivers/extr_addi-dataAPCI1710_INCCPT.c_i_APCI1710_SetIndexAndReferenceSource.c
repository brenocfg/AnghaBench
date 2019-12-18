#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_7__ {int* dw_MolduleConfiguration; } ;
struct TYPE_12__ {TYPE_5__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_8__ {int b_ModeRegister4; } ;
struct TYPE_9__ {TYPE_2__ s_ByteModeRegister; } ;
struct TYPE_10__ {TYPE_3__ s_ModeRegister; } ;
struct TYPE_11__ {TYPE_4__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 int APCI1710_DEFAULT_INDEX_RFERENCE ; 
 int APCI1710_INCREMENTAL_COUNTER ; 
 int APCI1710_INVERT_INDEX_RFERENCE ; 
 unsigned char APCI1710_SOURCE_0 ; 
 unsigned char APCI1710_SOURCE_1 ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_6__* devpriv ; 

int i_APCI1710_SetIndexAndReferenceSource(struct comedi_device *dev,
	unsigned char b_ModulNbr, unsigned char b_SourceSelection)
{
	int i_ReturnValue = 0;

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /*******************************/
		/* Test if incremental counter */
	   /*******************************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_INCREMENTAL_COUNTER) {
	      /******************************/
			/* Test if firmware >= Rev1.5 */
	      /******************************/

			if ((devpriv->s_BoardInfos.
					dw_MolduleConfiguration[b_ModulNbr] &
					0xFFFF) >= 0x3135) {
		 /*****************************/
				/* Test the source selection */
		 /*****************************/

				if (b_SourceSelection == APCI1710_SOURCE_0 ||
					b_SourceSelection == APCI1710_SOURCE_1)
				{
		    /******************************************/
					/* Test if invert the index and reference */
		    /******************************************/

					if (b_SourceSelection ==
						APCI1710_SOURCE_1) {
		       /********************************************/
						/* Invert index and reference source (DQ25) */
		       /********************************************/

						devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SiemensCounterInfo.
							s_ModeRegister.
							s_ByteModeRegister.
							b_ModeRegister4 =
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SiemensCounterInfo.
							s_ModeRegister.
							s_ByteModeRegister.
							b_ModeRegister4 |
							APCI1710_INVERT_INDEX_RFERENCE;
					} else {
		       /****************************************/
						/* Set the default configuration (DQ25) */
		       /****************************************/

						devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SiemensCounterInfo.
							s_ModeRegister.
							s_ByteModeRegister.
							b_ModeRegister4 =
							devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_SiemensCounterInfo.
							s_ModeRegister.
							s_ByteModeRegister.
							b_ModeRegister4 &
							APCI1710_DEFAULT_INDEX_RFERENCE;
					}
				}	/*  if (b_SourceSelection == APCI1710_SOURCE_0 ||b_SourceSelection == APCI1710_SOURCE_1) */
				else {
		    /*********************************/
					/* The source selection is wrong */
		    /*********************************/

					DPRINTK("The source selection is wrong\n");
					i_ReturnValue = -4;
				}	/*  if (b_SourceSelection == APCI1710_SOURCE_0 ||b_SourceSelection == APCI1710_SOURCE_1) */
			} else {
		 /**************************************/
				/* The module is not a counter module */
		 /**************************************/

				DPRINTK("The module is not a counter module\n");
				i_ReturnValue = -3;
			}
		} else {
	      /**************************************/
			/* The module is not a counter module */
	      /**************************************/

			DPRINTK("The module is not a counter module\n");
			i_ReturnValue = -3;
		}
	} else {
	   /***************************************/
		/* The selected module number is wrong */
	   /***************************************/

		DPRINTK("The selected module number is wrong\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}