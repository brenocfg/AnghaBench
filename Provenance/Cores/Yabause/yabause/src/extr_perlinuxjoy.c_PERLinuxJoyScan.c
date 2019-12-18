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
typedef  int u32 ;

/* Variables and functions */
 int LinuxJoyScan (scalar_t__) ; 
 int joycount ; 
 scalar_t__ joysticks ; 

u32 PERLinuxJoyScan(u32 flags) {
   int i;

   for(i = 0;i < joycount;i++)
   {
      int ret = LinuxJoyScan(joysticks + i);
      if (ret != 0) return ret;
   }

   return 0;
}