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
typedef  int /*<<< orphan*/  title ;
struct TYPE_2__ {scalar_t__ zxdg_toplevel; scalar_t__ xdg_toplevel; scalar_t__ deco; } ;
typedef  TYPE_1__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE ; 
 int /*<<< orphan*/  video_driver_get_window_title (char*,int) ; 
 int /*<<< orphan*/  xdg_toplevel_set_title (scalar_t__,char*) ; 
 int /*<<< orphan*/  zxdg_toplevel_decoration_v1_set_mode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_set_title (scalar_t__,char*) ; 

__attribute__((used)) static void gfx_ctx_wl_update_title(void *data, void *data2)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;
   char title[128];

   title[0] = '\0';

   video_driver_get_window_title(title, sizeof(title));

   if (wl && title[0])
   {
      if (wl->xdg_toplevel || wl->zxdg_toplevel)
      {
         if (wl->deco)
         {
            zxdg_toplevel_decoration_v1_set_mode(wl->deco,
                  ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
         }
      }
      if (wl->xdg_toplevel)
         xdg_toplevel_set_title(wl->xdg_toplevel, title);
      else if (wl->zxdg_toplevel)
         zxdg_toplevel_v6_set_title(wl->zxdg_toplevel, title);
   }
}