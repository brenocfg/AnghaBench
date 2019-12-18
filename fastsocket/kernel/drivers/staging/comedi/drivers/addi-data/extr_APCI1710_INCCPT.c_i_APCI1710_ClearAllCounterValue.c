#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_3__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_4__ {TYPE_1__ s_BoardInfos; } ;

/* Variables and functions */
 int APCI1710_INCREMENTAL_COUNTER ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

int i_APCI1710_ClearAllCounterValue(struct comedi_device *dev)
{
	unsigned char b_ModulCpt = 0;
	int i_ReturnValue = 0;

	/********************************/
	/* Test if counter module found */
	/********************************/

	if ((devpriv->s_BoardInfos.
			dw_MolduleConfiguration[0] & 0xFFFF0000UL) ==
		APCI1710_INCREMENTAL_COUNTER
		|| (devpriv->s_BoardInfos.
			dw_MolduleConfiguration[1] & 0xFFFF0000UL) ==
		APCI1710_INCREMENTAL_COUNTER
		|| (devpriv->s_BoardInfos.
			dw_MolduleConfiguration[2] & 0xFFFF0000UL) ==
		APCI1710_INCREMENTAL_COUNTER
		|| (devpriv->s_BoardInfos.
			dw_MolduleConfiguration[3] & 0xFFFF0000UL) ==
		APCI1710_INCREMENTAL_COUNTER) {
		for (b_ModulCpt = 0; b_ModulCpt < 4; b_ModulCpt++) {
	      /*******************************/
			/* Test if incremental counter */
	      /*******************************/

			if ((devpriv->s_BoardInfos.
					dw_MolduleConfiguration[b_ModulCpt] &
					0xFFFF0000UL) ==
				APCI1710_INCREMENTAL_COUNTER) {
		 /*********************/
				/* Clear the counter */
		 /*********************/

				outl(1, devpriv->s_BoardInfos.
					ui_Address + 16 + (64 * b_ModulCpt));
			}
		}
	} else {
	   /***************************/
		/* No counter module found */
	   /***************************/

		DPRINTK("No counter module found\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}