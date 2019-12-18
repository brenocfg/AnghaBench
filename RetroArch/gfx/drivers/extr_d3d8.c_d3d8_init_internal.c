#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {unsigned int width; unsigned int height; int /*<<< orphan*/  fullscreen; } ;
typedef  TYPE_3__ video_info_t ;
struct TYPE_26__ {int /*<<< orphan*/  input_joypad_driver; int /*<<< orphan*/  input_driver; } ;
struct TYPE_25__ {int video_windowed_fullscreen; } ;
struct TYPE_28__ {TYPE_2__ arrays; TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_29__ {int* tex_coords; int* vert_coords; } ;
typedef  TYPE_5__ overlay_t ;
typedef  int /*<<< orphan*/  input_driver_t ;
struct TYPE_33__ {int /*<<< orphan*/  lpfnWndProc; } ;
struct TYPE_30__ {TYPE_3__ video_info; int /*<<< orphan*/  cur_mon_id; TYPE_9__ windowClass; TYPE_5__* menu; } ;
typedef  TYPE_6__ d3d8_video_t ;
struct TYPE_31__ {unsigned int right; unsigned int left; unsigned int bottom; unsigned int top; int /*<<< orphan*/  member_0; } ;
struct TYPE_32__ {TYPE_7__ rcMonitor; } ;
typedef  TYPE_7__ RECT ;
typedef  TYPE_8__ MONITORINFOEX ;
typedef  int /*<<< orphan*/  HMONITOR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  WndProcD3D ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  d3d8_get_video_size (TYPE_6__*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  d3d8_init_singlepass (TYPE_6__*) ; 
 int /*<<< orphan*/  d3d8_initialize (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  d3d_input_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,void**) ; 
 unsigned int g_win32_resize_height ; 
 unsigned int g_win32_resize_width ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  video_driver_set_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  win32_monitor_info (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win32_set_style (TYPE_8__*,int /*<<< orphan*/ *,unsigned int*,unsigned int*,int /*<<< orphan*/ ,int,TYPE_7__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win32_set_window (unsigned int*,unsigned int*,int /*<<< orphan*/ ,int,TYPE_7__*) ; 
 int /*<<< orphan*/  win32_window_create (TYPE_6__*,int /*<<< orphan*/ ,TYPE_7__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win32_window_init (TYPE_9__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool d3d8_init_internal(d3d8_video_t *d3d,
      const video_info_t *info, input_driver_t **input,
      void **input_data)
{
#ifdef HAVE_MONITOR
   bool windowed_full;
   RECT mon_rect;
   MONITORINFOEX current_mon;
   HMONITOR hm_to_use;
#endif
#ifdef HAVE_WINDOW
   DWORD style;
   unsigned win_width        = 0;
   unsigned win_height       = 0;
   RECT rect                 = {0};
#endif
   unsigned full_x           = 0;
   unsigned full_y           = 0;
   settings_t    *settings   = config_get_ptr();
   overlay_t *menu           = (overlay_t*)calloc(1, sizeof(*menu));

   if (!menu)
      return false;

   d3d->menu                 = menu;
   d3d->cur_mon_id           = 0;
   d3d->menu->tex_coords[0]  = 0;
   d3d->menu->tex_coords[1]  = 0;
   d3d->menu->tex_coords[2]  = 1;
   d3d->menu->tex_coords[3]  = 1;
   d3d->menu->vert_coords[0] = 0;
   d3d->menu->vert_coords[1] = 1;
   d3d->menu->vert_coords[2] = 1;
   d3d->menu->vert_coords[3] = -1;

#ifdef HAVE_WINDOW
   memset(&d3d->windowClass, 0, sizeof(d3d->windowClass));
   d3d->windowClass.lpfnWndProc = WndProcD3D;
   win32_window_init(&d3d->windowClass, true, NULL);
#endif

#ifdef HAVE_MONITOR
   win32_monitor_info(&current_mon, &hm_to_use, &d3d->cur_mon_id);

   mon_rect              = current_mon.rcMonitor;
   g_win32_resize_width  = info->width;
   g_win32_resize_height = info->height;

   windowed_full   = settings->bools.video_windowed_fullscreen;

   full_x          = (windowed_full || info->width  == 0) ?
      (mon_rect.right  - mon_rect.left) : info->width;
   full_y          = (windowed_full || info->height == 0) ?
      (mon_rect.bottom - mon_rect.top)  : info->height;

   RARCH_LOG("[D3D8]: Monitor size: %dx%d.\n",
         (int)(mon_rect.right  - mon_rect.left),
         (int)(mon_rect.bottom - mon_rect.top));
#else
   d3d8_get_video_size(d3d, &full_x, &full_y);
#endif
   {
      unsigned new_width  = info->fullscreen ? full_x : info->width;
      unsigned new_height = info->fullscreen ? full_y : info->height;
      video_driver_set_size(&new_width, &new_height);
   }

#ifdef HAVE_WINDOW
   video_driver_get_size(&win_width, &win_height);

   win32_set_style(&current_mon, &hm_to_use, &win_width, &win_height,
         info->fullscreen, windowed_full, &rect, &mon_rect, &style);

   win32_window_create(d3d, style, &mon_rect, win_width,
         win_height, info->fullscreen);

   win32_set_window(&win_width, &win_height, info->fullscreen,
	   windowed_full, &rect);
#endif

   if (!d3d8_init_singlepass(d3d))
      return false;

   d3d->video_info = *info;
   if (!d3d8_initialize(d3d, &d3d->video_info))
      return false;

   d3d_input_driver(settings->arrays.input_driver, settings->arrays.input_joypad_driver, input, input_data);

   RARCH_LOG("[D3D8]: Init complete.\n");
   return true;
}