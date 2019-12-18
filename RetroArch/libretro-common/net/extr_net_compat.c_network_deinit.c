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
 int /*<<< orphan*/  CELL_SYSMODULE_NET ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/ * _net_compat_net_memory ; 
 int /*<<< orphan*/  cellNetCtlTerm () ; 
 int /*<<< orphan*/  cellSysmoduleUnloadModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_deinit () ; 
 int /*<<< orphan*/  sceNetCtlTerm () ; 
 int /*<<< orphan*/  sceNetTerm () ; 
 int /*<<< orphan*/  socExit () ; 
 int /*<<< orphan*/  sys_net_finalize_network () ; 

void network_deinit(void)
{
#if defined(_WIN32)
   WSACleanup();
#elif defined(__CELLOS_LV2__) && !defined(__PSL1GHT__)
   cellNetCtlTerm();
   sys_net_finalize_network();
   cellSysmoduleUnloadModule(CELL_SYSMODULE_NET);
#elif defined(VITA)
   sceNetCtlTerm();
   sceNetTerm();

   if (_net_compat_net_memory)
   {
      free(_net_compat_net_memory);
      _net_compat_net_memory = NULL;
   }
#elif defined(GEKKO) && !defined(HW_DOL)
   net_deinit();
#elif defined(_3DS)
   socExit();

   if(_net_compat_net_memory)
   {
	  free(_net_compat_net_memory);
	  _net_compat_net_memory = NULL;
   }
#endif
}