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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Devices_GetIOCB () ; 
 scalar_t__ Devices_ICAX3 ; 
 scalar_t__ Devices_ICAX4 ; 
 scalar_t__ Devices_ICAX5 ; 
 size_t Devices_IOCB0 ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  MEMORY_dPutByte (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ devbug ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** h_fp ; 
 size_t h_iocb ; 
 scalar_t__* h_lastbyte ; 
 char* h_lastop ; 

__attribute__((used)) static void Devices_H_Note(void)
{
	if (devbug)
		Log_print("NOTE Command");
	if (!Devices_GetIOCB())
		return;
	if (h_fp[h_iocb] != NULL) {
		long pos = ftell(h_fp[h_iocb]);
		if (pos >= 0) {
			int iocb = Devices_IOCB0 + h_iocb * 16;
			/* In Devices_H_Read one byte is read ahead. Take it into account. */
			if (h_lastop[h_iocb] == 'r' && h_lastbyte[h_iocb] != EOF)
				--pos;
			MEMORY_dPutByte(iocb + Devices_ICAX5, (UBYTE) pos);
			MEMORY_dPutByte(iocb + Devices_ICAX3, (UBYTE) (pos >> 8));
			MEMORY_dPutByte(iocb + Devices_ICAX4, (UBYTE) (pos >> 16));
			CPU_regY = 1;
			CPU_ClrN;
		}
		else {
			CPU_regY = 144; /* device done error */
			CPU_SetN;
		}
	}
	else {
		CPU_regY = 130; /* specified device does not exist; XXX: correct? */
		CPU_SetN;
	}
}