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
 scalar_t__ BINLOAD_LOADING_BASIC_LISTED ; 
 scalar_t__ BINLOAD_LOADING_BASIC_SAVED ; 
 scalar_t__ BINLOAD_loading_basic ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  CPU_rts_handler ; 
 int /*<<< orphan*/  Devices_E_Read ; 
 int /*<<< orphan*/  Devices_OpenBasicFile ; 
 int /*<<< orphan*/  Devices_RestoreEHREAD ; 
 int /*<<< orphan*/  ESC_AddEscRts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESC_EHOPEN ; 
 int /*<<< orphan*/  ESC_EHREAD ; 
 char* basic_command_ptr ; 
 int /*<<< orphan*/  ehopen_addr ; 
 int /*<<< orphan*/  ehread_addr ; 

__attribute__((used)) static void Devices_GetBasicCommand(void)
{
	if (basic_command_ptr != NULL) {
		CPU_regA = *basic_command_ptr++;
		CPU_regY = 1;
		CPU_ClrN;
		if (*basic_command_ptr != '\0')
			return;
		if (BINLOAD_loading_basic == BINLOAD_LOADING_BASIC_SAVED || BINLOAD_loading_basic == BINLOAD_LOADING_BASIC_LISTED)
			ESC_AddEscRts(ehopen_addr, ESC_EHOPEN, Devices_OpenBasicFile);
		basic_command_ptr = NULL;
	}
#ifdef BASIC
	ESC_AddEscRts(ehread_addr, ESC_EHREAD, Devices_E_Read);
#else
	CPU_rts_handler = Devices_RestoreEHREAD;
#endif
}