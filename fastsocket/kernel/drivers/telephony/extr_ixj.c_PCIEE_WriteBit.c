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
typedef  int /*<<< orphan*/  WORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PCIEE_WriteBit(WORD wEEPROMAddress, BYTE lastLCC, BYTE byData)
{
	lastLCC = lastLCC & 0xfb;
	lastLCC = lastLCC | (byData ? 4 : 0);
	outb(lastLCC, wEEPROMAddress);	/*set data out bit as appropriate */

	mdelay(1);
	lastLCC = lastLCC | 0x01;
	outb(lastLCC, wEEPROMAddress);	/*SK rising edge */

	byData = byData << 1;
	lastLCC = lastLCC & 0xfe;
	mdelay(1);
	outb(lastLCC, wEEPROMAddress);	/*after delay, SK falling edge */

}