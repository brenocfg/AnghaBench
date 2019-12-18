#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ClkrstSession ;

/* Variables and functions */
 int /*<<< orphan*/  PcvModuleId_CpuBus ; 
 int /*<<< orphan*/  PcvModule_CpuBus ; 
 int /*<<< orphan*/  appletUnlockExit () ; 
 int /*<<< orphan*/  clkrstCloseSession (TYPE_1__*) ; 
 int /*<<< orphan*/  clkrstExit () ; 
 int /*<<< orphan*/  clkrstOpenSession (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clkrstSetClockRate (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ hosversionBefore (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nifmExit () ; 
 int /*<<< orphan*/  pcvExit () ; 
 int /*<<< orphan*/  pcvSetClockRate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psmExit () ; 
 scalar_t__ psmInitialized ; 
 int /*<<< orphan*/  socketExit () ; 
 int /*<<< orphan*/ * splashData ; 

__attribute__((used)) static void frontend_switch_deinit(void *data)
{
   (void)data;

#ifdef HAVE_LIBNX
   nifmExit();

   if(hosversionBefore(8, 0, 0)) {
      pcvSetClockRate(PcvModule_CpuBus, 1020000000);
      pcvExit();
   } else {
      ClkrstSession session = {0};
      clkrstOpenSession(&session, PcvModuleId_CpuBus, 3);
      clkrstSetClockRate(&session, 1020000000);
      clkrstCloseSession(&session);
      clkrstExit();
   }

#if defined(SWITCH) && defined(NXLINK)
   socketExit();
#endif

   /* Splash */
   if (splashData)
   {
      free(splashData);
      splashData = NULL;
   }

   if (psmInitialized)
       psmExit();

   appletUnlockExit();
#endif
}