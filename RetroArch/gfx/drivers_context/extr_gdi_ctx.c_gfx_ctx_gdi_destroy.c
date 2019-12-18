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
typedef  int /*<<< orphan*/  gfx_ctx_gdi_data_t ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int g_win32_inited ; 
 int g_win32_restore_desktop ; 
 int /*<<< orphan*/  win32_destroy_window () ; 
 int /*<<< orphan*/ * win32_gdi_hdc ; 
 scalar_t__ win32_gdi_major ; 
 scalar_t__ win32_gdi_minor ; 
 scalar_t__ win32_get_window () ; 
 int /*<<< orphan*/  win32_monitor_from_window () ; 
 int /*<<< orphan*/  win32_monitor_get_info () ; 

__attribute__((used)) static void gfx_ctx_gdi_destroy(void *data)
{
   gfx_ctx_gdi_data_t *gdi = (gfx_ctx_gdi_data_t*)data;
   HWND     window         = win32_get_window();

   if (window && win32_gdi_hdc)
   {
      ReleaseDC(window, win32_gdi_hdc);
      win32_gdi_hdc = NULL;
   }

   if (window)
   {
      win32_monitor_from_window();
      win32_destroy_window();
   }

   if (g_win32_restore_desktop)
   {
      win32_monitor_get_info();
      g_win32_restore_desktop     = false;
   }

   if (gdi)
      free(gdi);

   g_win32_inited                   = false;
   win32_gdi_major                  = 0;
   win32_gdi_minor                  = 0;
}