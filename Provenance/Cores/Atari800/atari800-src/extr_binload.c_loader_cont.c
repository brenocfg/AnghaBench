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
 int /*<<< orphan*/ * BINLOAD_bin_file ; 
 scalar_t__ BINLOAD_start_binloading ; 
 int /*<<< orphan*/  CPU_SetC ; 
 int CPU_regPC ; 
 int CPU_regS ; 
 int EOF ; 
 int /*<<< orphan*/  ESC_Add (scalar_t__,int /*<<< orphan*/ ,void (*) ()) ; 
 int /*<<< orphan*/  ESC_BINLOADER_CONT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MEMORY_PutByte (scalar_t__,int /*<<< orphan*/ ) ; 
 int MEMORY_dGetByte (int) ; 
 int MEMORY_dGetWordAligned (int) ; 
 int /*<<< orphan*/  MEMORY_dPutByte (int,int) ; 
 int /*<<< orphan*/  MEMORY_dPutWordAligned (int,scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int read_word () ; 

__attribute__((used)) static void loader_cont(void)
{
	if (BINLOAD_bin_file == NULL)
		return;
	if (BINLOAD_start_binloading) {
		MEMORY_dPutByte(0x244, 0);
		MEMORY_dPutByte(0x09, 1);
	}
	else
		CPU_regS += 2;	/* pop ESC code */

	MEMORY_dPutByte(0x2e3, 0xd7);
	do {
		int temp;
		UWORD from;
		UWORD to;
		do
			temp = read_word();
		while (temp == 0xffff);
		if (temp < 0)
			return;
		from = (UWORD) temp;

		temp = read_word();
		if (temp < 0)
			return;
		to = (UWORD) temp;

		if (BINLOAD_start_binloading) {
			MEMORY_dPutWordAligned(0x2e0, from);
			BINLOAD_start_binloading = FALSE;
		}

		to++;
		do {
			int byte = fgetc(BINLOAD_bin_file);
			if (byte == EOF) {
				fclose(BINLOAD_bin_file);
				BINLOAD_bin_file = NULL;
				CPU_regPC = MEMORY_dGetWordAligned(0x2e0);
				if (MEMORY_dGetByte(0x2e3) != 0xd7) {
					/* run INIT routine which RTSes directly to RUN routine */
					CPU_regPC--;
					MEMORY_dPutByte(0x0100 + CPU_regS--, CPU_regPC >> 8);		/* high */
					MEMORY_dPutByte(0x0100 + CPU_regS--, CPU_regPC & 0xff);	/* low */
					CPU_regPC = MEMORY_dGetWordAligned(0x2e2);
				}
				return;
			}
			MEMORY_PutByte(from, (UBYTE) byte);
			from++;
		} while (from != to);
	} while (MEMORY_dGetByte(0x2e3) == 0xd7);

	CPU_regS--;
	ESC_Add((UWORD) (0x100 + CPU_regS), ESC_BINLOADER_CONT, loader_cont);
	CPU_regS--;
	MEMORY_dPutByte(0x0100 + CPU_regS--, 0x01);	/* high */
	MEMORY_dPutByte(0x0100 + CPU_regS, CPU_regS + 1);	/* low */
	CPU_regS--;
	CPU_regPC = MEMORY_dGetWordAligned(0x2e2);
	CPU_SetC;

	MEMORY_dPutByte(0x0300, 0x31);	/* for "Studio Dream" */
}