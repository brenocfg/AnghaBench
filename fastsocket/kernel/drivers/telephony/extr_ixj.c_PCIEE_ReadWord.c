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
typedef  int WORD ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int PCIEE_ReadBit (int,int) ; 
 int /*<<< orphan*/  PCIEE_WriteBit (int,int,int) ; 
 int inb (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static bool PCIEE_ReadWord(WORD wAddress, WORD wLoc, WORD * pwResult)
{
	BYTE lastLCC;
	WORD wEEPROMAddress = wAddress + 3;
	DWORD i;
	BYTE byResult;
	*pwResult = 0;
	lastLCC = inb(wEEPROMAddress);
	lastLCC = lastLCC | 0x02;
	lastLCC = lastLCC & 0xfe;
	outb(lastLCC, wEEPROMAddress);	/* CS hi, SK lo */

	mdelay(1);		/* delay */

	PCIEE_WriteBit(wEEPROMAddress, lastLCC, 1);
	PCIEE_WriteBit(wEEPROMAddress, lastLCC, 1);
	PCIEE_WriteBit(wEEPROMAddress, lastLCC, 0);
	for (i = 0; i < 8; i++) {
		PCIEE_WriteBit(wEEPROMAddress, lastLCC, wLoc & 0x80 ? 1 : 0);
		wLoc <<= 1;
	}

	for (i = 0; i < 16; i++) {
		byResult = PCIEE_ReadBit(wEEPROMAddress, lastLCC);
		*pwResult = (*pwResult << 1) | byResult;
	}

	mdelay(1);		/* another delay */

	lastLCC = lastLCC & 0xfd;
	outb(lastLCC, wEEPROMAddress);	/* negate CS */

	return 0;
}