#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int opacity; } ;
typedef  TYPE_1__ dispserv_win32_t ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWA_ALPHA ; 
 int SetLayeredWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int WS_EX_LAYERED ; 
 int /*<<< orphan*/  win32_get_window () ; 

__attribute__((used)) static bool win32_display_server_set_window_opacity(void *data, unsigned opacity)
{
   HWND hwnd = win32_get_window();
   dispserv_win32_t *serv = (dispserv_win32_t*)data;

   if (serv)
      serv->opacity       = opacity;

#if defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0500
   /* Set window transparency on Windows 2000 and above */
   if (opacity < 100)
   {
      SetWindowLongPtr(hwnd,
            GWL_EXSTYLE,
            GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
      return SetLayeredWindowAttributes(hwnd, 0, (255 * opacity) / 100, LWA_ALPHA);
   }

   SetWindowLongPtr(hwnd,
         GWL_EXSTYLE,
         GetWindowLongPtr(hwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
   return true;
#else
   return false;
#endif
}