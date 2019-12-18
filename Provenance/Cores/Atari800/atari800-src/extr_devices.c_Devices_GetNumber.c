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
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Devices_GetIOCB () ; 
 int /*<<< orphan*/  Devices_ICDNOZ ; 
 int /*<<< orphan*/  FALSE ; 
 int MEMORY_dGetByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t h_iocb ; 
 int /*<<< orphan*/ * h_textmode ; 

__attribute__((used)) static int Devices_GetNumber(int set_textmode)
{
	int devnum;
	if (!Devices_GetIOCB())
		return -1;
	devnum = MEMORY_dGetByte(Devices_ICDNOZ);
	if (devnum > 9 || devnum == 0 || devnum == 5) {
		CPU_regY = 160; /* invalid unit/drive number */
		CPU_SetN;
		return -1;
	}
	if (devnum < 5) {
		if (set_textmode)
			h_textmode[h_iocb] = FALSE;
		return devnum - 1;
	}
	if (set_textmode)
		h_textmode[h_iocb] = TRUE;
	return devnum - 6;
}