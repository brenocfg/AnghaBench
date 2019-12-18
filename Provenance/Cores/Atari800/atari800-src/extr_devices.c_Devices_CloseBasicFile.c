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
 scalar_t__ BINLOAD_LOADING_BASIC_RUN ; 
 scalar_t__ BINLOAD_LOADING_BASIC_SAVED ; 
 int /*<<< orphan*/ * BINLOAD_bin_file ; 
 scalar_t__ BINLOAD_loading_basic ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  CPU_rts_handler ; 
 int /*<<< orphan*/  Devices_E_Read ; 
 int /*<<< orphan*/  Devices_IgnoreReady ; 
 int /*<<< orphan*/  Devices_RestoreEHCLOS ; 
 int /*<<< orphan*/  Devices_RestoreEHREAD () ; 
 int /*<<< orphan*/  ESC_AddEscRts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESC_EHREAD ; 
 int /*<<< orphan*/  ESC_EHWRIT ; 
 int /*<<< orphan*/  ehread_addr ; 
 int /*<<< orphan*/  ehwrit_addr ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ready_prompt ; 
 int /*<<< orphan*/  ready_ptr ; 

__attribute__((used)) static void Devices_CloseBasicFile(void)
{
	if (BINLOAD_bin_file != NULL) {
		fclose(BINLOAD_bin_file);
		BINLOAD_bin_file = NULL;
		/* "RUN" ENTERed program */
		if (BINLOAD_loading_basic != 0 && BINLOAD_loading_basic != BINLOAD_LOADING_BASIC_SAVED) {
			ready_ptr = ready_prompt;
			ESC_AddEscRts(ehwrit_addr, ESC_EHWRIT, Devices_IgnoreReady);
			BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_RUN;
		}
		else
			BINLOAD_loading_basic = 0;
	}
#ifdef BASIC
	ESC_AddEscRts(ehread_addr, ESC_EHREAD, Devices_E_Read);
#else
	Devices_RestoreEHREAD();
#endif
	CPU_rts_handler = Devices_RestoreEHCLOS;
	CPU_regY = 1;
	CPU_ClrN;
}