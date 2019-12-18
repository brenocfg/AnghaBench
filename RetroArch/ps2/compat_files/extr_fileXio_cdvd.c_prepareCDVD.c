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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int SCECdNODISC ; 
 int SCECdPS2DVD ; 
 int SCECdPSCD ; 
 int SCECdUNKNOWN ; 
 scalar_t__ cd_Timer () ; 
 int /*<<< orphan*/  ps2_cdDiscValid () ; 
 int /*<<< orphan*/  ps2_cdStop () ; 
 int sceCdGetDiskType () ; 

__attribute__((used)) static int prepareCDVD(void)
{
   u64 wait_start;
   int cdmode = sceCdGetDiskType();

   if (sceCdGetDiskType() <= SCECdUNKNOWN) {
      wait_start = cd_Timer();
      while ((cd_Timer() < wait_start + 500) && !ps2_cdDiscValid()) {
         if (cdmode == SCECdNODISC)
            return 0;
      }
      if (cdmode == SCECdNODISC)
         return 0;
      if ((cdmode < SCECdPSCD) || (cdmode > SCECdPS2DVD)) {
         ps2_cdStop();
         return 0;
      }
   }

   return 1;
}