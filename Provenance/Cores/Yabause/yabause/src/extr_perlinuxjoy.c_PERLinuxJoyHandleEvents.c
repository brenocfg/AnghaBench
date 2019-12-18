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
 int /*<<< orphan*/  LinuxJoyHandleEvents (scalar_t__) ; 
 scalar_t__ YabauseExec () ; 
 int joycount ; 
 scalar_t__ joysticks ; 

int PERLinuxJoyHandleEvents(void)
{
   int i;

   for(i = 0;i < joycount;i++)
      LinuxJoyHandleEvents(joysticks + i);

   // execute yabause
   if ( YabauseExec() != 0 )
   {
      return -1;
   }
   
   // return success
   return 0;
}