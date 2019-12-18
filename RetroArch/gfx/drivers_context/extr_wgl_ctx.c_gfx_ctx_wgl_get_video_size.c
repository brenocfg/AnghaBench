#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int right; unsigned int left; unsigned int bottom; unsigned int top; } ;
struct TYPE_5__ {TYPE_1__ rcMonitor; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ MONITORINFOEX ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HMONITOR ;

/* Variables and functions */
 unsigned int g_win32_resize_height ; 
 unsigned int g_win32_resize_width ; 
 int /*<<< orphan*/  win32_get_window () ; 
 int /*<<< orphan*/  win32_monitor_info (TYPE_2__*,int /*<<< orphan*/ **,unsigned int*) ; 

__attribute__((used)) static void gfx_ctx_wgl_get_video_size(void *data,
      unsigned *width, unsigned *height)
{
   HWND         window  = win32_get_window();

   (void)data;

   if (!window)
   {
      RECT mon_rect;
      MONITORINFOEX current_mon;
      unsigned mon_id           = 0;
      HMONITOR hm_to_use        = NULL;

      win32_monitor_info(&current_mon, &hm_to_use, &mon_id);
      mon_rect = current_mon.rcMonitor;
      *width  = mon_rect.right - mon_rect.left;
      *height = mon_rect.bottom - mon_rect.top;
   }
   else
   {
      *width  = g_win32_resize_width;
      *height = g_win32_resize_height;
   }
}