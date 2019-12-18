#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  EE76_CMD_LEN ; 
 int EE_READ ; 
 unsigned int inl (unsigned int) ; 
 int /*<<< orphan*/  outl (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  v_EepromClock76 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  v_EepromSendCommand76 (unsigned int,int,int /*<<< orphan*/ ) ; 

void v_EepromCs76Read(unsigned int dw_Address, unsigned short w_offset, unsigned short *pw_Value)
{

        char c_BitPos = 0;

	unsigned int dw_RegisterValue = 0;

	unsigned int dw_RegisterValueRead = 0;

   /*************************************************/

	/* Send EEPROM read command and offset to EEPROM */

   /*************************************************/

	v_EepromSendCommand76(dw_Address, (EE_READ << 4) | (w_offset / 2),
		EE76_CMD_LEN);

   /*******************************/

	/* Get the last register value */

   /*******************************/

	dw_RegisterValue = (((w_offset / 2) & 0x1) << 2) | 0x2;

   /*****************************/

	/* Set the 16-bit value of 0 */

   /*****************************/

	*pw_Value = 0;

   /************************/

	/* Get the 16-bit value */

   /************************/

	for (c_BitPos = 0; c_BitPos < 16; c_BitPos++)
	{

      /****************************/

		/* Trigger the EEPROM clock */

      /****************************/

		v_EepromClock76(dw_Address, dw_RegisterValue);

      /**********************/

		/* Get the result bit */

      /**********************/

		dw_RegisterValueRead = inl(dw_Address);

      /***************/

		/* Wait 0.1 ms */

      /***************/

		udelay(100);

      /***************************************/

		/* Get bit value and shift into result */

      /***************************************/

		if (dw_RegisterValueRead & 0x8)
		{

	 /**********/

			/* Read 1 */

	 /**********/

			*pw_Value = (*pw_Value << 1) | 0x1;

		}

		else
		{

	 /**********/

			/* Read 0 */

	 /**********/

			*pw_Value = (*pw_Value << 1);

		}

	}

   /*************************/

	/* Clear all EEPROM bits */

   /*************************/

	dw_RegisterValue = 0x0;

   /********************************************************************/

	/* Toggle EEPROM's Chip select to get it out of Shift Register Mode */

   /********************************************************************/

	outl(dw_RegisterValue, dw_Address);

   /***************/

	/* Wait 0.1 ms */

   /***************/

	udelay(100);

}