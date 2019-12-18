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
struct TYPE_11__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_12__ {TYPE_5__ s_BoardInfos; TYPE_4__* s_ModuleInfo; } ;
struct TYPE_7__ {int b_ModeRegister4; int b_ModeRegister3; } ;
struct TYPE_8__ {int /*<<< orphan*/  dw_ModeRegister1_2_3_4; TYPE_1__ s_ByteModeRegister; } ;
struct TYPE_9__ {TYPE_2__ s_ModeRegister; } ;
struct TYPE_10__ {TYPE_3__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 unsigned char APCI1710_30MHZ ; 
 unsigned char APCI1710_33MHZ ; 
 unsigned char APCI1710_40MHZ ; 
 int APCI1710_DISABLE_40MHZ_FILTER ; 
 int APCI1710_ENABLE_40MHZ_FILTER ; 
 int APCI1710_INCREMENTAL_COUNTER ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_6__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

int i_APCI1710_SetInputFilter(struct comedi_device *dev,
	unsigned char b_ModulNbr, unsigned char b_PCIInputClock, unsigned char b_Filter)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status = 0;

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
		 /**************************/
				/* Test the PCI bus clock */
		 /**************************/

				if ((b_PCIInputClock == APCI1710_30MHZ) ||
					(b_PCIInputClock == APCI1710_33MHZ) ||
					(b_PCIInputClock == APCI1710_40MHZ)) {
		    /*************************/
					/* Test the filter value */
		    /*************************/

					if (b_Filter < 16) {
		       /**********************/
						/* Test if 40MHz used */
		       /**********************/

						if (b_PCIInputClock ==
							APCI1710_40MHZ) {
			  /*********************************/
							/* Test if 40MHz quartz on board */
			  /*********************************/

							dw_Status =
								inl(devpriv->
								s_BoardInfos.
								ui_Address +
								36 +
								(64 * b_ModulNbr));

			  /******************************/
							/* Test the quartz flag (DQ0) */
			  /******************************/

							if ((dw_Status & 1) !=
								1) {
			     /*****************************/
								/* 40MHz quartz not on board */
			     /*****************************/

								DPRINTK("40MHz quartz not on board\n");
								i_ReturnValue =
									-6;
							}
						}	/*  if (b_PCIInputClock == APCI1710_40MHZ) */

		       /***************************/
						/* Test if error not occur */
		       /***************************/

						if (i_ReturnValue == 0) {
			  /**********************/
							/* Test if 40MHz used */
			  /**********************/

							if (b_PCIInputClock ==
								APCI1710_40MHZ)
							{
			     /*********************************/
								/* Enable the 40MHz quarz (DQ31) */
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
									APCI1710_ENABLE_40MHZ_FILTER;

							}	/*  if (b_PCIInputClock == APCI1710_40MHZ) */
							else {
			     /**********************************/
								/* Disable the 40MHz quarz (DQ31) */
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
									APCI1710_DISABLE_40MHZ_FILTER;

							}	/*  if (b_PCIInputClock == APCI1710_40MHZ) */

			  /************************/
							/* Set the filter value */
			  /************************/

							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_SiemensCounterInfo.
								s_ModeRegister.
								s_ByteModeRegister.
								b_ModeRegister3
								=
								(devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_SiemensCounterInfo.
								s_ModeRegister.
								s_ByteModeRegister.
								b_ModeRegister3
								& 0x1F) |
								((b_Filter &
									0x7) <<
								5);

							devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_SiemensCounterInfo.
								s_ModeRegister.
								s_ByteModeRegister.
								b_ModeRegister4
								=
								(devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_SiemensCounterInfo.
								s_ModeRegister.
								s_ByteModeRegister.
								b_ModeRegister4
								& 0xFE) |
								((b_Filter &
									0x8) >>
								3);

			  /***************************/
							/* Write the configuration */
			  /***************************/

							outl(devpriv->
								s_ModuleInfo
								[b_ModulNbr].
								s_SiemensCounterInfo.
								s_ModeRegister.
								dw_ModeRegister1_2_3_4,
								devpriv->
								s_BoardInfos.
								ui_Address +
								20 +
								(64 * b_ModulNbr));
						}	/*  if (i_ReturnValue == 0) */
					}	/*  if (b_Filter < 16) */
					else {
		       /**************************************/
						/* The selected filter value is wrong */
		       /**************************************/

						DPRINTK("The selected filter value is wrong\n");
						i_ReturnValue = -5;
					}	/*  if (b_Filter < 16) */
				}	/*  if ((b_PCIInputClock == APCI1710_30MHZ) || (b_PCIInputClock == APCI1710_33MHZ) || (b_PCIInputClock == APCI1710_40MHZ)) */
				else {
		    /*****************************************/
					/* The selected PCI input clock is wrong */
		    /*****************************************/

					DPRINTK("The selected PCI input clock is wrong\n");
					i_ReturnValue = 4;
				}	/*  if ((b_PCIInputClock == APCI1710_30MHZ) || (b_PCIInputClock == APCI1710_33MHZ) || (b_PCIInputClock == APCI1710_40MHZ)) */
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
	   /*************************************************/
		/* The selected module number parameter is wrong */
	   /*************************************************/

		DPRINTK("The selected module number parameter is wrong\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}