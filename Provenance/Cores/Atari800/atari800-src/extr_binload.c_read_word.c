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
 int /*<<< orphan*/ * BINLOAD_bin_file ; 
 scalar_t__ BINLOAD_start_binloading ; 
 int /*<<< orphan*/  CPU_regPC ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  MEMORY_dGetWordAligned (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_word(void)
{
	UBYTE buf[2];
	if (fread(buf, 1, 2, BINLOAD_bin_file) != 2) {
		fclose(BINLOAD_bin_file);
		BINLOAD_bin_file = NULL;
		if (BINLOAD_start_binloading) {
			BINLOAD_start_binloading = FALSE;
			Log_print("binload: not valid BIN file");
			return -1;
		}
		CPU_regPC = MEMORY_dGetWordAligned(0x2e0);
		return -1;
	}
	return buf[0] + (buf[1] << 8);
}