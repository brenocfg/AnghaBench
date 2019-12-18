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
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ UnregisterClassA (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void winraw_destroy_window(HWND wnd)
{
   BOOL r;

   if (!wnd)
      return;

   r = DestroyWindow(wnd);

   if (!r)
   {
      RARCH_WARN("[WINRAW]: DestroyWindow failed with error %lu.\n", GetLastError());
   }

   r = UnregisterClassA("winraw-input", NULL);

   if (!r)
   {
      RARCH_WARN("[WINRAW]: UnregisterClassA failed with error %lu.\n", GetLastError());
   }
}