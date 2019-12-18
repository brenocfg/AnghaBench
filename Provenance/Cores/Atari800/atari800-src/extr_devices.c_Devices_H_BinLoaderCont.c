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
typedef  scalar_t__ UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 scalar_t__ BINLOAD_start_binloading ; 
 int /*<<< orphan*/  CPU_SetC ; 
 int CPU_regPC ; 
 int CPU_regS ; 
 int Devices_H_BinReadWord () ; 
 int EOF ; 
 int /*<<< orphan*/  ESC_Add (scalar_t__,int /*<<< orphan*/ ,void (*) ()) ; 
 int /*<<< orphan*/  ESC_BINLOADER_CONT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Log_print (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MEMORY_PutByte (scalar_t__,int /*<<< orphan*/ ) ; 
 int MEMORY_dGetByte (int) ; 
 int MEMORY_dGetWordAligned (int) ; 
 int /*<<< orphan*/  MEMORY_dPutByte (int,int) ; 
 int /*<<< orphan*/  MEMORY_dPutWordAligned (int,scalar_t__) ; 
 int /*<<< orphan*/ * binf ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 scalar_t__ initBinFile ; 
 scalar_t__ runBinFile ; 

__attribute__((used)) static void Devices_H_BinLoaderCont(void)
{
	if (binf == NULL)
		return;
	if (BINLOAD_start_binloading) {
		MEMORY_dPutByte(0x244, 0);
		MEMORY_dPutByte(0x09, 1);
	}
	else
		CPU_regS += 2;				/* pop ESC code */

	MEMORY_dPutByte(0x2e3, 0xd7);
	do {
		int temp;
		UWORD from;
		UWORD to;
		do
			temp = Devices_H_BinReadWord();
		while (temp == 0xffff);
		if (temp < 0)
			return;
		from = (UWORD) temp;

		temp = Devices_H_BinReadWord();
		if (temp < 0)
			return;
		to = (UWORD) temp;

		if (devbug)
			Log_print("H: Load: From %04X to %04X", from, to);

		if (BINLOAD_start_binloading) {
			if (runBinFile)
				MEMORY_dPutWordAligned(0x2e0, from);
			BINLOAD_start_binloading = FALSE;
		}

		to++;
		do {
			int byte = fgetc(binf);
			if (byte == EOF) {
				fclose(binf);
				binf = NULL;
				if (runBinFile)
					CPU_regPC = MEMORY_dGetWordAligned(0x2e0);
				if (initBinFile && (MEMORY_dGetByte(0x2e3) != 0xd7)) {
					/* run INIT routine which RTSes directly to RUN routine */
					CPU_regPC--;
					MEMORY_dPutByte(0x0100 + CPU_regS--, CPU_regPC >> 8);	/* high */
					MEMORY_dPutByte(0x0100 + CPU_regS--, CPU_regPC & 0xff);	/* low */
					CPU_regPC = MEMORY_dGetWordAligned(0x2e2);
				}
				return;
			}
			MEMORY_PutByte(from, (UBYTE) byte);
			from++;
		} while (from != to);
	} while (!initBinFile || MEMORY_dGetByte(0x2e3) == 0xd7);

	CPU_regS--;
	ESC_Add((UWORD) (0x100 + CPU_regS), ESC_BINLOADER_CONT, Devices_H_BinLoaderCont);
	CPU_regS--;
	MEMORY_dPutByte(0x0100 + CPU_regS--, 0x01);	/* high */
	MEMORY_dPutByte(0x0100 + CPU_regS, CPU_regS + 1);	/* low */
	CPU_regS--;
	CPU_regPC = MEMORY_dGetWordAligned(0x2e2);
	CPU_SetC;

	MEMORY_dPutByte(0x0300, 0x31);		/* for "Studio Dream" */
}