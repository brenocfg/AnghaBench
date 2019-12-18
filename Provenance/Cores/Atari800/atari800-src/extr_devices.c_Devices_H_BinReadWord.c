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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ BINLOAD_start_binloading ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 int /*<<< orphan*/  CPU_regPC ; 
 int CPU_regY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  MEMORY_dGetWordAligned (int) ; 
 int /*<<< orphan*/ * binf ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ runBinFile ; 

__attribute__((used)) static int Devices_H_BinReadWord(void)
{
	UBYTE buf[2];
	if (fread(buf, 1, 2, binf) != 2) {
		fclose(binf);
		binf = NULL;
		if (BINLOAD_start_binloading) {
			BINLOAD_start_binloading = FALSE;
			Log_print("binload: not valid BIN file");
			CPU_regY = 180; /* MyDOS: not a binary file */
			CPU_SetN;
			return -1;
		}
		if (runBinFile)
			CPU_regPC = MEMORY_dGetWordAligned(0x2e0);
		CPU_regY = 1;
		CPU_ClrN;
		return -1;
	}
	return buf[0] + (buf[1] << 8);
}