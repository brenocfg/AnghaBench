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
 int /*<<< orphan*/ * BINLOAD_bin_file ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  CPU_rts_handler ; 
 int /*<<< orphan*/  Devices_CloseBasicFile ; 
 int /*<<< orphan*/  Devices_ReadBasicFile ; 
 int /*<<< orphan*/  Devices_RestoreEHOPEN ; 
 int /*<<< orphan*/  ESC_AddEscRts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESC_EHCLOS ; 
 int /*<<< orphan*/  ESC_EHREAD ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  ehclos_addr ; 
 int /*<<< orphan*/  ehread_addr ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Devices_OpenBasicFile(void)
{
	if (BINLOAD_bin_file != NULL) {
		fseek(BINLOAD_bin_file, 0, SEEK_SET);
		ESC_AddEscRts(ehclos_addr, ESC_EHCLOS, Devices_CloseBasicFile);
		ESC_AddEscRts(ehread_addr, ESC_EHREAD, Devices_ReadBasicFile);
		CPU_regY = 1;
		CPU_ClrN;
	}
	CPU_rts_handler = Devices_RestoreEHOPEN;
}