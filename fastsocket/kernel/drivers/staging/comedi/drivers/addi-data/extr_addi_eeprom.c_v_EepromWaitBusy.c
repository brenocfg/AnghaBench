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
 unsigned char inb (unsigned short) ; 

void v_EepromWaitBusy(unsigned short w_PCIBoardEepromAddress)
{

	unsigned char b_EepromBusy = 0;

	do
	{

	   /*************/

		/* IMPORTANT */

	   /*************/

	   /************************************************************************/

		/* An error has been written in the AMCC 5933 book at the page B-13 */

		/* Ex: if you read a byte and look for the busy statusEEPROM=0x80 and   */

		/*      the operator register is AMCC_OP_REG_MCSR+3 */

		/*      unsigned short read  EEPROM=0x8000 andAMCC_OP_REG_MCSR+2                  */

		/*      unsigned int read  EEPROM=0x80000000 and AMCC_OP_REG_MCSR */

	   /************************************************************************/

		b_EepromBusy = inb(w_PCIBoardEepromAddress + 0x3F);
		b_EepromBusy = b_EepromBusy & 0x80;

	} while (b_EepromBusy == 0x80);

}