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
typedef  int /*<<< orphan*/  cmd ;
typedef  scalar_t__ Window ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int system (char*) ; 
 int xdg_screensaver_available ; 

__attribute__((used)) static void xdg_screensaver_inhibit(Window wnd)
{
   int  ret;
   char cmd[64];

   cmd[0] = '\0';

   RARCH_LOG("[X11]: Suspending screensaver (X11, xdg-screensaver).\n");

   snprintf(cmd, sizeof(cmd), "xdg-screensaver suspend 0x%x", (int)wnd);

   ret = system(cmd);
   if (ret == -1)
   {
      xdg_screensaver_available = false;
      RARCH_WARN("Failed to launch xdg-screensaver.\n");
   }
   else if (WEXITSTATUS(ret))
   {
      xdg_screensaver_available = false;
      RARCH_WARN("Could not suspend screen saver.\n");
   }
}